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

WorkerThread_T::WorkerThread_T(const CreateDesc& cdesc)
{
	_threadPool = cdesc.threadPool;
	Base::create(cdesc);
}

WorkerThread_T::~WorkerThread_T()
{
	debugLog("thread {} ~WorkerThread_T()", localId());
	terminate();
}

void WorkerThread_T::submit(JobHandle task)
{
	_jobs.push(task);
	//debugLog("thread {} submit(), current task size: {}", localId(), _jobs.size());
}

void WorkerThread_T::terminate()
{
	join();
}

void* WorkerThread_T::onRoutine()
{
	JobSystemTraits::setThreadLocalId(Base::localId());
	::tracy::SetThreadName(name().c_str());

	std::exception_ptr ptr = nullptr;
	//debugLog("=== threadLocalId {}, localId {} onProc()", threadLocalId(), localId());

	try
	{
		JobHandle job = nullptr;

		for (;;)
		{
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
				//	log("=== thread {} end, queue count {}", threadLocalId(), _jobs.size());
				break;
			}
		}
	}
	catch(...)
	{
		ptr = std::current_exception();
	}

	JobSystemTraits::resetThreadLocalId();

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

	if (_threadPool->trySteal(this, job))
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

	if (_threadPool->_isDone && !_jobs.try_pop(job))
	{
		return false;
	}

	return true;
}

WorkerThread_T::ThreadStorage&	WorkerThread_T::threadStorage()	
{
	return _threadPool->threadStroages(JobSystemTraits::threadLocalId()); 
}

#endif

}