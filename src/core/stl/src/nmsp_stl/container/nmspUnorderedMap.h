#pragma once

#include "nmspContainer_Common.h"
#include "nmsp_stl/extra/nmspPair.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "std/nmspUnorderedMap_Std.h"

namespace nmsp {

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_Impl = UnorderedMap_Std<KEY, VALUE, HASH, PRED, ALLOC>;

}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspUnorderedMap_Nmsp.h"

namespace nmsp {

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_Impl = UnorderedMap_Nmsp<KEY, VALUE, HASH, PRED, ALLOC>;

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspUnorderedMap_Eastl.h"

namespace nmsp {

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_Impl = UnorderedMap_Eastl<KEY, VALUE, HASH, PRED, ALLOC>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_T = UnorderedMap_Impl<KEY, VALUE, HASH, PRED, ALLOC>;

}