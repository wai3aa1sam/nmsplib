#include "nmsp_job_system-pch.h"
#include "nmspJobSystem.h"

#include "thread/nmspThreadStorage.h"

namespace nmsp {

#if 0
#pragma mark --- JobSystem_T-Impl ---
#endif // 0
#if 1

JobSystem_T* StackSingleton_T<JobSystem_T>::s_instance = nullptr;

JobSystem_T::JobSystem_T(int workerCount, int threadTypeCount)
{
	auto cDesc = makeCDesc();
	create(cDesc);
}

JobSystem_T::JobSystem_T(const CreateDesc& cDesc)
{
	create(cDesc);
}

JobSystem_T::~JobSystem_T()
{
	_threadPool.terminate();
}

void JobSystem_T::create(const CreateDesc& cDesc)
{
	destroy();

	auto threadTypeCount	= cDesc.threadTypeCount;
	auto workerCount		= cDesc.workerCount;

	NMSP_ASSERT(JobSystemTraits::logicalThreadCount() == JobSystemTraits::s_kJobSystemLogicalThreadCount, "please set marco NMSP_JOB_SYSTEM_LOGICAL_THREAD_COUNT to correct number");
	NMSP_ASSERT(threadTypeCount > 0 && threadTypeCount <= OsTraits::logicalThreadCount());

	auto total_thread = OsTraits::logicalThreadCount();
	_typedThreadCount = threadTypeCount;
	auto nWorkers = workerCount > 0 ? workerCount : total_thread - _typedThreadCount;
	NMSP_ASSERT(nWorkers >= 0 && nWorkers<= OsTraits::logicalThreadCount(), "workerCount + threadTypeCount > logicalThreadCount");

	JobSystemTraits::setThreadLocalId(JobSystemTraits::s_kMainThreadLocalId);
	NMSP_PROFILE_SET_THREAD_NAME(JobSystemTraits::s_mainThreadName);

	_createTypedThreads();

	ThreadPool_CreateDesc desc;
	desc.typedThreadCount	= _typedThreadCount;
	desc.workerCount		= nWorkers;
	_threadPool.create(desc);
}

void JobSystem_T::destroy()
{
	JobSystemTraits::resetThreadLocalId();
	//_threadPool.destroy();
	_typedThreadStorages.clear();
	_typedThreads.clear();
}

void JobSystem_T::waitForComplete(JobHandle job)
{
	NMSP_ASSERT(JobSystemTraits::isMainThread(), "");
	auto* jsys = this;
	auto& threadPool = this->_threadPool;
	auto& storage = jsys->_threadStorage(); (void)storage;

	while (!job->isCompleted())
	{
		JobHandle tmp = nullptr;

		if (threadPool.tryGetJob(tmp))
		{
			_execute(tmp);
		}

		OsUtil::sleep_ms(JobSystemTraits::s_kBusySleepTimeMS);
	}

	//atomicLog("=== done waitForComplete()");
}

void JobSystem_T::submit(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
	NMSP_ASSERT(!job->_storage._isSubmitted);
	NMSP_ASSERT(!job->_storage._isExecuted);

	job->_storage._isSubmitted.store(true);
	job->_storage._isAllowAddDeps.store(false);
	#endif // 0

	#if NMSP_JOB_SYSTEM_ENABLE_SINGLE_THREAD_DEBUG
	_execute(job);
	#else

	if (!job->_storage.dep.couldRun())
	{
		// rare case, maybe have some bug, all job should sumbit when dep count is 0
		// 19/1/2023: no bug now, since _complete() are not reading and compare the copy, 
		// when contex-switch, possibly call _complete() multiple times which causing calling multipy runAfterThisIffNoDeps(),
		// couldRun() would be compare negative number, since it is executed
		NMSP_ASSERT(job->_storage.dep.couldRun());
	}

	auto& threadPool = instance()->_threadPool;
	threadPool.submit(job);
	#endif
}

void JobSystem_T::_internal_nextFrame()
{
	NMSP_ASSERT(JobSystemTraits::isMainThread());

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::nextFrame();
	#endif // 0

	_threadPool.nextFrame();
}

JobSystem_T::ThreadStorage& JobSystem_T::_threadStorage()
{
	auto* jsys = this;
	jsys->_checkError();

	auto id = JobSystemTraits::threadLocalId();
	return jsys->isTypedThread(id) ? *jsys->_typedThreadStorages[id] : _threadPool.threadStroages(id);
}

JobSystem_T::JobHandle JobSystem_T::createEmptyJob()
{
	auto* job = JobSystem_T::allocateJob();
	job->setEmpty();
	return job;
}

StrViewA_T JobSystem_T::threadName() const
{
	auto* jsys = this;
	jsys->_checkError();
	auto id = JobSystemTraits::threadLocalId();
	if (id < typedThreadCount())
	{
		return jsys->_typedThreads[id]->name();
	}
	else
	{
		return jsys->_threadPool._workers[id]->name();
	}
}

bool JobSystem_T::_tryGetJob(JobHandle& job)
{
	return _threadPool.tryGetJob(job);
}

JobSystem_T::FrameAllocator& JobSystem_T::_defaultAllocator()
{
	auto* jsys = JobSystem_T::instance();
	jsys->_checkError();



	auto& frameAlloc = jsys->_threadPool.threadStroages(JobSystemTraits::threadLocalId()).frameAllocator();
	return frameAlloc;
}

void JobSystem_T::_checkError() const
{
	//if (!(JobSystemTraits::threadLocalId() >= 0 && JobSystemTraits::threadLocalId() < _threadPool.threadCount()))
	{
		//atomicLog("=== threadLocalId() {}, localId {} _checkError()", threadLocalId(), this->_threadStorages[threadLocalId()]->localId());
	}

	//NMSP_ASSERT(JobSystemTraits::threadLocalId() >= 0 && JobSystemTraits::threadLocalId() < _threadPool.threadCount());
}

void JobSystem_T::_complete(JobHandle job)
{
	auto& jobRemainCount	= job->_storage._jobRemainCount;
	auto& parent			= job->_storage._parent;
	//auto& depsOnThis		= job->_storage.dep._depsOnThis;

	//atomicLog("=== task complete");
	int ret = jobRemainCount.fetch_sub(1) - 1;
	// must have a copy, consider the jobRemainCount maybe 1, when contex-switch, 
	// other thread is decr the jobRemainCount, both of them will trigger jobRemainCount == 0,
	// possibly call _complete() multiple times which causing calling multipy runAfterThisIffNoDeps(),

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	if (!parent)
		DependencyManager::jobFinish(job);
	#endif // 0

	if (ret == 0)	// must compare
	{
		if (parent)
		{
			_complete(parent);
		}

		job->_storage.dep.runAfterThis_for_each_ifNoDeps(JobSystem_T::submit);
	}
}

void JobSystem_T::_execute(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::jobExecute(job);
	#endif // 0

	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
	NMSP_ASSERT(job->_storage._isSubmitted);
	NMSP_ASSERT(!job->_storage._isExecuted);

	job->_storage._isAllowAddDeps.store(false);
	job->_storage._isExecuted.store(true);
	#endif // 0

	auto& task  = job->_storage._task;
	auto& info	= job->info();

	JobArgs args;
	args.batchID = info.batchID;

	for (u32 i = info.batchOffset; i < info.batchEnd; ++i)
	{
		args.loopIndex  = i;
		args.batchIndex = i - info.batchOffset;
		task(args);
	}

	_complete(job);
}
void JobSystem_T::_createTypedThreads()
{
	_typedThreads.reserve(_typedThreadCount);
	_typedThreadStorages.reserve(_typedThreadCount);

	// Main Thread
	_typedThreadStorages.emplace_back();
	_typedThreads.emplace_back(nullptr);

	for (size_t i = 1; i < _typedThreadCount; i++)
	{
		_typedThreadStorages.emplace_back(nmsp_new<ThreadStorage>());
		_typedThreads.emplace_back(/*nmsp_new<WorkerThread>(workerCDesc)*/);
	}

}

#endif


}