#pragma once

#include <EASTL/string_view.h>

namespace nmsp {

#if 0
#pragma mark --- StringView_Eastl-Decl ---
#endif // 0
#if 1

template<class T> 
class StrView_Eastl : public eastl::basic_string_view<T>
{
public:
	using Base = eastl::basic_string_view<T>;

public:
	using SizeType = typename Base::size_type;
public:

	/*template<class... ARGS>
	StrView_Eastl(ARGS&&... args)
		: Base(nmsp::forward<ARGS>(args)...)
	{
	}*/
	NMSP_CONSTEXPR StrView_Eastl() = default;
	NMSP_CONSTEXPR StrView_Eastl(const StrView_Eastl& rhs) = default;
	NMSP_CONSTEXPR StrView_Eastl(const T* s, SizeType count);
	NMSP_CONSTEXPR StrView_Eastl(const T* s);


	bool is_empty() const;
};

#endif


#if 0
#pragma mark --- StringView_Eastl-Impl ---
#endif // 0
#if 1

template<class T> inline NMSP_CONSTEXPR
StrView_Eastl<T>::StrView_Eastl(const T* s, SizeType count)
	: Base (s, count)
{

}

template<class T> inline NMSP_CONSTEXPR
StrView_Eastl<T>::StrView_Eastl(const T* s)
	: Base (s)
{

}

template<class T> inline 
bool StrView_Eastl<T>::is_empty() const
{
	return size() == 0;
}

#endif

}