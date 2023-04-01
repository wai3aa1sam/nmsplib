#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

namespace nmsp {

#if 0
#pragma mark --- Vector_Eastl-Decl ---
#endif // 0
#if 1

template<class T, size_t N, bool bEnableOverflow = true, class OverflowAllocator = DefaultAllocator>
struct EASTL_Vector
{
	using Type = ::eastl::fixed_vector<T, N, bEnableOverflow, OverflowAllocator>;
};

template<class T, class Allocator>
struct EASTL_Vector<T, 0, true, Allocator>
{
	using Type = ::eastl::vector<T, Allocator>;
};

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class Vector_Eastl : public EASTL_Vector<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type
{
	using Base = typename EASTL_Vector<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type;

public:
	using ValueType = typename Base::value_type;

public:
	Vector_Eastl() = default;
	~Vector_Eastl() = default;

	Vector_Eastl(std::initializer_list<ValueType> ilist)
		: Base(ilist)
	{
	}

private:

};


#endif

}
