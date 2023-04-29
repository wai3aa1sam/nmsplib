#pragma once

#include "nmspContainer_Common.h"
#include "nmsp_stl/extra/nmspPair.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspUnorderedMap_Std.h"

	namespace nmsp {

	template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
	using UnorderedMap_Impl = UnorderedMap_Std<KEY, VALUE, HASH, PRED, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspUnorderedMap_Nmsp.h"

	namespace nmsp {

	template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
	using UnorderedMap_Impl = UnorderedMap_Nmsp<KEY, VALUE, HASH, PRED, ALLOC>;

	}


#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspUnorderedMap_Eastl.h"

	namespace nmsp {

	template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
	using UnorderedMap_Impl = UnorderedMap_Eastl<KEY, VALUE, HASH, PRED, ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_T = UnorderedMap_Impl<KEY, VALUE, HASH, PRED, ALLOC>;

}