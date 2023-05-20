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
	_workers[_nextIndex]->submit(job);
	_nextIndex = getNextIndex(_nextIndex);
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