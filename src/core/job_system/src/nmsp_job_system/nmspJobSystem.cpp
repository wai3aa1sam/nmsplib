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
	terminate();
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
	auto& storage = jsys->threadStorage(); (void)storage;

	while (!job->isCompleted())
	{
		JobHandle tmp = nullptr;

		if (threadPool.tryGetJob(tmp))
		{
			threadPool.execute(tmp);
		}

		OsUtil::sleep_ms(JobSystemTraits::s_kBusySleepTimeMS);
	}

	//atomicLog("=== done waitForComplete()");
}

void JobSystem_T::submit(JobHandle job)
{
	//NMSP_ASSERT(JobSystemTraits::isMainThread(), "only can submit job in main thread");
	//throwIf(!JobSystemTraits::isMainThread(), "only can submit job in main thread");
	/*
		- since Unity JobSystem cannot submit job in main thread only, however, we cannot follow it, 
		since the job delayDispatch() in current implementation is create the actual job within a job. 
		If want follow it, then we must found another implementation for delay dispatch  
		(no job within job, then FrameAllocator will have no problem, 
		currently I believe there is some rare bug when the frame run very fast 
		and some job may allocate in the next frame since it may still doing stuff in previous frame, this may have bug
	*/

	auto& threadPool = instance()->_threadPool;
	threadPool.submit(job);
}

void JobSystem_T::_internal_nextFrame()
{
	NMSP_ASSERT(JobSystemTraits::isMainThread());

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::nextFrame();
	#endif // 0

	for (auto& ts : _typedThreadStorages)
	{
		ts->nextFrame();
	}
	_threadPool.nextFrame();
}


JobSystem_T::JobHandle JobSystem_T::createEmptyJob()
{
	auto* job = JobSystem_T::allocateJob();
	job->setEmpty();
	return job;
}

void JobSystem_T::terminate()
{
	_threadPool.terminate();
	for (auto& t : _typedThreads)
	{
		if (!t)
			continue;
		t->join();
	}
}

JobSystem_T::FrameAllocator& JobSystem_T::_defaultAllocator()
{
	auto* jsys = JobSystem_T::instance();
	jsys->_checkError();

	auto& frameAlloc = jsys->threadStorage().frameAllocator();
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

void JobSystem_T::_createTypedThreads()
{
	_typedThreads.reserve(_typedThreadCount);
	_typedThreadStorages.reserve(_typedThreadCount);

	// Main Thread
	_typedThreadStorages.emplace_back(nmsp_new<ThreadStorage>());
	_typedThreads.emplace_back(nullptr);

	for (size_t i = 1; i < _typedThreadCount; i++)
	{
		_typedThreadStorages.emplace_back(nmsp_new<ThreadStorage>());
		_typedThreads.emplace_back(/*nmsp_new<WorkerThread>(workerCDesc)*/);
	}
}

#endif


}