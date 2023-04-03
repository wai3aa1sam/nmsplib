#pragma once

#include "../nmspContainer_Common.h"
#include "nmsp_stl/view/nmspStringView.h"

#include <EASTL/string.h>
#include <EASTL/fixed_string.h>

namespace nmsp {

#if 0
#pragma mark --- String_Eastl-Decl ---
#endif // 0
#if 1

template<class T, size_t N, bool bEnableOverflow, class OverflowAllocator>
struct EASTL_String
{
	using Type = eastl::fixed_string<T, N, bEnableOverflow, OverflowAllocator>;
};

template<class T, class Allocator>
struct EASTL_String<T, 0, true, Allocator>
{
	using Type = eastl::basic_string<T, Allocator>;
};

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class String_Eastl : public EASTL_String<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type
{
public:
	using Base = typename EASTL_String<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type;

	using ViewType	= StrView_T<T>;
	using Allocator = FALLBACK_ALLOC;

public:
	String_Eastl() = default;
	~String_Eastl() = default;

	explicit String_Eastl(ViewType sv, const Allocator& allocator = DefaultAllocator{});

private:

};



#endif


#if 0
#pragma mark --- String_Eastl-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class FALLBACK_ALLOC> inline
String_Eastl<T, N, FALLBACK_ALLOC>::String_Eastl(ViewType sv, const Allocator& allocator)
	: Base(sv, allocator)
{}



#endif

}
