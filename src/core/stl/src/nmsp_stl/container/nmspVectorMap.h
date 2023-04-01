#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "std/nmspVectorMap_Std.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl	= VectorMap_Std<KEY, VALUE, PRED, ALLOC>;

}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspVectorMap_Nmsp.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl = VectorMap_Nmsp<KEY, VALUE, PRED, ALLOC>;

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspVectorMap_Eastl.h"

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Impl	= VectorMap_Eastl<KEY, VALUE, PRED, ALLOC>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_T = VectorMap_Impl<KEY, VALUE, PRED, ALLOC>;

}