#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_core-config.h"

namespace nmsp {


#if 0
#pragma mark --- CoreTraits-Impl ---
#endif // 0
#if 1

struct CoreDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_CORE_CUSTOM_TRAITS

using CoreTraits = CoreDefaultTraits_T;

#else

#endif // 

#endif

}
