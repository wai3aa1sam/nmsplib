#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER

	#include "std/nmspStringView_Std.h"

	namespace nmsp {


	}

#elif NMSP_STL_BUILD_NMSP_CONTAINER

	#include "nmsp/nmspStringView_Nmsp.h"

	namespace nmsp {

	}


#elif NMSP_STL_BUILD_EASTL_CONTAINER

	#include "eastl/nmspStringView_Eastl.h"

	namespace nmsp {

	template<class T> using StrView_Impl = StrView_Eastl<T>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T> using StrView_T = StrView_Impl<T>;

using StrViewA_T = StrView_T<char>;
using StrViewW_T = StrView_T<wchar_t>;

inline StrViewA_T c_strToStrView(const char* str)
{
	return str ? StrViewA_T{str, strlen(str)} : StrViewA_T{};
}

}