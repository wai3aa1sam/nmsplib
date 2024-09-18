#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

namespace nmsp {

class ThreadStorage_T;
class ThreadPool_T;
class JobSystem_T;

#if 0
#pragma mark --- TypeThread_T-Decl ---
#endif // 0
#if 1

struct TypeThread_CreateDesc : public NativeThread_T::CreateDesc
{
	using ThreadPool = ThreadPool_T;

public:
	ThreadPool* threadPool = nullptr;
};

class TypeThread_T : public NativeThread_T
{
public:
	using Base = NativeThread_T;

	using CreateDesc		= TypeThread_CreateDesc;
	using CreateDesc_Base	= Base::CreateDesc_Base;

	using JobQueue		= JobQueue_T<>;
	using JobHandle		= JobHandle_T;
	using ThreadPool	= ThreadPool_T;
	using ThreadStorage = ThreadStorage_T;
	using JobSystem_T	= JobSystem_T;

public:
	static CreateDesc makeCDesc();

public:
	TypeThread_T();
	virtual ~TypeThread_T();

	void create(const CreateDesc_Base& cDescBase);
	void destroy();

	void wake();
	void sleep();

public:
	ThreadStorage& threadStorage();

protected:
	virtual void onCreate(const CreateDesc_Base& cDescBase);
	virtual void onDestroy();

	virtual void* onProceed() override;

	void* routine();
	virtual void* onRoutine() = 0;

protected:
	void resetSleepCount();
	void addSleepCount();
	bool shouldSleep() const;

	template<class... ARGS> void debugLog(ARGS&&... args);
	template<class... ARGS> void log(ARGS&&... args);

protected:
	ThreadPool* threadPool();

protected:
	ThreadPool*	_threadPool = nullptr;

private:
	// ThreadSleeper
	int _sleepCount	= 0;
};

#endif

#if 0
#pragma mark --- TypeThread_T-Decl ---
#endif // 0
#if 1

inline
TypeThread_T::CreateDesc TypeThread_T::makeCDesc()
{
	return CreateDesc{};
}

inline void TypeThread_T::resetSleepCount()		{ _sleepCount = 0; }
inline void TypeThread_T::addSleepCount()		{ _sleepCount++; }
inline bool TypeThread_T::shouldSleep() const	{ return _sleepCount >= JobSystemTraits::s_kSleepCountThreshold; }

template<class... ARGS> inline
void  
TypeThread_T::debugLog(ARGS&&... args)
{
	//atomicLog(nmsp::forward<ARGS>(args)...);
}

template<class... ARGS> inline
void 
TypeThread_T::log(ARGS&&... args)
{
	//atomicLog(nmsp::forward<ARGS>(args)...);
}

inline TypeThread_T::ThreadPool* TypeThread_T::threadPool() { return _threadPool; }

#endif

}