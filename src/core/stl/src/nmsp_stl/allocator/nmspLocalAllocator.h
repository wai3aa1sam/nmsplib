#pragma once

#include "nmspAllocator_Common.h"
#include "nmspAlloctorType.h"
#include "nmspLocalBuffer.h"
#include "nmspMallocAllocator.h"

namespace nmsp {

#if 0
#pragma mark --- LocalAllocator_T-Impl ---
#endif // 0
#if 1

template<size_t LOCAL_SIZE = 0, size_t ALIGN = NmspTraits::s_kDefaultAlign, size_t OFFSET = 0, class FALLBACK_ALLOC = MallocAllocator_T<ALIGN> >
class LocalAllocator_T : public FallbackAllocator_T<LocalBuffer_T<LOCAL_SIZE, ALIGN>, FALLBACK_ALLOC >
{
public:
	using LocalBuffer	= LocalBuffer_T<LOCAL_SIZE, ALIGN>;
	using Base			= FallbackAllocator_T<LocalBuffer, FALLBACK_ALLOC >;
	using This			= LocalAllocator_T<LOCAL_SIZE, ALIGN, OFFSET, FALLBACK_ALLOC>;

public:
	using SizeType			= size_t;
	using FallbackAllocator = FALLBACK_ALLOC;

	static constexpr SizeType s_kLocalSize			= LOCAL_SIZE;
	static constexpr SizeType s_kAlign				= ALIGN;
	//static constexpr bool	  s_enableFallbackAlloc = Base::s_enableFallbackAlloc;

	//static_assert(Base::s_kPrimaryAlign == Base::s_kFallBackAlign);

public:
	LocalAllocator_T(const char* name = "LocalAllocator_T") {};
	~LocalAllocator_T() = default;

	void*	alloc(SizeType n)			{ return Base::alloc(n); }
	void	free(void* p, SizeType n)	{ Base::free(p, n); }

	bool	isUsingLocalBuf(void* p)	{ return first().isUsingLocalBuffer(p); }

private:
	//void* _pOverflowData = nullptr;
};

//template<typename T>
//class LocalAllocator_T<T, 0> : public LocalBuffer_T<0>
//{
//public:
//	using SizeType = size_t;
//	using ValueType = T;
//
//public:
//	using Base = LocalBuffer_T<0>;
//
//public:
//	void*	alloc(SizeType n)			{ return Base::alloc(); }
//	void	free(void* p, SizeType n)	{}
//private:
//};

#endif

}