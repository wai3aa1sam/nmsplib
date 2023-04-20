#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER

	#include "std/nmspVector_Std.h"

	namespace nmsp {

	template<class T, class ALLOC>												using IVector_Impl	= Vector_Std<T, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl	= Vector_Std<T, ALLOC>;

	}

#elif NMSP_STL_BUILD_NMSP_CONTAINER

	#include "nmsp/nmspVector_Nmsp.h"

	namespace nmsp {
	
	#if NMSP_STL_ENABLE_IVECTOR
		template<class T, class ALLOC> using IVector_Impl = IVector_Nmsp<T, ALLOC>;
	#else
		template<class T, class ALLOC> using IVector_Impl = Vector_Nmsp<T, 0, ALLOC>;
	#endif // NMSP_STL_ENABLE_IVECTOR

	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl = Vector_Nmsp<T, N, FALLBACK_ALLOC>;

	}

	
#elif NMSP_STL_BUILD_EASTL_CONTAINER

	#include "eastl/nmspVector_Eastl.h"

	namespace nmsp {
	
	template<class T, class ALLOC>												using IVector_Impl	= Vector_Eastl<T, 0, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl	= Vector_Eastl<T, N, FALLBACK_ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T, class ALLOC = DefaultAllocator>							using IVector_T	= IVector_Impl<T, ALLOC>;
template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_T	= Vector_Impl<T, N, FALLBACK_ALLOC>;

}