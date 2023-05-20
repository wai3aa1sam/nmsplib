#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspList_Std.h"

	namespace nmsp {

	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using List_Impl	= List_Std<T, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspList_Nmsp.h"

	namespace nmsp {

	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using List_Impl = List_Nmsp<T, N, FALLBACK_ALLOC>;

	}

	
#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspList_Eastl.h"

	namespace nmsp {
	
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using List_Impl	= List_Eastl<T, N, FALLBACK_ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using List_T	= List_Impl<T, N, FALLBACK_ALLOC>;

}