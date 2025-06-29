#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"
#include "nmsp_stl/view/nmspSpan.h"

namespace nmsp 
{

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
	using This = typename Vector_Eastl<T, N, FALLBACK_ALLOC>;

	using SizeType = StlTraits::SizeType;

public:
	using ValueType = typename Base::value_type;
	using Allocator = FALLBACK_ALLOC;

	using ViewType 	= Span_T<T>;
	using CViewType = Span_T<const T>;

	using Iter	= typename Base::iterator;      
	using CIter = typename Base::const_iterator;

public:
	using Base::data;
	using Base::size;
	using Base::begin;
	using Base::end;

public:
	Vector_Eastl() = default;
	~Vector_Eastl() = default;

	Vector_Eastl(const	This&	v);
	Vector_Eastl(		This&&	v);

	explicit Vector_Eastl(Allocator& allocator);
	Vector_Eastl(std::initializer_list<ValueType> ilist, const Allocator& allocator = Allocator{});
	template<class... ARGS> Vector_Eastl(SizeType n, ARGS&&... args);
	//explicit Vector_Eastl(ViewType view, const Allocator& allocator = Allocator{});

	void operator=(const	This&	v);
	void operator=(			This&&	v);

public:
	void	appendRange(const CViewType& r);
	T		moveBack();

						Iter	find(const T& v);
						CIter	find(const T& v) const;

	template<class PRED> Iter	findIf(PRED pred);
	template<class PRED> CIter	findIf(PRED pred) const;

	void reverse();

	Iter remove(const T& value);

public:
	bool		is_empty()		const NMSP_NOEXCEPT;
	SizeType	size_in_bytes() const;

	ViewType	span();
	CViewType	span() const;

	operator ViewType ();
	operator CViewType() const;

	ViewType	subspan(SizeType offset, SizeType count);
	CViewType	subspan(SizeType offset, SizeType count) const;

	ViewType	subspan(SizeType offset);
	CViewType	subspan(SizeType offset) const;

	ByteSpan_T	byteSpan() const;

private:

};


#endif


#if 0
#pragma mark --- Vector_Eastl-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(const This& v)
	: Base(v)
{

}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::Vector_Eastl(This&&	v)
	: Base(nmsp::move(v))
{

}

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
void 
Vector_Eastl<T, N, FALLBACK_ALLOC>::operator=(const This& v)
{
	Base::operator=(v);
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void 
Vector_Eastl<T, N, FALLBACK_ALLOC>::operator=(This&& v)
{
	Base::operator=(nmsp::move(v));
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void 
Vector_Eastl<T, N, FALLBACK_ALLOC>::appendRange(const CViewType& r)
{
	Base::insert(end(), r.begin(), r.end());
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
T 
Vector_Eastl<T, N, FALLBACK_ALLOC>::moveBack()
{
	NMSP_CORE_ASSERT(!is_empty(), "failed, vector is empty");
	T out;
	auto* pBack = &back();
	out = nmsp::move(*pBack);
	pop_back();
	return out;
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::Iter
Vector_Eastl<T, N, FALLBACK_ALLOC>::find(const T& v)
{
	return nmsp::find(begin(), end(), v);
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::CIter
Vector_Eastl<T, N, FALLBACK_ALLOC>::find(const T& v) const
{
	return nmsp::find(cbegin(), cend(), v);
}

template<class T, size_t N, class FALLBACK_ALLOC>
template<class PRED> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::Iter
Vector_Eastl<T, N, FALLBACK_ALLOC>::findIf(PRED pred)
{
	return nmsp::find_if(begin(), end(), pred);
}

template<class T, size_t N, class FALLBACK_ALLOC>
template<class PRED> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::CIter
Vector_Eastl<T, N, FALLBACK_ALLOC>::findIf(PRED pred) const
{
	return nmsp::find_if(begin(), end(), pred);
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void Vector_Eastl<T, N, FALLBACK_ALLOC>::reverse()
{
	return nmsp::reverse(begin(), end());
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::Iter
Vector_Eastl<T, N, FALLBACK_ALLOC>::remove(const T& v)
{
	return nmsp::remove(begin(), end(), v);
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
bool Vector_Eastl<T, N, FALLBACK_ALLOC>::is_empty() const NMSP_NOEXCEPT
{
	return size() == 0;
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::SizeType
Vector_Eastl<T, N, FALLBACK_ALLOC>::size_in_bytes() const
{
	return size() * sizeof(T);
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::ViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::span()
{
	//return Span_T<T>{begin(), end()};
	return ViewType{begin(), end()};
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::CViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::span() const
{
	//return Span_T<const T>{begin(), end()};
	return CViewType{begin(), end()};
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::operator ViewType()	
{ 
	return span(); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
Vector_Eastl<T, N, FALLBACK_ALLOC>::operator CViewType() const	
{ 
	return span(); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::ViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::subspan(SizeType offset, SizeType count)			
{ 
	NMSP_CORE_ASSERT(size() > offset && count <= size() - offset, "overflow, invalid offset / count");
	return ViewType(begin() + offset, count); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::CViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::subspan(SizeType offset, SizeType count) const	
{ 
	NMSP_CORE_ASSERT(size() > offset && count <= size() - offset, "overflow, invalid offset / count");
	return CViewType(begin() + offset, count); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::ViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::subspan(SizeType offset)		
{ 
	return subspan(offset, size() - offset); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename Vector_Eastl<T, N, FALLBACK_ALLOC>::CViewType
Vector_Eastl<T, N, FALLBACK_ALLOC>::subspan(SizeType offset) const	
{
	return subspan(offset, size() - offset); 
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
ByteSpan_T 
Vector_Eastl<T, N, FALLBACK_ALLOC>::byteSpan() const
{
	return makeByteSpan(span());
}

#endif

}
