#pragma once

#include "nmspContainer_Common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspString_Std.h"

	namespace nmsp {

	template<class T, class ALLOC = DefaultAllocator>				using IString_Impl	= String_Std<T, ALLOC>;
	template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_Impl	= String_Std<T, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspString_Nmsp.h"

	namespace nmsp {

	template<class T, class ALLOC = DefaultAllocator>				using IString_Impl	= String_Nmsp<T, 0, ALLOC>;
	template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_Impl	= String_Nmsp<T, N, ALLOC>;

	}

#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspString_Eastl.h"

	namespace nmsp {
	
	template<class T, class ALLOC>												using IString_Impl	= String_Eastl<T, 0, ALLOC>;
	template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using String_Impl	= String_Eastl<T, N, FALLBACK_ALLOC>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T, class ALLOC = DefaultAllocator>				using IString_T = IString_Impl<T, ALLOC>;
template<class T, size_t N = 0, class ALLOC = DefaultAllocator>	using String_T	=  String_Impl<T, N, ALLOC>;

template<size_t N = 0, class ALLOC = DefaultAllocator> using StringA_T = String_T<char,	N, ALLOC>;
template<size_t N = 0, class ALLOC = DefaultAllocator> using StringW_T = String_T<wchar_t,	N, ALLOC>;

template<class CHAR, class ALLOC = DefaultAllocator> 
struct StringInfo_T 
{ 
	using Type = String_T<CHAR, 0, ALLOC>;  
	static constexpr size_t s_kSize			= sizeof(Type); 
	static constexpr size_t s_kTempStrSize	= 256 - s_kSize; 
};
template<class ALLOC = DefaultAllocator> using StringAInfo_T = StringInfo_T<char,	 ALLOC>;
template<class ALLOC = DefaultAllocator> using StringWInfo_T = StringInfo_T<wchar_t, ALLOC>;

template<class CHAR, class ALLOC = DefaultAllocator>	using TempString_T	= String_T<CHAR, StringInfo_T<CHAR, ALLOC>::s_kTempStrSize, ALLOC>;
template<class ALLOC = DefaultAllocator>				using TempStringA_T = TempString_T<char,	ALLOC>;
template<class ALLOC = DefaultAllocator>				using TempStringW_T = TempString_T<wchar_t, ALLOC>;

using StringT	= StringA_T<0>;
using StringWT	= StringW_T<0>;


template<class T, size_t N, class ALLOC>
void onFormat(fmt::format_context& ctx, const String_T<T, N, ALLOC>& v)
{
	formatTo(ctx, "{}", v.view());

	/*if constexpr (IsSame<T, char>)
	{
		formatTo(ctx, "{}", v.view());
	}
	else if constexpr (IsSame<T, wchar_t>)
	{
		formatTo(ctx, L"{}", v.view());
	}
	else
	{
		throw "invalid char type";
	}*/
}
NMSP_FORMATTER_T(NMSP_ARGS(class T, size_t N, class ALLOC), String_T<NMSP_ARGS(T, N, ALLOC)> );

}


