#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#include <EASTL/span.h>

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

public:
	using IndexType = typename Base::index_type;

public:
	using Base::data;
	using Base::size;
	using Base::begin;
	using Base::end;

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

template<class T> inline 
bool Span_Eastl<T>::is_empty() const
{
	return size() == 0;
}

#endif

}