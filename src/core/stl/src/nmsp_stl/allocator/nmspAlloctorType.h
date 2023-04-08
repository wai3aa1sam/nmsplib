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

class EmptyAllocator : public Allocator_Base<EmptyAllocator> 
{
public:
	using This = Allocator_Base<EmptyAllocator>;
public:
	using SizeType = size_t;

public:
	EmptyAllocator(const char* name = "EmptyAllocator") {};
	~EmptyAllocator()	= default;

	void* alloc(SizeType n, SizeType align = NmspTraits::s_kDefaultAlign, SizeType offset = 0)	{ return nullptr; }
	void* alloc_all(SizeType n)																	{ return nullptr; }

	void free(void* p, SizeType n = 0)	{}
	void free_all()						{}

	bool is_owning(void* p, SizeType n) { return false; }

	bool operator==(const EmptyAllocator& rhs) { return true;}
	bool operator!=(const EmptyAllocator& rhs) { return false;}
private:
};
using NoFallbackAllocator_Policy = EmptyAllocator;

template<class PRIMARY_ALLOC, class FALLBACK_ALLOC = NoFallbackAllocator_Policy>
class FallbackAllocator_T : public Allocator_Base<FallbackAllocator_T<PRIMARY_ALLOC, FALLBACK_ALLOC > >
{
public:
	//using Base = CompressedPair<PRIMARY_ALLOC, FALLBACK_ALLOC>;
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
	FallbackAllocator_T(const char* name = "FallbackAllocator_T") {}
	~FallbackAllocator_T() = default;

	void* alloc(SizeType n, SizeType align = s_kDefaultAlign, SizeType offset = 0);
	void* alloc_all(SizeType n);

	void free(void* p, SizeType n);
	void free_all();

	bool is_owning(void* p, SizeType n);

public:
	//using Base::first;
	//using Base::second;

	CompressedPair<PRIMARY_ALLOC, FALLBACK_ALLOC> _pair;
};

#endif

#if 0
#pragma mark --- FallbackAllocator_T-Impl ---
#endif // 0
#if 1

template<class P, class F> inline
void* FallbackAllocator_T<P, F>::alloc(SizeType n, SizeType align, SizeType offset)
{
	auto& f = _pair.first();
	auto* p = f.alloc(n, align, offset);
	if (p)
		return p;

	auto& s = _pair.second();
	p		= s.alloc(n, align, offset);
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
	auto& f = _pair.first();
	if (f.is_owning(p, n))
		return f.free(p, n);

	auto& s = _pair.second();
	if (s.is_owning(p, n))
		return s.free(p, n);

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
	auto& f	= _pair.first();
	auto& s	= _pair.second();
	return f.is_owning(p, n) || s.is_owning(p, n);
}

#endif

}