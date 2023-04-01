#pragma once

#include "../common/nmsp_stl_common.h"
#include "../container/nmspIterator.h"

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

void memory_copy()
{

}

void memory_set()
{

}

}