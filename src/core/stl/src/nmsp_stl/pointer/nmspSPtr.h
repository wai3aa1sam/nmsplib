#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "nmsp/nmspSPtr_Std.h"

namespace nmsp {


}

#elif NMSP_BUILD_STL_NMSP_CONTAINER || NMSP_STL_INTRUSIVE_S_PTR

#include "nmsp/nmspSPtr_Nmsp.h"

namespace nmsp {

template<class T> using SPtr_Impl = SPtr_Nmsp<T>;

}

#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspSPtr_Eastl.h"

namespace nmsp {

template<class T> using SPtr_Impl = SPtr_Eastl<T>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class T> using SPtr_T = SPtr_Impl<T>;

}