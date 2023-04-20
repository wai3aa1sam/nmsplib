#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_math-config.h"

namespace nmsp {

#if 0
#pragma mark --- ProfilerTraits-Impl ---
#endif // 0
#if 1
struct MathDefaultTraits_T : public CoreBaseTraits
{
	using SizeType	= size_t;
	using IndexType = i32;
};


#if !NMSP_MATH_CUSTOM_TRAITS

using MathTraits = MathDefaultTraits_T;

#else

#endif // 

#endif

}
