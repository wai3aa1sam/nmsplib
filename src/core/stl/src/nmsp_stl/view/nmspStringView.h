#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspStringView_Std.h"

	namespace nmsp {


	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspStringView_Nmsp.h"

	namespace nmsp {

	}


#elif NMSP_STL_BUILD_CONTAINER_EASTL

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

#if 0
#pragma mark --- toStrView-Impl ---
#endif // 0
#if 1

inline 
StrViewA_T toStrView(const char* str)
{
	return str ? StrViewA_T{str, strlen(str)} : StrViewA_T{};
}

template<size_t N> inline
StrViewA_T toStrView(char (&str)[N])
{
	return N ? StrView_T{str, N} : StrView_T{};
}

inline 
StrViewA_T toStrView(const std::string& str)
{
	return StrViewA_T{ str.c_str(), str.size() };
}

inline 
StrViewW_T toStrViewW(const wchar_t* str)
{
	return str ? StrViewW_T{str, wcslen(str)} : StrViewW_T{};
}

template<size_t N> inline
StrViewW_T toStrViewW(wchar_t (&str)[N])
{
	return N ? StrViewW_T{str, N} : StrViewW_T{};
}

inline 
StrViewW_T toStrViewW(const std::wstring& str)
{
	return StrViewW_T{ str.c_str(), str.size() };
}

#endif // 1


void onFormat(fmt::format_context& ctx, const StrViewA_T& v);
void onFormat(fmt::format_context& ctx, const StrViewW_T& v);

}

NMSP_FORMATTER(StrViewA_T);
NMSP_FORMATTER(StrViewW_T);