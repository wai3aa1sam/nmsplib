#include "nmsp_job_system-pch.h"
#include "nmspTypeThread.h"

#include "nmsp_job_system/nmspJobSystem.h"
#include "nmspThreadStorage.h"
#include "nmspThreadPool.h"

namespace nmsp 
{

#if 0
#pragma mark --- TypeThread_T-Impl ---
#endif // 0
#if 1

TypeThread_T::TypeThread_T()
{
	
}

TypeThread_T::~TypeThread_T()
{
	debugLog("thread {} ~TypeThread_T()", localId());
}

void 
TypeThread_T::create(const CreateDesc_Base& cDescBase)
{
	Base::create(cDescBase);
	onCreate(cDescBase);
}

void 
TypeThread_T::destroy()
{
	onDestroy();
	join();
}

void* 
TypeThread_T::routine()
{
	JobSystemTraits::setThreadLocalId(Base::localId());
	NMSP_PROFILE_SET_THREAD_NAME(name().c_str());

	std::exception_ptr	ptr = nullptr;
	void*				ret = nullptr;
	//debugLog("=== threadLocalId {}, localId {} onProc()", threadLocalId(), localId());

	while (!threadPool() || !threadPool()->isReadyToRun())
	{
		sleep();
	}

	try
	{
		ret = onRoutine();
	}
	catch(...)
	{
		ptr = std::current_exception();
	}

	JobSystemTraits::resetThreadLocalId();

	return ret;
}

void 
TypeThread_T::onCreate(const CreateDesc_Base& cDescBase)
{
	const auto& cDesc = sCast<const CreateDesc&>(cDescBase);
	_threadPool = cDesc.threadPool;
}

void 
TypeThread_T::onDestroy()
{
	
}

void* 
TypeThread_T::onProceed()
{
	return routine();
}

TypeThread_T::ThreadStorage&
TypeThread_T::threadStorage()	
{
	return _threadPool->threadStroages(JobSystemTraits::threadLocalId()); 
}

void 
TypeThread_T::wake() 
{ 
	//NMSP_PROFILE_SCOPED(); 
	resetSleepCount(); 
}

void
TypeThread_T::sleep()
{
	//NMSP_PROFILE_SCOPED();

	if (shouldSleep())
	{
		OsUtil::sleep_ms(JobSystemTraits::s_kIdleSleepTimeMS);
	}
	else
	{
		OsUtil::sleep_ms(JobSystemTraits::s_kBusySleepTimeMS);
		addSleepCount();
	}
}


#endif

}