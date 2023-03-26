#pragma once

#include "nmspAllocator_Common.h"
#include "../extra/nmspCompressedPair.h"

/*
references:
- CppCon 2015: Andrei Alexandrescu “std::allocator...” - YouTube (https://www.youtube.com/watch?v=LIb3L4vKZ7U)

*/


namespace nmsp {

#if 0
#pragma mark --- FallbackAllocator_T-Decl
#endif // 0
#if 1

class NoFallbackAllocator_Policy {};

template<class PRIMARY_ALLOC, class FALLBACK_ALLOC = NoFallbackAllocator_Policy>
class FallbackAllocator_T : protected Allocator_Base< CompressedPair<PRIMARY_ALLOC, FALLBACK_ALLOC> >
{
public:
	using Base = CompressedPair<PRIMARY_ALLOC, FALLBACK_ALLOC>;
	using This = FallbackAllocator_T<PRIMARY_ALLOC, FALLBACK_ALLOC>;
public:
	using PrimaryAllocator	= PRIMARY_ALLOC;
	using FallbackAllocator = FALLBACK_ALLOC;


	using SizeType = typename PrimaryAllocator::SizeType;

	//static constexpr SizeType s_kPrimaryAlign	= PRIMARY_ALLOC::s_kAlign;
	//static constexpr SizeType s_kFallbackAlign	= FALLBACK_ALLOC::s_kAlign;

	static constexpr bool s_enableFallbackAlloc = !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>;
	
public:
	static_assert(!s_enableFallbackAlloc || IsSame<typename PRIMARY_ALLOC::SizeType, typename FALLBACK_ALLOC::SizeType>);

public:
	void* alloc(SizeType n, SizeType align = s_kDefaultAlign, SizeType offset = 0);
	void* alloc_all(SizeType n);

	void free(void* p, SizeType n);
	void free_all();

	bool is_owning(void* p, SizeType n);

public:
	using Base::first;
	using Base::second;

};

#endif

#if 0
#pragma mark --- FallbackAllocator_T-Impl ---
#endif // 0
#if 1

template<class P, class F> inline
void* FallbackAllocator_T<P, F>::alloc(SizeType n, SizeType align, SizeType offset)
{
	auto* p = first().alloc(n, align, offset);
	if (p)
		return p;
	p = second().alloc(n, align, offset);
	return p;
}

template<class P, class F> inline
void* FallbackAllocator_T<P, F>::alloc_all(SizeType n)
{
	NMSP_ASSERT(false);
}

template<class P, class F> inline
void FallbackAllocator_T<P, F>::free(void* p, SizeType n)
{
	if (first().is_owning(p, n))
		return first().free(p, n);

	if (second().is_owning(p, n))
		return second().free(p, n);

	NMSP_ASSERT(false);
}

template<class P, class F> inline
void  FallbackAllocator_T<P, F>::free_all()
{
	NMSP_ASSERT(false);
}

template<class P, class F> inline
bool  FallbackAllocator_T<P, F>::is_owning(void* p, SizeType n)
{
	return first().is_owning(p, n) || second().is_owning(p, n);
}

#endif

}