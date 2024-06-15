#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"
#include "nmsp_stl/container/nmspArray.h"

namespace nmsp {

#if 0
#pragma mark --- Span_Eastl-Decl ---
#endif // 0
#if 1

template<class T, size_t EXTENT = eastl::dynamic_extent> 
class Span_Eastl : public eastl::span<T>
{
public:
	using Base			= eastl::span<T>;
	using ElementType	= typename Base::element_type;
	using ValueType		= typename Base::value_type;

	using Iter		= typename Base::iterator;
	using CIter		= typename Base::const_iterator;
	using RevIter	= typename Base::reverse_iterator;
	using CRevIter	= typename Base::const_reverse_iterator;

public:
	using SizeType	= StlTraits::SizeType;
	using IndexType = typename Base::index_type;

public:
	using Base::data;
	using Base::size;

public:

	/*template<class... ARGS>
	Span_Eastl(ARGS&&... args)
		: Base(nmsp::forward<ARGS>(args)...)
	{
	}*/
	NMSP_CONSTEXPR Span_Eastl() = default;
	NMSP_CONSTEXPR Span_Eastl(const Span_Eastl& rhs) = default;
	NMSP_CONSTEXPR Span_Eastl(T* s, IndexType count);
	NMSP_CONSTEXPR Span_Eastl(T* begin, T* end);
	NMSP_CONSTEXPR Span_Eastl(std::initializer_list<T> list);

	// conversion constructors for c-array and Array_T
	template <size_t N, class = EnableIf<(EXTENT == eastl::dynamic_extent || N == EXTENT)>> 
	NMSP_CONSTEXPR Span_Eastl(ElementType (&arr)[N]) NMSP_NOEXCEPT;

	template <size_t N, class = EnableIf<(EXTENT == eastl::dynamic_extent || N == EXTENT)>>
	NMSP_CONSTEXPR Span_Eastl(Array_T<ValueType, N>& arr) NMSP_NOEXCEPT;

	template <size_t N, class = EnableIf<(EXTENT == eastl::dynamic_extent || N == EXTENT)>>
	NMSP_CONSTEXPR Span_Eastl(const Array_T<ValueType, N>& arr) NMSP_NOEXCEPT;

public:
	bool		is_empty()		const;
	SizeType	size_in_bytes() const;

	// iterator support
	NMSP_CONSTEXPR Iter		begin()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR Iter		end()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CIter	cbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CIter	cend()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR RevIter	rbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR RevIter	rend()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CRevIter	crbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CRevIter	crend()		const NMSP_NOEXCEPT;
};

#endif


#if 0
#pragma mark --- Span_Eastl-Impl ---
#endif // 0
#if 1

template<class T, size_t EXTENT> inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(T* s, IndexType count)
	: Base (s, count)
{

}

template<class T, size_t EXTENT> inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(T* begin, T* end)
	: Base(begin, end)
{

}

template<class T, size_t EXTENT> inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(std::initializer_list<T> list)
//: Base(constCast<T*>(list.begin()), list.size())
	: Base(list.begin(), list.end())
{

}

template <class T, size_t EXTENT>
template <size_t N, class>  inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(ElementType(&arr)[N]) NMSP_NOEXCEPT 
	: Base(arr, static_cast<index_type>(N))
{

}

template <class T, size_t EXTENT>
template <size_t N, class>  inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(Array_T<ValueType, N> &arr) NMSP_NOEXCEPT 
	: Base(arr.data(), arr.size())
{

}

template <class T, size_t EXTENT>
template <size_t N, class>  inline NMSP_CONSTEXPR
Span_Eastl<T, EXTENT>::Span_Eastl(const Array_T<ValueType, N>& arr) NMSP_NOEXCEPT
	: Base(arr.data(), arr.size())
{

}

template<class T, size_t EXTENT> inline 
bool 
Span_Eastl<T, EXTENT>::is_empty() const
{
	return size() == 0;
}

template<class T, size_t EXTENT> inline 
typename Span_Eastl<T, EXTENT>::SizeType
Span_Eastl<T, EXTENT>::size_in_bytes() const
{
	return size() * sizeof(T);
}

template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::Iter		Span_Eastl<T, EXTENT>::begin()		const NMSP_NOEXCEPT	{ return Base::begin();		}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::Iter		Span_Eastl<T, EXTENT>::end()		const NMSP_NOEXCEPT	{ return Base::end();		}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::CIter	Span_Eastl<T, EXTENT>::cbegin()		const NMSP_NOEXCEPT	{ return Base::cbegin();	}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::CIter	Span_Eastl<T, EXTENT>::cend()		const NMSP_NOEXCEPT	{ return Base::cend();		}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::RevIter	Span_Eastl<T, EXTENT>::rbegin()		const NMSP_NOEXCEPT	{ return Base::rbegin();	}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::RevIter	Span_Eastl<T, EXTENT>::rend()		const NMSP_NOEXCEPT	{ return Base::rend();		}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::CRevIter	Span_Eastl<T, EXTENT>::crbegin()	const NMSP_NOEXCEPT	{ return Base::crbegin();	}
template<class T, size_t EXTENT> inline NMSP_CONSTEXPR typename Span_Eastl<T, EXTENT>::CRevIter	Span_Eastl<T, EXTENT>::crend()		const NMSP_NOEXCEPT	{ return Base::crend();		}

#endif

}