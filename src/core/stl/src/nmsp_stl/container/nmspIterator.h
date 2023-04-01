#pragma once

#include "../common/nmsp_stl_common.h"

#if NMSP_BUILD_STL_STD

	#include <iterator>

#elif NMSP_BUILD_STL_NMSP

	#include "nmsp/nmspIterator_Nmsp.h"
	
#elif NMSP_BUILD_STL_EASTL_CONTAINER

	#include "eastl/nmspIterator_Eastl.h"

	namespace nmsp {
	
	}

#else
	#error "unsupported stl build"
#endif // 0

namespace nmsp {



}