#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_log-config.h"

namespace nmsp {

#if 0
#pragma mark --- LogTraits-Impl ---
#endif // 0
#if 1
struct LogDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_LOG_CUSTOM_TRAITS

using LogTraits = LogDefaultTraits_T;

#else

#endif // 

#endif

}
