#pragma once

#include "../common/nmsp_stl_common.h"
#include "../container/nmspIterator.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER



#elif NMSP_STL_BUILD_NMSP_CONTAINER

namespace nmsp {

#if 0
#pragma mark --- destruct_impl ---
#endif // 0
#if 1

template<class ITER, class ENABLE = void>
struct destruct_Helper
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;

	static void destruct_impl(ITER dst)
	{
		static_assert(false;)
	}

	static void destruct_impl(ITER beg, ITER end)
	{
		static_assert(false;)
	}
};

template<class ITER>
struct destruct_Helper<ITER, EnableIf<IsTrivial<typename Iter_Traits<ITER>::ValueType> > >
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;

	static void destruct_impl(ITER dst)
	{
	}

	static void destruct_impl(ITER beg, ITER end)
	{
	}
};

template<class ITER>
struct destruct_Helper<ITER, EnableIf<!IsTrivial<typename Iter_Traits<ITER>::ValueType> > >
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;

	static void destruct_impl(ITER dst)
	{
		dst->~ValueType();
	}

	static void destruct_impl(ITER beg, ITER end)
	{
		for (; beg != end; ++beg)
			beg->~ValueType();
	}
};

#endif // 1

template<class ITER> inline
void destruct(ITER dst)
{
	destruct_Helper<ITER>::destruct_impl(dst);
}

template<class ITER> inline
void destruct(ITER beg, ITER end)
{
	destruct_Helper<ITER>::destruct_impl(beg, end);
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER copy_data(OUTPUT_ITER dst, INPUT_ITER src)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	*dst = *src;
	return dst;
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER copy_data(OUTPUT_ITER out, INPUT_ITER beg, INPUT_ITER end)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	for (; beg != end; ++beg, ++out)
		*out = *beg;
	return out;
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER copy_data(OUTPUT_ITER out, INPUT_ITER beg, size_t count)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	for (; beg != beg + count; ++beg, ++out)
		*out = *beg;
	return out;
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER move_data(OUTPUT_ITER dst, INPUT_ITER src)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	*dst = move(*src);
	return dst;
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER move_data(OUTPUT_ITER out, INPUT_ITER beg, INPUT_ITER end)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	for (; beg != end; ++beg, ++out)
		*out = move(*beg);
	return out;
}

template<class OUTPUT_ITER, class INPUT_ITER> inline
OUTPUT_ITER move_data(OUTPUT_ITER out, INPUT_ITER beg, size_t count)
{
	using ValueType = typename Iter_Traits<OUTPUT_ITER>::ValueType;
	static_assert(IsSame<ValueType, typename Iter_Traits<INPUT_ITER>::ValueType>);
	for (; beg != beg + count; ++beg, ++out)
		*out = move(*beg);
	return out;
}

template<class ITER> inline
void move_construct(ITER dst, ITER src)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	new(dst) ValueType(move(*src));
}

template<class ITER> inline
void move_construct(ITER dst, ITER srcBeg, ITER srcEnd)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	for (; srcBeg != srcEnd; ++dst, ++srcBeg)
		new(dst) ValueType(move(*srcBeg));
}

template<class ITER> inline
void move_destruct(ITER dst, ITER srcBeg, ITER srcEnd)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	nmsp::move_construct(dst, srcBeg, srcEnd);
	nmsp::destruct(srcBeg, srcEnd);
}

template<class ITER> inline
void copy_construct(ITER dstBeg, ITER srcBeg, ITER srcEnd)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	for (; srcBeg != srcEnd; ++dstBeg, srcBeg++)
		new(dstBeg) ValueType(*srcBeg);
}

template<class ITER, class T> inline
void copy_construct(ITER dstBeg, const T& val, size_t count)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	static_assert(IsSame<T, ValueType>());
	auto end = dstBeg + count;
	for (; dstBeg != end; ++dstBeg)
		new(dstBeg) ValueType(val);
}

template<class ITER, class... ARGS> inline
void construct(ITER dst, ARGS&&... args)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	new(dst) ValueType(forward<ARGS>(args)...);
}

template<class ITER, class... ARGS> inline
void construct(ITER beg, ITER end, ARGS&&... args)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	for (; beg != end; ++beg)
		new(beg) ValueType(forward<ARGS>(args)...);
}

template<class ITER, class... ARGS> inline
void assign(ITER dst, ARGS&&... args)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	*dst = ValueType(forward<ARGS>(args)...);
}

template<class ITER, class... ARGS> inline
void assign(ITER beg, ITER end, ARGS&&... args)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	for (; beg != end; ++beg)
		*beg = ValueType(forward<ARGS>(args)...);
}

template<class ITER, class T> inline
void assign(ITER dstBeg, const T& val, size_t count)
{
	using ValueType = typename Iter_Traits<ITER>::ValueType;
	static_assert(IsSame<T, ValueType>());
	auto end = dstBeg + count;
	for (; dstBeg != end; ++dstBeg)
		*dstBeg = val;
}

}

#elif NMSP_STL_BUILD_EASTL_CONTAINER


#else
	#error "nmspAlgorithm.h should have backend switch"
#endif // NMSP_STL_BUILD_EASTL_CONTAINER

#endif


namespace nmsp {

#if 0
#pragma mark --- MemoryUtil-Decl ---
#endif // 0
#if 1

template<typename T>
void memory_copy(T* dst, const T* src, size_t n);

template<typename T> inline
void memory_move(T* dst, const T* src, size_t n);

template<typename T> inline
void memory_set(T* dst, size_t n, int val = 0);


#endif

#if 0
#pragma mark --- MemoryUtil-Impl ---
#endif // 0
#if 1

template<typename T> inline
void memory_copy(T* dst, const T* src, size_t n)
{
	if (n < 0)
		return;

	if constexpr(IsTrivial<T>)
	{
		size_t bytes = sizeof(T) * n;
		if (bytes > StlTraits::s_kThresholdToCallDMA)
		{
			::memcpy(dst, src, bytes);
			return;
		}
	}

	auto* end = src + n;
	for (; src != end; ++dst, ++src)
		*dst = *src;
}

template<typename T> inline // const T* will trigger copy intead of move
void memory_move(T* dst, /*const*/ T* src, size_t n)
{
	if (n < 0)
		return;

	if constexpr (IsTrivial<T>)
	{
		size_t bytes = sizeof(T) * n;
		if (bytes > StlTraits::s_kThresholdToCallDMA)
		{
			::memmove(dst, src, bytes);
			return;
		}
	}

	auto* end = src + n;
	for (; src != end; ++dst, ++src)
		*dst = move(*src);
}

#if 0
#pragma mark --- MemoryUtil::memory_set()-Impl ---
#endif // 0
#if 1

template<class UINT, class ENABLE = void>
struct MemSetHelper;


template<class UINT>
struct MemSetHelper<UINT, void /*EnableIf< sizeof(UINT) >= sizeof(u64) >*/ >
{
	template<class T>
	static void small_memset_impl(T* dst, size_t n, int val)
	{
		auto v	  = sCast<UINT>(val);
		auto* beg = reinCast<UINT*>(dst);
		auto* end = reinCast<UINT*>(dst + n);
		for (; beg != end; ++beg)
			*beg = v;
	}
};

//template<class UINT>
//struct MemSetHelper < UINT, EnableIf< sizeof(UINT) <= sizeof(u32) > >
//{
//	template<class T>
//	static void small_memset_impl(T* dst, size_t n, int val)
//	{
//		auto bytes	= sizeof(T) * n;
//		auto v		= sCast<UINT>(val);
//		auto end	= bytes / sizeof(UINT);
//		for (u32 i = 0; i < n; i++)
//		{
//
//		}
//		auto* beg = reinCast<UINT>(beg);
//		auto* end = reinCast<UINT>(dst + n);
//		for (; beg != end; ++beg)
//			*beg = v;
//	}
//};

template<typename T> inline
void memory_set(T* dst, size_t n, int val)
{
	if (n < 0)
		return;
	
	static_assert(IsTrivial<T>, "memory_set() must be Trivial Type");

	size_t bytes = sizeof(T) * n;
	if (bytes > StlTraits::s_kThresholdToCallDMA)
	{
		::memset(dst, val, bytes);
		return;
	}

	auto v	  = sCast<u8>(val);
	auto* beg = reinCast<u8*>(dst);
	auto* end = reinCast<u8*>(dst + n);
	for (; beg != end; ++beg)
		*beg = v;

	/*if		(bytes % 8 == 0) { return MemSetHelper<u64>::small_memset_impl(dst, n, val); }
	else if (bytes % 4 == 0) { return MemSetHelper<u32>::small_memset_impl(dst, n, val); }
	else if (bytes % 2 == 0) { return MemSetHelper<u16>::small_memset_impl(dst, n, val); }
	else					 { return MemSetHelper<u8 >::small_memset_impl(dst, n, val); }*/
}

#endif // 0


#endif

}

