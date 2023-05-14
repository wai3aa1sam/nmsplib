#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_job_system-config.h"

namespace nmsp {


#if 0
#pragma mark --- JobSystemTraits-Impl ---
#endif // 0
#if 1
struct JobSystemDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_JOB_SYSTEM_CUSTOM_TRAITS

using JobSystemTraits = JobSystemDefaultTraits_T;

#else

#endif // 

#endif

}
