#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

	#include "std/Vector_Std.h"

	namespace nmsp {

	template<class T, class ALLOC>												using IVector_Impl	= Vector_Std<T, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl	= Vector_Std<T, ALLOC>;

	}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

	#include "nmsp/nmspVector_Nmsp.h"

	namespace nmsp {
	
	#if NMSP_ENABLE_IVECTOR
		template<class T, class ALLOC> using IVector_Impl = IVector_Nmsp<T, ALLOC>;
	#else
		template<class T, class ALLOC> using IVector_Impl = Vector_Nmsp<T, 0, ALLOC>;
	#endif // NMSP_ENABLE_IVECTOR

	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl = Vector_Nmsp<T, N, FALLBACK_ALLOC>;

	}

	
#elif NMSP_BUILD_STL_EASTL_CONTAINER

	#include "eastl/nmspVector_Eastl.h"

	namespace nmsp {
	
	template<class T, class ALLOC>												using IVector_Impl	= Vector_Eastl<T, 0, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_Impl	= Vector_Eastl<T, N, FALLBACK_ALLOC>;

	}

#else
	#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class T, class ALLOC = DefaultAllocator>							using IVector_T	= IVector_Impl<T, ALLOC>;
template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Vector_T	= Vector_Impl<T, N, FALLBACK_ALLOC>;

}