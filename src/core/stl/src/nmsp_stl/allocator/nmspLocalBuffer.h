#pragma once

#include "nmspAllocator_Common.h"
#include "nmspMallocAllocator.h"
#include "../extra/nmspCompressedPair.h"

namespace nmsp {

template<size_t LOCAL_SIZE, size_t ALIGN> class LocalBuffer_Base;
template<size_t LOCAL_SIZE, size_t ALIGN = s_kDefaultAlign> using LocalBuffer_T = LocalBuffer_Base<LOCAL_SIZE, ALIGN>;

#if 0
#pragma mark --- LocalBuffer_Base-Impl ---
#endif // 0
#if 1

template<size_t LOCAL_SIZE, size_t ALIGN = s_kDefaultAlign>
class LocalBuffer_Base
{
public:
	using LocalBufferType = typename std::aligned_storage<LOCAL_SIZE, ALIGN>::type;
	using SizeType = size_t;

	static constexpr SizeType s_kLocalSize	= LOCAL_SIZE;
	static constexpr SizeType s_kAlign		= ALIGN;

public:
	using This = LocalBuffer_Base<s_kLocalSize, s_kAlign>;

public:
	NMSP_NODISCARD void* alloc(SizeType n, SizeType align = s_kAlign, SizeType offset = 0) NMSP_NOEXCEPT
	{
		//NMSP_ASSERT(n <= s_kLocalSize, "LocalBuffer_Base n: {} > s_kLocalSize: {}", n, LOCAL_SIZE);
		if (n > s_kLocalSize)
			return nullptr;
		return &_buf;
	}

	void free(void* p, SizeType n) NMSP_NOEXCEPT
	{

	}

			void* data()		{ return &_buf; }
	const	void* data() const	{ return &_buf; }

	//bool is_owning(void* p, SizeType size) const	{ return p >= reinCast<const char*>(data()) && p < reinCast<const char*>(data()) + s_kLocalSize; }
	bool is_owning(void* p, SizeType size) const	{ return isUsingLocalBuf(p); }
	bool isUsingLocalBuf(void* p) const				{ return p == data(); }

	//void clear()			{ ::memset(&_buf, 0, n);  /* TODO: our impl for memset(like memcpy)*/ }
	//bool isEmpty() const	{ return &_buf == nullptr; }
private:
	LocalBufferType _buf;
};

template<size_t ALIGN>
class LocalBuffer_Base<0, ALIGN>
{
public:
	using LocalBufferType = void;
	using SizeType = size_t;

	static constexpr SizeType s_kLocalSize = 0;
	static constexpr SizeType s_kAlign = 0;

public:
	using This = LocalBuffer_Base<s_kLocalSize, s_kAlign>;

public:
	NMSP_NODISCARD void* alloc(SizeType n, SizeType align = s_kAlign, SizeType offset = 0)
	{
		return nullptr;
	}

	void free(void* p, SizeType n)
	{

	}

			void* data()		{ return nullptr; }
	const	void* data() const	{ return nullptr; }

	bool is_owning(void* p, SizeType size) const	{ return false; }
	bool isUsingLocalBuf(void* p) const				{ return false; }

	//void clear()			{ ::memset(&_buf, 0, n);  /* TODO: our impl for memset(like memcpy)*/ }
	//bool isEmpty() const	{ return &_buf == nullptr; }
};

#endif

#if 0
#pragma mark --- LocalBuffer_T-Impl ---
#endif // 0
#if 0

template<size_t LOCAL_SIZE, size_t ALIGN = s_kDefaultAlign, bool ENABLE_FALLBACK_ALLOC = true, class FALLBACK_ALLOC = MallocAllocator>
class LocalBuffer_T
{
public:
	using LocalBufferType = LocalBuffer_Base<LOCAL_SIZE, ALIGN>;
	using SizeType = size_t;
	using FallbackAllocator = FALLBACK_ALLOC;

	static constexpr SizeType s_kLocalSize			= LOCAL_SIZE;
	static constexpr SizeType s_kAlign				= ALIGN;
	static constexpr bool	  s_enableFallbackAlloc = ENABLE_FALLBACK_ALLOC;
	//static constexpr bool	  s_isAllocator			= IS_ALLOC;

public:
	using This = LocalBuffer_T<s_kLocalSize, s_kAlign, s_enableFallbackAlloc, FallbackAllocator>;
public:
	LocalBuffer_T()		= default;
	~LocalBuffer_T()	= default;

	NMSP_NODISCARD void* alloc(SizeType n)
	{
		auto& localBuf = _pair.first();

		if constexpr (s_enableFallbackAlloc)
		{
			auto& fallbackAllocator = _pair.second();
			if (n > s_kLocalSize)
				return fallbackAllocator.alloc(n);
		}
		return localBuf.alloc(n);
	}

	void free(void* p, SizeType n)
	{
		NMSP_ASSERT(!isUsingLocalBuffer(p), "cannot free local buffer pointer");

		if constexpr (s_enableFallbackAlloc)
		{
			auto& fallbackAllocator = _pair.second();
			fallbackAllocator.free(p, n);
		}
	}

	bool isUsingLocalBuffer(void* p) const { auto& localBuf = _pair.first(); return localBuf.isUsingLocalBuffer(p); }

private:
	CompressedPair<LocalBufferType, FALLBACK_ALLOC> _pair;
};

template<size_t LOCAL_SIZE, size_t ALIGN>
class LocalBuffer_T<LOCAL_SIZE, ALIGN, false> : public LocalBuffer_Base<LOCAL_SIZE, ALIGN>
{
public:
	using LocalBufferType	= LocalBuffer_Base<LOCAL_SIZE, ALIGN>;
	using SizeType			= size_t;

	static constexpr SizeType s_kLocalSize			= LOCAL_SIZE;
	static constexpr SizeType s_kAlign				= ALIGN;
	static constexpr bool	  s_enableFallbackAlloc = false;
	//static constexpr bool	  s_isAllocator			= IS_ALLOC;

public:
	using Base = LocalBufferType;
	using This = LocalBuffer_T<s_kLocalSize, s_kAlign, s_enableFallbackAlloc>;

public:
	LocalBuffer_T()		= default;
	~LocalBuffer_T()	= default;
};

template<> class LocalBuffer_T<0> : public LocalBuffer_Base<0, 0> {};

#endif // 0


}