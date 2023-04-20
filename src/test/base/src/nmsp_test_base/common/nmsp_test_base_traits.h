#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_test_base-config.h"

namespace nmsp {

#if 0
#pragma mark --- TestBaseTraits-Impl ---
#endif // 0
#if 1
struct TestBaseDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_TEST_BASE_CUSTOM_TRAITS

using TestBaseTraits = TestBaseDefaultTraits_T;

#else

#endif // 

#endif

}

