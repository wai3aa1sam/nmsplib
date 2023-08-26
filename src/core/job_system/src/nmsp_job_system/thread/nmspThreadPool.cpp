#include "nmsp_job_system-pch.h"
#include "nmspThreadPool.h"

#include "nmspWorkerThread.h"

#include "nmsp_job_system/nmspJobSystem.h"

#include "nmsp_job_system/job/nmspJobDispatch.h"

namespace nmsp {

#if 0
#pragma mark --- ThreadPool_T-Impl ---
#endif // 0
#if 1

ThreadPool_T::ThreadPool_T(const CreateDesc& desc)
{
	create(desc);
}

ThreadPool_T::~ThreadPool_T()
{
	destroy();
}

void ThreadPool_T::create(const CreateDesc& desc)
{
	NMSP_ASSERT(desc.workerCount <= OsTraits::logicalThreadCount());
	auto workerCount = math::clamp(desc.workerCount, sCast<SizeType>(1), OsTraits::logicalThreadCount() - 1);
	//workerCount = ( OsTraits::logicalThreadCount() - 1) / 2;
	//workerCount = 1;

	_typedThreadCount = sCast<int>(desc.typedThreadCount);

	try
	{
		_workers.reserve(workerCount);
		_threadStorages.reserve(workerCount);

		auto workerCDesc = WorkerThread::makeCDesc();
		workerCDesc.threadPool = this;

		for (int i = 0; i < workerCount; i++)
		{
			auto localId = sCast<int>(desc.typedThreadCount) + i;
			workerCDesc.affinityIdx = localId - 1;
			workerCDesc.localId		= localId;
			workerCDesc.name		= fmtAs_T<TempStringA_T<> >("Worker_{}", workerCDesc.affinityIdx);	// must not share TempBuffer, buffer will be race condition

			_threadStorages.emplace_back(NMSP_NEW(ThreadStorage)());
			_workers.emplace_back(NMSP_NEW(WorkerThread)(workerCDesc));
		}

		_isReadyToRun.store(true);
	}
	catch (...)
	{
		_threadStorages.clear();
		_workers.clear();
		//atomicLog("ThreadPool_T create failed");
	}
}

void ThreadPool_T::destroy()
{
	if (_workers.is_empty())
		return;

	_isDone = true;
	for (auto& t : _workers)
	{
		if (!t)
			continue;
		//atomicLog("ThreadPool_T::terminate(), thread {}", t->localId());
		t->destroy();
	}
	_threadStorages.clear();
	_workers.clear();
}

void ThreadPool_T::submit(JobHandle job)
{
	preSubmitCheck(job);
	_submit(job);
}

void ThreadPool_T::execute(JobHandle job)
{
	preExecuteCheck(job);
	_execute(job);
}

void ThreadPool_T::run()
{
	JobHandle job = nullptr;
	while (_queue.try_pop(job))
	{
		_workers[_nfsNextIndex]->submit(job);
		_nfsNextIndex = getNextIndex(_nfsNextIndex);
	}
}

bool ThreadPool_T::tryGetJob(JobHandle& job)
{
	#if 0
	for (int i = 0; i < _workers.size(); i++)
	{
		if (_workers[i]->queue().try_pop(job))
		{
			return true;
		}
	}
	return false;

	#else

	auto stealAttempt = 0;

	//auto& rnd	= threadStroage().random();
	auto& rnd	= JobSystem::instance()->threadStorage().random();

	while (stealAttempt < _workers.size())
	{
		auto target = rnd.range<SizeType>(0, workerCount() - 1);
		(target != workerId()) ? _workers[target]->queue().try_pop(job) : nullptr;
		if (job)
			return true;
		stealAttempt++;
	}
	return false;

	#endif // 0
}

bool ThreadPool_T::trySteal(WorkerThread* worker, JobHandle& job)
{
	#if 0

	auto stealAttempt = 0;

	auto& rnd	= threadStroage().random();

	while (stealAttempt < _workers.size())
	{
		auto target = rnd.range<SizeType>(0, workerCount() - 1);
		(target != workerId()) ? _workers[target]->queue().try_pop(job) : nullptr;
		if (job)
			return true;
		stealAttempt++;
	}
	return false;

	#else

	return tryGetJob(job);

	#endif // 0
}

void ThreadPool_T::complete(JobHandle job)
{
	return _complete_onBeginEndSupported(job);
}

void 
ThreadPool_T::_complete(JobHandle job)
{
	throwIf(true, "ThreadPool_T::_complete original version, not support onBegin()/onEnd()");

	auto& jobRemainCount	= job->_storage._jobRemainCount;
	auto& parent			= job->_storage._parent;
	//auto& depsOnThis		= job->_storage.dep._depsOnThis;

	//atomicLog("=== task complete");
	auto ret = jobRemainCount.fetch_sub(1) - 1;
	// must be a copy, consider the jobRemainCount maybe 1, when contex-switch, 
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

		//job->_storage.dep.runAfterThis_for_each_ifNoDeps(*this, &ThreadPool_T::submit);
		job->_storage.dep.runAfterThis_for_each_ifNoDeps(&JobSystem::submit); // change to this just for compatible with single thread mode
	}
}

void 
ThreadPool_T::_complete_onBeginEndSupported(JobHandle job)
{
	auto& jobRemainCount	= job->_storage._jobRemainCount;
	auto& parent			= job->_storage._parent;

	auto ret = jobRemainCount.fetch_sub(1) - 1;

	if (ret == 0)	// must compare
	{
		if (parent)
		{
			_complete_onBeginEndSupported(parent);
		}
		else
		{
			NMSP_PROFILE_SECTION("Completed");

			job->dispatchJob()->onEnd();
			job->_storage._hasExecutedOnEnd = true;
		}
		
		//job->_storage.dep.runAfterThis_for_each_ifNoDeps(*this, &ThreadPool_T::submit);
		job->_storage.dep.runAfterThis_for_each_ifNoDeps(&JobSystem::submit); // change to this just for compatible with single thread mode
	}
}

void ThreadPool_T::_submit(JobHandle job)
{
	_nextIndex = getNextIndex(_nextIndex);
	_workers[_nextIndex]->submit(job);
}

int ThreadPool_T::getNextIndex(int i)
{
	/*i++;
	if (i >= _workers.size() || i < 0)
		i = 0;*/
	// only JobSystem has all threadStorage, calling ThreadPool_T::threadStorage() will just get the worker's one
	int nWorkers = sCast<int>(workerCount()) - 1; // math::clamp(sCast<int>(workerCount()) - 1, 0, nWorkers);
	i = JobSystem::instance()->threadStorage().random().range(0, nWorkers);
	return i;
}

void ThreadPool_T::nextFrame()
{
	for (auto& ts : _threadStorages)
	{
		ts->nextFrame();
	}
}

void 
ThreadPool_T::preSubmitCheck(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(!job->_storage._isSubmitted,	"job already submitted");
	NMSP_ASSERT(!job->_storage._isExecuted,		"job already executed");

	job->_storage._isSubmitted.store(true);
	job->_storage._isAllowAddDeps.store(false);

	if (!job->_storage.dep.couldRun())
	{
		// rare case, maybe have some bug, all job should sumbit when dep count is 0
		// 19/1/2023: no bug now, since _complete() are not reading and compare the copy, 
		// when contex-switch, possibly call _complete() multiple times which causing calling multipy runAfterThisIffNoDeps(),
		// couldRun() would be compare negative number, since it is executed
		NMSP_ASSERT(job->_storage.dep.couldRun());
	}

	#endif // 0
}

void 
ThreadPool_T::preExecuteCheck(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::jobExecute(job);
	#endif // 0

	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(job->_storage._isSubmitted);
	NMSP_ASSERT(!job->_storage._isExecuted);

	job->_storage._isAllowAddDeps.store(false);
	job->_storage._isExecuted.store(true);
	#endif // 0

	NMSP_ASSERT(job->dependencyCount() == 0, "");
}

void 
ThreadPool_T::_execute(JobHandle job)
{
	auto& task  = job->_storage._task;
	auto& info	= job->info();

	JobArgs args;
	args.batchID = info.batchID;

	if (!job->parent())
	{
		job->dispatchJob()->onBegin();
	}

	for (u32 i = info.batchOffset; i < info.batchEnd; ++i)
	{
		args.loopIndex  = i;
		args.batchIndex = i - info.batchOffset;
		task(args);
	}

	complete(job);
}


#endif

}