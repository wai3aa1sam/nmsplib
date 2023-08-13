#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"
#include "nmsp_stl/view/nmspSpan.h"

namespace nmsp {

#if 0
#pragma mark --- Vector_Eastl-Decl ---
#endif // 0
#if 1

template<class T, size_t N, bool bEnableOverflow = true, class OverflowAllocator = DefaultAllocator>
struct EASTL_Vector
{
	using Type = eastl::fixed_vector<T, N, bEnableOverflow, OverflowAllocator>;
};

template<class T, class Allocator>
struct EASTL_Vector<T, 0, true, Allocator>
{
	using Type = eastl::vector<T, Allocator>;
};

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class Vector_Eastl : public EASTL_Vector<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type
{
public:
	using Base = typename EASTL_Vector<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type;

	using SizeType = StlTraits::SizeType;

public:
	using ValueType = typename Base::value_type;
	using Allocator = FALLBACK_ALLOC;

	using ViewType 	= Span_T<T>;
	using CViewType = Span_T<const T>;

public:
	using Base::data;
	using Base::size;
	using Base::begin;
	using Base::end;

public:
	Vector_Eastl() = default;
	~Vector_Eastl() = default;

	explicit Vector_Eastl(Allocator& allocator);
	Vector_Eastl(std::initializer_list<ValueType> ilist, const Allocator& allocator = Allocator{});
	template<class... ARGS> Vector_Eastl(SizeType n, ARGS&&... args);
	//explicit Vector_Eastl(ViewType view, const Allocator& allocator = Allocator{});

	bool is_empty() const NMSP_NOEXCEPT;

	Span_T<      T> span();
	Span_T<const T> span() const;

	ByteSpan_T byteSpan() const;


private:

};


#endif


#if 0
#pragma mark --- Vector_Eastl-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(Allocator& allocator)
	: Base(allocator)
{

}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(std::initializer_list<ValueType> ilist, const Allocator& allocator)
	: Base(ilist, allocator)
{}

template<class T, size_t N, class FALLBACK_ALLOC>
template<class... ARGS> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(SizeType n, ARGS&&... args)
{
	reserve(n);
	for (size_t i = 0; i < n; i++)
	{
		emplace_back(nmsp::forward<ARGS>(args)...);
	}
}

//template<class T, size_t N, class FALLBACK_ALLOC> inline
//Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(ViewType view, const Allocator& allocator)
//	: Base(view, allocator)
//{}

template<class T, size_t N, class FALLBACK_ALLOC> inline
bool Vector_Eastl<T, N, FALLBACK_ALLOC>::is_empty() const NMSP_NOEXCEPT
{
	return size() == 0;
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Span_T<T> Vector_Eastl<T, N, FALLBACK_ALLOC>::span()
{
	return Span_T<T>{begin(), end()};
	//return ViewType{begin(), end()};
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Span_T<const T> Vector_Eastl<T, N, FALLBACK_ALLOC>::span() const
{
	return Span_T<const T>{begin(), end()};
	//return CViewType{begin(), end()};
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
ByteSpan_T 
Vector_Eastl<T, N, FALLBACK_ALLOC>::byteSpan() const
{
	return makeByteSpan(span());
}

#endif

}
