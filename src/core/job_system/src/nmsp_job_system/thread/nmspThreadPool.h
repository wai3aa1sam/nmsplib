#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include <nmsp_os/atomic/extra/nmspAtomicQueue.h>

#include "nmsp_job_system/thread/nmspThreadStorage.h"
#include "nmspWorkerThread.h"

namespace nmsp {

#if 0
#pragma mark --- ThreadPool_T-Decl ---
#endif // 0
#if 1

struct ThreadPool_CreateDesc
{
	using SizeType		= JobSystemTraits::SizeType;

	SizeType workerCount		= 0;
	SizeType typedThreadCount	= 1;
};

class ThreadPool_T : public NonCopyable
{
public:
	using CreateDesc	= ThreadPool_CreateDesc;
	using JobQueue		= JobQueue_T<>;
	using JobHandle		= JobHandle_T;
	using ThreadStorage	= ThreadStorage_T;
	using WorkerThread	= WorkerThread_T;
	using JobSystem		= JobSystem_T;

	using SizeType		= JobSystemTraits::SizeType;

public:
	friend class WorkerThread;
	friend class JobSystem;

public:
	ThreadPool_T() = default;
	ThreadPool_T(const CreateDesc& desc);
	~ThreadPool_T();

	void create(const CreateDesc& desc);
	void destroy();

	void submit(JobHandle job);
	void execute(JobHandle job);

	void run();	// useless now, maybe have a pending sumbit and then call run to execute those jobs
	void nextFrame();

	SizeType workerCount() const;
	SizeType threadCount() const;

	SizeType workerId(int threadLocalId = JobSystemTraits::threadLocalId()) const;
	ThreadStorage& threadStroages(int threadLocalId);
	ThreadStorage& threadStroage();
	
	WorkerThread& workerThreads(int threadLocalId);
	WorkerThread& workerThread();

	const WorkerThread& workerThreads(int threadLocalId) const;

protected:
	bool tryGetJob(JobHandle& job);
	bool trySteal(WorkerThread* worker, JobHandle& job);
	void complete(JobHandle job);
	void _submit(JobHandle job);
	int getNextIndex(int i);

	bool isReadyToRun() const;

private:
	Vector_T<UPtr_T<WorkerThread>,	JobSystemTraits::s_kJobSystemLogicalThreadCount> _workers;
	Vector_T<UPtr_T<ThreadStorage>, JobSystemTraits::s_kJobSystemLogicalThreadCount> _threadStorages;

	JobQueue _queue;

	Atm_T<int>	_nextIndex = 0;
	Atm_T<bool>	_isDone			= false;
	Atm_T<bool>	_isReadyToRun	= false;

	int _nfsNextIndex = 0;

	SizeType _typedThreadCount = 0;
};

#endif


#if 0
#pragma mark --- ThreadPool_T-Impl ---
#endif // 0
#if 1

inline
ThreadPool_T::SizeType ThreadPool_T::workerId(int threadLocalId) const
{
	return threadLocalId - _typedThreadCount;
	//return math::clamp(threadLocalId - _typedThreadCount, sCast<SizeType>(0), _threadStorages.size() - 1);
}

inline
ThreadPool_T::ThreadStorage& ThreadPool_T::threadStroage()
{
	return threadStroages(JobSystemTraits::threadLocalId());
}

inline
ThreadPool_T::ThreadStorage& ThreadPool_T::threadStroages(int threadLocalId)
{
	auto i = workerId(threadLocalId);
	NMSP_ASSERT(_workers[i]->localId() == threadLocalId);
	return *_threadStorages[i];
}

inline ThreadPool_T::WorkerThread& ThreadPool_T::workerThread() { return workerThreads(JobSystemTraits::threadLocalId()); }

inline 
ThreadPool_T::WorkerThread& ThreadPool_T::workerThreads(int threadLocalId)
{
	auto i = workerId();
	NMSP_ASSERT(_workers[i]->localId() == threadLocalId);
	return *_workers[i];
}

inline 
const ThreadPool_T::WorkerThread& ThreadPool_T::workerThreads(int threadLocalId) const
{
	auto i = workerId();
	NMSP_ASSERT(_workers[i]->localId() == threadLocalId);
	return *_workers[i];
}

inline ThreadPool_T::SizeType ThreadPool_T::workerCount() const { return _workers.size(); }
inline ThreadPool_T::SizeType ThreadPool_T::threadCount() const { return _threadStorages.size(); }

inline bool ThreadPool_T::isReadyToRun() const { return _isReadyToRun.load(); }


#endif

}