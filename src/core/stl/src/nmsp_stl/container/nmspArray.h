#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspArray_Std.h"

	namespace nmsp {

	template<class T, class ALLOC>												using IArray_Impl	= Array_Std<T, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Array_Impl	= Array_Std<T, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspArray_Nmsp.h"

	namespace nmsp {
	
	#if NMSP_STL_ENABLE_IVECTOR
		template<class T, class ALLOC> using IArray_Impl = IArray_Nmsp<T, ALLOC>;
	#else
		template<class T, class ALLOC> using IArray_Impl = Array_Nmsp<T, 0, ALLOC>;
	#endif // NMSP_STL_ENABLE_IVECTOR

	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using Array_Impl = Array_Nmsp<T, N, FALLBACK_ALLOC>;

	}

	
#elif NMSP_STL_BUILD_CONTAINER_EASTL

	//#include "eastl/nmspArray_Eastl.h"
	#include <EASTL/array.h>

	namespace nmsp {

	template<class T, size_t N = 0> using Array_Impl	= eastl::array<T, N>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T, size_t N = 0>
class Array_T : public Array_Impl<T, N>
{
	template<T... VALS>
	constexpr Array_T()
	{
		//Array_T 
	}
};

}