#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_job_system-config.h"

namespace nmsp {

#if 0
#pragma mark --- JobSystemTraits-Impl ---
#endif // 0
#if 1

struct JobSystemDefaultTraits_T : public OsTraits
{
	using SizeType = size_t;
	
	static constexpr int s_kIdleSleepTimeMS		= 1;
	static constexpr int s_kBusySleepTimeMS		= 0;
	static constexpr int s_kSleepCountThreshold	= 2000;


	static constexpr SizeType s_kMaxFrameInFlightCount			= NMSP_JOB_SYSTEM_MAX_FRAME_IN_FLIGHT_COUNT;
	static constexpr SizeType s_kJobSystemLogicalThreadCount	= NMSP_JOB_SYSTEM_LOGICAL_THREAD_COUNT;

public:

	static void setMainThread() { setThreadLocalId(s_kMainThreadLocalId); NMSP_PROFILE_SET_THREAD_NAME(s_mainThreadName);}
};


#if !NMSP_JOB_SYSTEM_CUSTOM_TRAITS

using JobSystemTraits = JobSystemDefaultTraits_T;

#else

#endif // 

#endif

}
