#pragma once

#include "nmspAllocator_Common.h"
#include "nmspLocalBuffer.h"

namespace nmsp {

#if 0
#pragma mark --- VectorAllocator_T-Impl
#endif // 0
#if 1

template<typename T, size_t COUNT, size_t ALIGN = s_kDefaultAlign, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOCATOR = DefaultAllocator_T<ALIGN>>
class VectorAllocator_T : public LocalBuffer_T<COUNT * sizeof(T), ALIGN, ENABLE_FALLBACK_ALLOC, FALLBACK_ALLOCATOR>
{
public:
	using SizeType			= size_t;
	using ValueType			= T;
	using FallbackAllocator = FALLBACK_ALLOCATOR;

	static constexpr SizeType s_kLocalSize			= COUNT * sizeof(T);
	static constexpr SizeType s_kAlign				= ALIGN;
	static constexpr bool	  s_enableFallbackAlloc = ENABLE_FALLBACK_ALLOC;

public:
	using Base = LocalBuffer_T<s_kLocalSize, s_kAlign, ENABLE_FALLBACK_ALLOC, FallbackAllocator>;
	using This = VectorAllocator_T<T, s_kLocalSize, s_kAlign, s_enableFallbackAlloc, FallbackAllocator>;

public:
	T*		alloc(SizeType n)			{ return reinCast<T*>(Base::alloc(n)); }
	void	free(void* p, SizeType n)	{ Base::free(p, n); }

private:
	//void* _pOverflowData = nullptr;
};

template<typename T>
class VectorAllocator_T<T, 0> : public LocalBuffer_T<0>
{
public:
	using SizeType = size_t;
	using ValueType = T;

public:
	using Base = LocalBuffer_T<0>;

public:
	void*	alloc(SizeType n)			{ return Base::alloc(); }
	void	free(void* p, SizeType n)	{}
private:
};

#endif

}