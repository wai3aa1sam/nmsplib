#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

#if 0
#pragma mark --- Vector_Eastl-Decl ---
#endif // 0
#if 1

namespace nmsp {

template<class T, size_t N, bool bEnableOverflow = true, class OverflowAllocator = DefaultAllocator>
struct EASTL_Vector
{
	using Type = eastl::fixed_vector<T, N, bEnableOverflow, OverflowAllocator>;
};

template<class T, class OverflowAllocator>
struct EASTL_Vector<T, 0, true, OverflowAllocator>
{
	using Type = eastl::vector<T, OverflowAllocator>;
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

}


#endif