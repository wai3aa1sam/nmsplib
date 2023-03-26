#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD

	#include "std/String_Std.h"

	namespace nmsp {

	template<class T, size_t N = 0, class ALLOC = MallocAllocator>	using String_Impl	= String_Std<T, ALLOC>;
	template<class T, class ALLOC = MallocAllocator>				using IString_Impl	= String_Std<T, ALLOC>;

	}

#elif NMSP_BUILD_STL_NMSP

	#include "nmsp/String_Nmsp.h"

	namespace nmsp {

	template<class T, size_t N = 0, class ALLOC = MallocAllocator>	using String_Impl	= String_Nmsp<T, N, ALLOC>;
	template<class T, class ALLOC = MallocAllocator>				using IString_Impl	= String_Nmsp<T, 0, ALLOC>;

	}

#else
	#error "unsupported stl build"
#endif // 0


namespace nmsp {

template<class T, size_t N = 0, class ALLOC = MallocAllocator>	using String_T	= String_Impl<T, N, ALLOC>;
template<class T, class ALLOC = MallocAllocator>				using IString_T = IString_Impl<T, ALLOC>;

}