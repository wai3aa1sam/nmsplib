#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/string.h>
#include <EASTL/fixed_string.h>

#if 0
#pragma mark --- String_Eastl-Decl ---
#endif // 0
#if 1

namespace nmsp {

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

private:

};

}


#endif