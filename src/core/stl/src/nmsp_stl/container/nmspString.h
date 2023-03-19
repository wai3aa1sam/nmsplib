#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD

	#include "std/String_Std.h"

	namespace nmsp {

	template<class T, size_t N = 0, class ALLOCATOR = DefaultAllocator> using String_Impl	= String_Std<T, ALLOCATOR>;
	template<class T, class ALLOCATOR = DefaultAllocator>				using IString_Impl	= String_Std<T, ALLOCATOR>;

	}

#elif NMSP_BUILD_STL_NMSP

	#include "nmsp/String_Nmsp.h"

	namespace nmsp {

	template<class T, size_t N = 0, class ALLOCATOR = DefaultAllocator> using String_Impl	= String_Nmsp<T, N, ALLOCATOR>;
	template<class T, class ALLOCATOR = DefaultAllocator>				using IString_Impl	= String_Nmsp<T, 0, ALLOCATOR>;

	}

#else
	#error "unsupported stl build"
#endif // 0


namespace nmsp {

template<class T, size_t N = 0, class ALLOCATOR = DefaultAllocator> using String_T	= String_Impl<T, N, ALLOCATOR>;
template<class T, class ALLOCATOR = DefaultAllocator>				using IString_T = IString_Impl<T, ALLOCATOR>;

}