#pragma once

#include <nmsp_core_base/common/nmspNmspTraits.h>

namespace nmsp {

struct NmspMathDefaultTraits_T : public NmspTraits
{
	using SizeType	= size_t;
	using IndexType = i32;
};


#if !NMSP_MATH_CUSTOM_TRAITS

using NmspMathTraits = NmspMathDefaultTraits_T;

#else

#endif // 

}
