#pragma once

#include "nmspContainer_Common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "std/nmspSet_Std.h"

namespace nmsp {

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Std<KEY, PRED, ALLOC>;

}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspSet_Nmsp.h"

namespace nmsp {

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Nmsp<KEY, PRED, ALLOC>;

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspSet_Eastl.h"

namespace nmsp {

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Impl = Set_Eastl<KEY, PRED, ALLOC>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>	using Set_T	= Set_Impl<KEY, PRED, ALLOC>;

}