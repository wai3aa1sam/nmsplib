#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

	#include "std/String_Std.h"

	namespace nmsp {

	template<class T, class ALLOC = DefaultAllocator>				using IString_Impl	= String_Std<T, ALLOC>;
	template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_Impl	= String_Std<T, ALLOC>;

	}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

	#include "nmsp/nmspString_Nmsp.h"

	namespace nmsp {

	template<class T, class ALLOC = DefaultAllocator>				using IString_Impl	= String_Nmsp<T, 0, ALLOC>;
	template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_Impl	= String_Nmsp<T, N, ALLOC>;

	}

#elif NMSP_BUILD_STL_EASTL_CONTAINER

	#include "eastl/nmspString_Eastl.h"

	namespace nmsp {
	
	template<class T, class ALLOC>												using IString_Impl	= String_Eastl<T, 0, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using String_Impl	= String_Eastl<T, N, FALLBACK_ALLOC>;

	}

#else
	#error "unsupported stl build"
#endif // 0


namespace nmsp {

template<class T, class ALLOC = DefaultAllocator>				using IString_T = IString_Impl<T, ALLOC>;
template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_T	= String_Impl<T, N, ALLOC>;

}