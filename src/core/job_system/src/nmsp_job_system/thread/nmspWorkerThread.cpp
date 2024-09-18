#include "nmsp_job_system-pch.h"
#include "nmspWorkerThread.h"

#include "nmsp_job_system/nmspJobSystem.h"
#include "nmspThreadStorage.h"
#include "nmspThreadPool.h"

namespace nmsp {

#if 0
#pragma mark --- WorkerThread_T-Impl ---
#endif // 0
#if 1

WorkerThread_T::WorkerThread_T()
{
	
}

WorkerThread_T::~WorkerThread_T()
{
	destroy();
}

void WorkerThread_T::submit(JobHandle task)
{
	_jobs.push(task);
	//debugLog("thread {} submit(), current task size: {}", localId(), _jobs.size());
}

void 
WorkerThread_T::onCreate(const CreateDesc_Base& cDescBase)
{
	const auto& cDesc = sCast<const CreateDesc&>(cDescBase);
	Base::onCreate(cDesc);
}

void 
WorkerThread_T::onDestroy()
{


	Base::onDestroy();
}

void* 
WorkerThread_T::onRoutine()
{
	JobHandle job = nullptr;

	for (;;)
	{
		if (false)
		{
			sleep();
			continue;
		}

		while (job)
		{

			wake();

			debugLog("=== thread {} execute job", localId());
			threadPool()->execute(job);

			job = nullptr;
			_jobs.try_pop(job);
		}

		if (!_tryGetJob(job))
		{
			log("=== worker thread {} end", threadPool()->workerId());
			break;
		}
	}

	return nullptr;
}

bool WorkerThread_T::_tryGetJob(JobHandle& job)
{
	job = nullptr;

	if (_jobs.try_pop(job))
	{
		debugLog("=== thread {} _jobs.try_pop()", JobSystemTraits::threadLocalId());
		return true;
	}

	if (_threadPool->trySteal(job))
	{
		debugLog("=== thread {} trysteal()", JobSystemTraits::threadLocalId());
		return true;
	}

	#if 0
	// {1}
	{
		auto isReady = _isReady.scopedLock();
		if (!*isReady) // maybe preempted and call submit/terminate by threadPool in {1}, isReady = true
		{
			*isReady = false;
			while (!*isReady)
			{
				isReady.wait();
			}
		}
	}
	#else
	sleep();

	#endif // 0

	if (threadPool()->_isDone && !_jobs.try_pop(job))
	{
		return false;
	}

	return true;
}


#endif

}