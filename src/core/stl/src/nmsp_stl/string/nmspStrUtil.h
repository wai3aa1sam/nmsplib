#pragma once

#include "../common/nmsp_stl_common.h"

#include "nmspUtfUtil.h"

namespace nmsp {


#if 0
#pragma mark --- UtfUtil-Decl ---
#endif // 0
#if 1

struct StrUtil
{
	StrUtil() = delete;

	template<class CHAR> 
	static constexpr size_t s_kMaxParseSize		= StringInfo_T<CHAR>::s_kSize;
	static constexpr size_t s_kMaxParseSizeA	= s_kMaxParseSize<char>;
	static constexpr size_t s_kMaxParseSizeW	= s_kMaxParseSize<wchar_t>;

	static size_t len(const char* str);


	template<class T, size_t N, class ALLOC = DefaultAllocator> static StringA_T<N, ALLOC>  toStr			(T val);
	template<class T, size_t N, class ALLOC = DefaultAllocator> static StringW_T<N, ALLOC>  toStrW			(T val);
	template<class T, class ALLOC = DefaultAllocator>			static TempStringA_T<ALLOC> toTempStr		(T val);
	template<class T, class ALLOC = DefaultAllocator>			static TempStringW_T<ALLOC> toTempStrW		(T val);
	template<class T, size_t N, class ALLOC = DefaultAllocator> static bool					convertToStr	(StringA_T<N, ALLOC>& o, T val);
	template<class T, size_t N, class ALLOC = DefaultAllocator> static bool					convertToStrW	(StringW_T<N, ALLOC>& o, T val);
	template<class STR, class T>								static STR					toStr_T			(T val);
	template<class STR, class T>								static STR					toStrW_T		(T val);
	template<class T, class STR>								static bool					convertToStr_T	(STR& dst, T val);
	template<class T, class STR>								static bool					convertToStrW_T	(STR& dst, T val);
};

#endif


#if 0
#pragma mark --- UtfUtil-Impl ---
#endif // 0
#if 1


#if 0
#pragma mark --- UtfUtil::convertToStr_T()-Impl ---
#endif // 0
#if 1

template<class T, size_t N, class ALLOC> inline StringA_T<N, ALLOC> StrUtil::toStr (T val)					{ return toStr_T <StringA_T<N, ALLOC> >(val); }
template<class T, size_t N, class ALLOC> inline StringW_T<N, ALLOC> StrUtil::toStrW(T val)					{ return toStrW_T<StringW_T<N, ALLOC> >(val); }

template<class T, class ALLOC>			 inline TempStringA_T<ALLOC> StrUtil::toTempStr (T val)				{ return toStr_T <TempStringA_T<ALLOC> >(val); }
template<class T, class ALLOC>			 inline TempStringW_T<ALLOC> StrUtil::toTempStrW(T val)				{ return toStrW_T<TempStringW_T<ALLOC> >(val); }

template<class T, size_t N, class ALLOC> inline bool StrUtil::convertToStr (StringA_T<N, ALLOC>& o, T val)	{ return convertToStr_T (o, val); }
template<class T, size_t N, class ALLOC> inline bool StrUtil::convertToStrW(StringW_T<N, ALLOC>& o, T val)  { return convertToStrW_T(o, val); }

template<class STR, class T> inline 
STR StrUtil::toStr_T(T val)
{
	STR o;
	convertToStr_T(o, val);
	return o;
}

template<class STR, class T> inline 
STR StrUtil::toStrW_T(T val)
{
	STR o;
	convertToStrW_T(o, val);
	return o;
}

template<class T, class STR> inline 
bool StrUtil::convertToStr_T(STR& dst, T val) 
{ 
	auto& o = dst;
	o.reserve(s_kMaxParseSize<typename STR::ValueType>);
	auto ret = ::snprintf(o.data(), s_kMaxParseSize<typename STR::ValueType>, FormatTrait<T>::s_formatStr, val);
	if (ret < 0)
		return false;
	o.force_size(ret);
	return true;
}

template<class T, class STR> inline 
bool StrUtil::convertToStrW_T(STR& dst, T val) 
{ 
	TempStringA_T<> tmp;
	auto ret = convertToStr_T(tmp, val);
	UtfUtil::convert(dst, tmp);
	return ret;
}

#endif

inline
size_t StrUtil::len(const char* str)
{
	return ::strlen(str);
}

#endif


}