#pragma once

#include <nmsp_test_base/common/nmsp_test_base_traits.h>
#include "nmsp_core_test-config.h"

namespace nmsp {

#if 0
#pragma mark --- CoreTestTraits-Impl ---
#endif // 0
#if 1
struct CoreTestDefaultTraits_T : public TestBaseTraits
{
	
};


#if !NMSP_CORE_TEST_CUSTOM_TRAITS

using CoreTestTraits = CoreTestDefaultTraits_T;

#else

#endif // 

#endif

}
