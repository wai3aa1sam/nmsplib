#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER

	#include "std/nmspVectorMap_Std.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl = VectorMap_Std<KEY, VALUE, PRED, ALLOC>;

	}

#elif NMSP_STL_BUILD_NMSP_CONTAINER

	#include "nmsp/nmspVectorMap_Nmsp.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl = VectorMap_Nmsp<KEY, VALUE, PRED, ALLOC>;

	}


#elif NMSP_STL_BUILD_EASTL_CONTAINER

	#include "eastl/nmspVectorMap_Eastl.h"

	namespace nmsp {

	template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl = VectorMap_Eastl<KEY, VALUE, PRED, ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_T = VectorMap_Impl<KEY, VALUE, PRED, ALLOC>;

}