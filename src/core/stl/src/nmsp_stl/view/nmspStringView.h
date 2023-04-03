#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "nmsp/nmspStringView_Std.h"

namespace nmsp {


}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspStringView_Nmsp.h"

namespace nmsp {

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspStringView_Eastl.h"

namespace nmsp {

template<class T> using StrView_Impl = StrView_Eastl<T>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class T> using StrView_T = StrView_Impl<T>;

using StrViewA_T = StrView_T<char>;
using StrViewW_T = StrView_T<wchar_t>;

inline StrViewA_T c_strToStrView(const char* str)
{
	return str ? StrViewA_T{str, strlen(str)} : StrViewA_T{};
}

}