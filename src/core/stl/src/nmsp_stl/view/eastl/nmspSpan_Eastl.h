#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

#if 0
#pragma mark --- Span_Eastl-Decl ---
#endif // 0
#if 1

template<class T> 
class Span_Eastl : public eastl::span<T>
{
public:
	using Base = eastl::span<T>;
	
	using Iter		= typename Base::iterator;
	using CIter		= typename Base::const_iterator;
	using RevIter	= typename Base::reverse_iterator;
	using CRevIter	= typename Base::const_reverse_iterator;

public:
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
	NMSP_CONSTEXPR Span_Eastl(T* s);
	NMSP_CONSTEXPR Span_Eastl(T* begin, T* end);


	// iterator support
	NMSP_CONSTEXPR Iter		begin()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR Iter		end()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CIter	cbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CIter	cend()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR RevIter	rbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR RevIter	rend()		const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CRevIter	crbegin()	const NMSP_NOEXCEPT;
	NMSP_CONSTEXPR CRevIter	crend()		const NMSP_NOEXCEPT;

	bool is_empty() const;
};

#endif


#if 0
#pragma mark --- Span_Eastl-Impl ---
#endif // 0
#if 1

template<class T> inline NMSP_CONSTEXPR
Span_Eastl<T>::Span_Eastl(T* s, IndexType count)
	: Base (s, count)
{

}

template<class T> inline NMSP_CONSTEXPR
Span_Eastl<T>::Span_Eastl(T* s)
	: Base (s)
{

}

template<class T> inline NMSP_CONSTEXPR
Span_Eastl<T>::Span_Eastl(T* begin, T* end)
	: Base(begin, end)
{

}

template<class T> inline 
bool Span_Eastl<T>::is_empty() const
{
	return size() == 0;
}

template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::Iter		Span_Eastl<T>::begin()		const NMSP_NOEXCEPT	{ return Base::begin();		}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::Iter		Span_Eastl<T>::end()		const NMSP_NOEXCEPT	{ return Base::end();		}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::CIter		Span_Eastl<T>::cbegin()		const NMSP_NOEXCEPT	{ return Base::cbegin();	}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::CIter		Span_Eastl<T>::cend()		const NMSP_NOEXCEPT	{ return Base::cend();		}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::RevIter		Span_Eastl<T>::rbegin()		const NMSP_NOEXCEPT	{ return Base::rbegin();	}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::RevIter		Span_Eastl<T>::rend()		const NMSP_NOEXCEPT	{ return Base::rend();		}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::CRevIter	Span_Eastl<T>::crbegin()	const NMSP_NOEXCEPT	{ return Base::crbegin();	}
template<class T> inline NMSP_CONSTEXPR typename Span_Eastl<T>::CRevIter	Span_Eastl<T>::crend()		const NMSP_NOEXCEPT	{ return Base::crend();		}

#endif

}