#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"
#include "nmsp_stl/view/nmspStringView.h"

namespace nmsp {

#if 0
#pragma mark --- String_Eastl-Decl ---
#endif // 0
#if 1

template<class T, size_t N, bool bEnableOverflow, class OverflowAllocator>
struct EASTL_String
{
	using Type = eastl::fixed_string<T, N, bEnableOverflow, OverflowAllocator>;
};

template<class T, class Allocator>
struct EASTL_String<T, 0, true, Allocator>
{
	using Type = eastl::basic_string<T, Allocator>;
};

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class String_Eastl : public EASTL_String<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type
{
public:
	using Base = typename EASTL_String<T, N, !IsSame<FALLBACK_ALLOC, NoFallbackAllocator_Policy>, FALLBACK_ALLOC>::Type;

public:
	using ValueType = T;
	using ViewType	= StrView_T<T>;
	using Allocator = FALLBACK_ALLOC;

public:
	using Base::data;
	using Base::size;
	using Base::begin;
	using Base::end;

public:
	String_Eastl() = default;
	~String_Eastl() = default;

	String_Eastl(ViewType view);
	explicit String_Eastl(ViewType sv, const Allocator& allocator);
	String_Eastl(const T* cstr);

	template<class STR> void operator= (STR&& rhs);
	template<class STR> void operator+=(const STR& rhs);

	template<size_t N_, class ALLOC = Allocator> void operator= (const String_Eastl<T, N_, ALLOC>& rhs);
	template<size_t N_, class ALLOC = Allocator> void operator+=(const String_Eastl<T, N_, ALLOC>& rhs);

	void operator= (ViewType view);
	void operator+=(ViewType view);

	operator ViewType() const NMSP_NOEXCEPT;

	ViewType view() const;

	bool is_empty() const;
	
private:

};



#endif


#if 0
#pragma mark --- String_Eastl-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class FALLBACK_ALLOC> inline
String_Eastl<T, N, FALLBACK_ALLOC>::String_Eastl(ViewType view)
	: Base(view.data(), view.size())
{

}

template<class T, size_t N, class FALLBACK_ALLOC> inline
String_Eastl<T, N, FALLBACK_ALLOC>::String_Eastl(ViewType sv, const Allocator& allocator)
	: Base(sv, allocator)
{}

template<class T, size_t N, class FALLBACK_ALLOC> inline
String_Eastl<T, N, FALLBACK_ALLOC>::String_Eastl(const T* cstr)
	: Base(cstr)
{}

template<class T, size_t N, class FALLBACK_ALLOC>
template<class STR> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator= (STR&& rhs)
{
	Base::operator=(nmsp::forward<STR>(rhs));
}

template<class T, size_t N, class FALLBACK_ALLOC>
template<class STR> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator+=(const STR& rhs)
{
	Base::operator+=(rhs);
}

template<class T, size_t N, class FALLBACK_ALLOC>
template<size_t N_, class ALLOC> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator=(const String_Eastl<T, N_, ALLOC>& rhs)
{
	this->clear();
	this->append(rhs.begin(), rhs.end());
}

template<class T, size_t N, class FALLBACK_ALLOC>
template<size_t N_, class ALLOC> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator+=(const String_Eastl<T, N_, ALLOC>& rhs)
{
	this->append(rhs.begin(), rhs.end());
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator= (ViewType view)
{
	this->clear();
	this->append(view.begin(), view.end());
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
void String_Eastl<T, N, FALLBACK_ALLOC>::operator+=(ViewType view)
{
	this->append(view.begin(), view.end());
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
String_Eastl<T, N, FALLBACK_ALLOC>::operator ViewType() const NMSP_NOEXCEPT
{
	return ViewType{ data(), size() };
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
typename String_Eastl<T, N, FALLBACK_ALLOC>::ViewType String_Eastl<T, N, FALLBACK_ALLOC>::view() const
{
	return ViewType{ data(), size() };
}

template<class T, size_t N, class FALLBACK_ALLOC> inline
bool
String_Eastl<T, N, FALLBACK_ALLOC>::is_empty() const
{
	return size() == 0;
}

#endif

}
