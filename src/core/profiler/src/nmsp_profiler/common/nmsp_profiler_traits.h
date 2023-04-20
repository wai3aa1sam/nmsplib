#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_profiler-config.h"

namespace nmsp {


#if 0
#pragma mark --- ProfilerTraits-Impl ---
#endif // 0
#if 1
struct ProfilerDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_PROFILER_CUSTOM_TRAITS

using ProfilerTraits = ProfilerDefaultTraits_T;

#else

#endif // 

#endif

}
