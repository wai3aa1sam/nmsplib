#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD

	#include "std/Vector_Std.h"

	namespace nmsp {

	template<class T, class ALLOCATOR> using IVector_Impl = Vector_Std<T, ALLOCATOR>;
	template<class T, size_t N = 0, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOCATOR = DefaultAllocator>
	using Vector_Impl = Vector_Std<T, ALLOCATOR>;

	}

#elif NMSP_BUILD_STL_NMSP

	#include "nmsp/Vector_Nmsp.h"

	namespace nmsp {
	
	template<class T, class ALLOCATOR> using IVector_Impl = IVector_Nmsp<T, ALLOCATOR>;
	template<class T, size_t N = 0, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOCATOR = DefaultAllocator>	
	using Vector_Impl = Vector_Nmsp<T, N, ENABLE_FALLBACK_ALLOC, FALLBACK_ALLOCATOR>;

	}

#else
	#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class T, class ALLOCATOR = DefaultAllocator> using IVector_T = IVector_Impl<T, ALLOCATOR>;
template<class T, size_t N = 0, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOCATOR = DefaultAllocator> 
using Vector_T = Vector_Impl<T, N, ENABLE_FALLBACK_ALLOC, FALLBACK_ALLOCATOR>;

}