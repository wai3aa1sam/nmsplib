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
	void terminate();

	void submit(JobHandle job);
	void run();

	bool tryGetJob(JobHandle& job);

	void nextFrame();

	SizeType workerCount() const;
	SizeType threadCount() const;

	SizeType workerId(int threadLocalId = JobSystemTraits::threadLocalId()) const;
	ThreadStorage& threadStroages(int threadLocalId);
	ThreadStorage& threadStroage();

protected:
	bool trySteal(WorkerThread* worker, JobHandle& job);

	int getNextIndex(int i);

private:
	Vector_T<UPtr_T<WorkerThread>,	JobSystemTraits::s_kJobSystemLogicalThreadCount> _workers;
	Vector_T<UPtr_T<ThreadStorage>, JobSystemTraits::s_kJobSystemLogicalThreadCount> _threadStorages;

	JobQueue _queue;

	Atm_T<int>	_nextIndex = 0;
	Atm_T<bool>	_isDone = false;

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
	return math::clamp(threadLocalId - _typedThreadCount, sCast<SizeType>(0), _threadStorages.size() - 1);
}

inline
ThreadPool_T::ThreadStorage& ThreadPool_T::threadStroage()
{
	return *_threadStorages[workerId()];
}

inline
ThreadPool_T::ThreadStorage& ThreadPool_T::threadStroages(int threadLocalId)
{
	return *_threadStorages[workerId(threadLocalId)];
}

inline ThreadPool_T::SizeType ThreadPool_T::workerCount() const { return _workers.size(); }
inline ThreadPool_T::SizeType ThreadPool_T::threadCount() const { return _threadStorages.size(); }


#endif

}