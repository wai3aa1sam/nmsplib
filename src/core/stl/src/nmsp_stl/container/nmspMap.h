#pragma once

#include "nmspContainer_Common.h"
#include "nmsp_stl/extra/nmspPair.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "std/nmspMap_Std.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl	= Map_Std<KEY, VALUE, PRED, ALLOC>;

}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspMap_Nmsp.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl = Map_Nmsp<KEY, VALUE, PRED, ALLOC>;

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspMap_Eastl.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Impl	= Map_Eastl<KEY, VALUE, PRED, ALLOC>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_T = Map_Impl<KEY, VALUE, PRED, ALLOC>;

}