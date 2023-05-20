#include "nmsp_job_system-pch.h"
#include "nmspThreadPool.h"

#include "nmspWorkerThread.h"

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
	terminate();
}

void ThreadPool_T::create(const CreateDesc& desc)
{
	NMSP_ASSERT(desc.workerCount <= OsTraits::logicalThreadCount());
	auto workerCount = (desc.workerCount == 0) ? OsTraits::logicalThreadCount() : desc.workerCount;
	//workerCount = ( OsTraits::logicalThreadCount() - 1) / 2;
	//workerCount = 1;

	_typedThreadCount = desc.typedThreadCount;

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

			_threadStorages.emplace_back(nmsp_new<ThreadStorage>());
			_workers.emplace_back(nmsp_new<WorkerThread>(workerCDesc));
		}
	}
	catch (...)
	{
		_threadStorages.clear();
		_workers.clear();
		//atomicLog("ThreadPool_T create failed");
	}
}

void ThreadPool_T::terminate()
{
	_isDone = true;
	for (auto& t : _workers)
	{
		//atomicLog("ThreadPool_T::terminate(), thread {}", t->localId());
		t->terminate();
	}
}

void ThreadPool_T::submit(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
	NMSP_ASSERT(!job->_storage._isSubmitted);
	NMSP_ASSERT(!job->_storage._isExecuted);

	job->_storage._isSubmitted.store(true);
	job->_storage._isAllowAddDeps.store(false);
	#endif // 0

	#if NMSP_JOB_SYSTEM_ENABLE_SINGLE_THREAD_DEBUG
	_submit(job);
	#else

	if (!job->_storage.dep.couldRun())
	{
		// rare case, maybe have some bug, all job should sumbit when dep count is 0
		// 19/1/2023: no bug now, since _complete() are not reading and compare the copy, 
		// when contex-switch, possibly call _complete() multiple times which causing calling multipy runAfterThisIffNoDeps(),
		// couldRun() would be compare negative number, since it is executed
		NMSP_ASSERT(job->_storage.dep.couldRun());
	}

	_submit(job);

	#endif
}

void ThreadPool_T::execute(JobHandle job)
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

	complete(job);
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
	for (int i = 0; i < _workers.size(); i++)
	{
		if (_workers[i]->queue().try_pop(job))
		{
			return true;
		}
	}
	return false;
}

bool ThreadPool_T::trySteal(WorkerThread* worker, JobHandle& job)
{
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
}

void ThreadPool_T::complete(JobHandle job)
{
	auto& jobRemainCount	= job->_storage._jobRemainCount;
	auto& parent			= job->_storage._parent;
	//auto& depsOnThis		= job->_storage.dep._depsOnThis;

	//atomicLog("=== task complete");
	int ret = jobRemainCount.fetch_sub(1) - 1;
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
			complete(parent);
		}

		job->_storage.dep.runAfterThis_for_each_ifNoDeps(*this, &ThreadPool_T::submit);
	}
}

void ThreadPool_T::_submit(JobHandle job)
{
	_workers[_nextIndex]->submit(job);
	_nextIndex = getNextIndex(_nextIndex);
}

int ThreadPool_T::getNextIndex(int i)
{
	i++;
	if (i >= _workers.size() || i < 0)
		i = 0;
	return i;
}

void ThreadPool_T::nextFrame()
{
	for (auto& ts : _threadStorages)
	{
		ts->nextFrame();
	}
}

#endif

}