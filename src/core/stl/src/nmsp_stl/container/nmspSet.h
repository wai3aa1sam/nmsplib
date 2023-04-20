#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER

	#include "std/nmspSet_Std.h"

	namespace nmsp {

	template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Std<KEY, PRED, ALLOC>;

	}

#elif NMSP_STL_BUILD_NMSP_CONTAINER

	#include "nmsp/nmspSet_Nmsp.h"

	namespace nmsp {

	template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Nmsp<KEY, PRED, ALLOC>;

	}

#elif NMSP_STL_BUILD_EASTL_CONTAINER

	#include "eastl/nmspSet_Eastl.h"

	namespace nmsp {

	template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Eastl<KEY, PRED, ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>	using Set_T	= Set_Impl<KEY, PRED, ALLOC>;

}