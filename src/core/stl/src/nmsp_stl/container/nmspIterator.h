#pragma once

#include "../common/nmsp_stl_common.h"

#if NMSP_STL_BUILD_STD

	#include <iterator>

#elif NMSP_STL_BUILD_NMSP

	#include "nmsp/nmspIterator_Nmsp.h"
	
#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspIterator_Eastl.h"

	namespace nmsp {
	
	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

namespace nmsp {



}