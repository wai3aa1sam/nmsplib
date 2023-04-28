#pragma once

#include "../common/nmsp_stl_common.h"

#include "nmspUtfUtil.h"

#include "nmsp_stl/extra/nmspPair.h"
#include "nmsp_stl/view/nmspView.h"

/*
references:
- src/core/file/StringUtil.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

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

	static void binToHex(StringT& result, Span_T<u8> data);
	static void appendBinToHex(StringT& result, ByteSpan_T data);

	static bool hasChar(StrViewA_T view, char ch);
	static bool hasAny (StrViewA_T view, StrViewA_T charList);

	static Pair<StrViewA_T, StrViewA_T> splitByChar(StrViewA_T view, StrViewA_T seperators);
	static Pair<StrViewA_T, StrViewA_T> splitByChar(StrViewA_T view, char seperator);

	static StrViewA_T	trimChar(StrViewA_T view, StrViewA_T seperators);

	static const char* findChar			(StrViewA_T view, StrViewA_T charList, bool ignoreCase);
	static const char* findCharFromEnd	(StrViewA_T view, StrViewA_T charList, bool ignoreCase);

	static int ignoreCaseCompare(StrViewA_T a, StrViewA_T b);
	static int ignoreCaseCompare(char a, char b);

	template<class T, size_t N> static StringA_T<N>		toStr			(const T& val);
	template<class T, size_t N> static StringW_T<N>		toStrW			(const T& val);
	template<class T>			static TempStringA_T<>	toTempStr		(const T& val);
	template<class T>			static TempStringW_T<>	toTempStrW		(const T& val);
	template<class T, size_t N> static bool				convertToStr	(StringA_T<N>& o, const T& val);
	template<class T, size_t N> static bool				convertToStrW	(StringW_T<N>& o, const T& val);

	template<class T> static bool tryParse(StrViewA_T view, T& outValue);

private:
	template<class STR, class T> static STR	 toStr_T		(const T& val);
	template<class STR, class T> static STR	 toStrW_T		(const T& val);
	template<class T, class STR> static bool convertToStr_T	(STR& dst, const T& val);
	template<class T, class STR> static bool convertToStrW_T(STR& dst, const T& val);
};

#endif


#if 0
#pragma mark --- UtfUtil-Impl ---
#endif // 0
#if 1

inline
size_t StrUtil::len(const char* str)
{
	return ::strlen(str);
}

inline
void StrUtil::binToHex(StringT& result, Span_T<u8> data) 
{
	result.clear();
	appendBinToHex(result, makeByteSpan(data));
}

inline
bool StrUtil::hasChar(StrViewA_T view, char ch) 
{ 
	return StrViewA_T::npos != view.find(ch); 
}

inline
bool StrUtil::hasAny(StrViewA_T view, StrViewA_T charList)
{
	for (auto ch : charList)
	{
		if (hasChar(view, ch))
		{
			return true;
		}
	}
	return false;
}

inline 
Pair<StrViewA_T, StrViewA_T> StrUtil::splitByChar(StrViewA_T view, StrViewA_T seperators)
{
	auto* s = view.begin();
	auto* e = view.end();
	for (auto* p = s; p < e; p++) {
		if (hasChar(seperators, *p)) {
			auto r0 = StrViewA_T(s,   p-s);
			auto r1 = StrViewA_T(p+1, e-p-1);
			return {r0, r1};
		}
	}
	return { view, StrViewA_T{} };
}

inline 
Pair<StrViewA_T, StrViewA_T> StrUtil::splitByChar(StrViewA_T view, char seperator)
{
	return splitByChar(view, StrViewA_T{&seperator, 1});
}

inline
StrViewA_T StrUtil::trimChar(StrViewA_T view, StrViewA_T charList) 
{
	auto* p = view.begin();
	auto* e = view.end();
	for (; p < e; p++) 
	{
		if (!hasChar(charList, *p))
			break;
	}
	return StrViewA_T(p, e-p);
}


inline
int StrUtil::ignoreCaseCompare(char a, char b) 
{ 
	return tolower(a) - tolower(b); 
}

#if 0
#pragma mark --- StrUtil::convertToStr_T()-Impl ---
#endif // 0
#if 1

template<class T, size_t N> inline StringA_T<N> StrUtil::toStr (const T& val)					{ return toStr_T <StringA_T<N> >(val); }
template<class T, size_t N> inline StringW_T<N> StrUtil::toStrW(const T& val)					{ return toStrW_T<StringW_T<N> >(val); }

template<class T>			inline TempStringA_T<> StrUtil::toTempStr (const T& val)			{ return toStr_T <TempStringA_T<> >(val); }
template<class T>			inline TempStringW_T<> StrUtil::toTempStrW(const T& val)			{ return toStrW_T<TempStringW_T<> >(val); }

template<class T, size_t N> inline bool StrUtil::convertToStr (StringA_T<N>& o, const T& val)	{ return convertToStr_T (o, val); }
template<class T, size_t N> inline bool StrUtil::convertToStrW(StringW_T<N>& o, const T& val)	{ return convertToStrW_T(o, val); }

template<class STR, class T> inline 
STR StrUtil::toStr_T(const T& val)
{
	STR o;
	convertToStr_T(o, val);
	return o;
}

template<class STR, class T> inline 
STR StrUtil::toStrW_T(const T& val)
{
	STR o;
	convertToStrW_T(o, val);
	return o;
}

template<class T, class STR> inline 
bool StrUtil::convertToStr_T(STR& dst, const T& val) 
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
bool StrUtil::convertToStrW_T(STR& dst, const T& val) 
{ 
	TempStringA_T<> tmp;
	auto ret = convertToStr_T(tmp, val);
	UtfUtil::convert(dst, tmp);
	return ret;
}

#endif

#if 0
#pragma mark --- StrUtil::tryParse()-Impl ---
#endif // 0
#if 1
template<class T, class ENABLE = void>
struct StrUtil_ParseHelper;

template<class T>
struct StrUtil_ParseHelper<T, EnableIf<IsUInt<T> > >
{
	using ResultType = u64;
};

template<class T>
struct StrUtil_ParseHelper<T, EnableIf<IsInt<T> > >
{
	using ResultType = i64;
};

template<class T>
struct StrUtil_ParseHelper<T, EnableIf<IsFloat<T> > >
{
	using ResultType = T;
};

template<class T> 
bool StrUtil::tryParse(StrViewA_T view, T& outValue)
{
	static_assert(IsUInt<T> || IsInt<T> || IsFloat<T>, "tryParse()");
	if constexpr (IsUInt<T>)
	{
		NMSP_ASSERT(!StrUtil::hasAny(view, "-f"), "tryParse()");
	}

	using ResultType = StrUtil_ParseHelper<T>::ResultType;

	TempStringA_T<> tmp = view;
	ResultType v;
	auto ret = ::sscanf(tmp.c_str(), FormatTrait<ResultType>::s_formatStr, &v);
	if (ret != 1) return false;

	if constexpr (!IsFloat<T>)
	{
		if (v < NumLimit<T>::min()) return false;
		if (v > NumLimit<T>::max()) return false;
	}

	outValue = sCast<T>(v);
	return true;
}
#endif // 1


#endif


}