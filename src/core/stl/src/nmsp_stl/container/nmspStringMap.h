#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "std/nmspStringMap_Std.h"

namespace nmsp {

template<class VALUE, class PRED = StrLess<VALUE>, class ALLOC = DefaultAllocator> using StringMap_Impl = StringMap_Std<VALUE, PRED, ALLOC>;

}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspStringMap_Nmsp.h"

namespace nmsp {

template<class VALUE, class PRED = StrLess<const char*>, class ALLOC = DefaultAllocator> using StringMap_Impl = StringMap_Nmsp<VALUE, PRED, ALLOC>;

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspStringMap_Eastl.h"

namespace nmsp {

template<class VALUE, class PRED = StrLess<const char*>, class ALLOC = DefaultAllocator> using StringMap_Impl = StringMap_Eastl<VALUE, PRED, ALLOC>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class VALUE, class PRED = StrLess<const char*>, class ALLOC = DefaultAllocator> using StringMap_T	= StringMap_Impl<VALUE, PRED, ALLOC>;

}