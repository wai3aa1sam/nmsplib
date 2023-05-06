#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_stl-config.h"

#include <thread>

namespace nmsp {

#if 0
#pragma mark --- StlTraits-Impl ---
#endif // 0
#if 1

struct StlDefaultTraits_T : public CoreBaseTraits
{
	using SizeType	= size_t;
	using IndexType = size_t;

};

#if !NMSP_CUSTOM_STL_TRAITS

using StlTraits = StlDefaultTraits_T;

#else

#endif // 

#endif

}