#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include <nmsp_os/atomic/extra/nmspAtomicQueue.h>


namespace nmsp {

class ThreadStorage_T;
class ThreadPool_T;
class JobSystem_T;

#if 0
#pragma mark --- WorkerThread_T-Decl ---
#endif // 0
#if 1

struct WorkerThread_CreateDesc : public NativeThread_T::CreateDesc
{
	using ThreadPool = ThreadPool_T;

public:
	ThreadPool* threadPool = nullptr;
};

class WorkerThread_T : public NativeThread_T
{
public:
	using Base = NativeThread_T;

	using CreateDesc		= WorkerThread_CreateDesc;
	using CreateDesc_Base	= Base::CreateDesc_Base;

	using JobQueue		= JobQueue_T<>;
	using JobHandle		= JobHandle_T;
	using ThreadPool	= ThreadPool_T;
	using ThreadStorage = ThreadStorage_T;
	using JobSystem_T	= JobSystem_T;

public:
	static CreateDesc makeCDesc();

public:
	WorkerThread_T(const CreateDesc& cdesc);
	~WorkerThread_T();

	virtual void* onRoutine() override;

	void submit(JobHandle task);
	void destroy();

	void wake();
	void sleep();

	ThreadStorage& threadStorage();
	JobQueue& queue();

protected:
	ThreadPool* threadPool();

	bool _tryGetJob(JobHandle& job);

	void resetSleepCount();
	void addSleepCount();
	bool shouldSleep() const;

	template<class... ARGS> void debugLog(ARGS&&... args);
	template<class... ARGS> void log(ARGS&&... args);

private:
	JobQueue	_jobs;
	ThreadPool*	_threadPool = nullptr;

	// ThreadSleeper
	int _sleepCount		= 0;
};

#endif

#if 0
#pragma mark --- WorkerThread_T-Decl ---
#endif // 0
#if 1

inline
WorkerThread_T::CreateDesc WorkerThread_T::makeCDesc()
{
	return CreateDesc{};
}

inline WorkerThread_T::JobQueue& WorkerThread_T::queue() { return _jobs; }

inline void WorkerThread_T::resetSleepCount()	{ _sleepCount = 0; }
inline void WorkerThread_T::addSleepCount()		{ _sleepCount++; }
inline bool WorkerThread_T::shouldSleep() const	{ return _sleepCount >= JobSystemTraits::s_kSleepCountThreshold; }

template<class... ARGS> inline
void  WorkerThread_T::debugLog(ARGS&&... args)
{
	//atomicLog(nmsp::forward<ARGS>(args)...);
}

template<class... ARGS> inline
void  WorkerThread_T::log(ARGS&&... args)
{
	//atomicLog(nmsp::forward<ARGS>(args)...);
}

inline WorkerThread_T::ThreadPool* WorkerThread_T::threadPool() { return _threadPool; }

#endif

}