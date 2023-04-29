#pragma once

#include "nmspContainer_Common.h"
#include "nmsp_stl/extra/nmspPair.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspMap_Std.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl	= Map_Std<KEY, VALUE, PRED, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspMap_Nmsp.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl = Map_Nmsp<KEY, VALUE, PRED, ALLOC>;

	}


#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspMap_Eastl.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl	= Map_Eastl<KEY, VALUE, PRED, ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_T = Map_Impl<KEY, VALUE, PRED, ALLOC>;

}