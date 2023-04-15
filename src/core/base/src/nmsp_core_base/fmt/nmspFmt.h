#pragma once

#include "fmt/format.h"

#include "nmsp_core_base/common/nmspDataType_Common.h"
#include "nmsp_core_base/common/nmspTypeTrait_Common.h"


#define NMSP_FORMATTER_T(TEMPLATE_ARGS, CLASS) \
	template<TEMPLATE_ARGS> \
	struct fmt::formatter<nmsp::CLASS> { \
		auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); } \
		auto format(const nmsp::CLASS& v, fmt::format_context& ctx) { \
			nmsp::onFormat(ctx, v); \
			return ctx.out(); \
		} \
	}; \
//------

#define NMSP_FORMATTER(CLASS) NMSP_FORMATTER_T(NMSP_EMPTY, CLASS)

namespace nmsp {

template<class T>
void onFormat(fmt::format_context& ctx, const T& v);

template<class... ARGS> inline
void formatTo(fmt::format_context& ctx, const char* fmt, ARGS&&... args)
{
	fmt::format_to(ctx.out(), fmt, forward<ARGS>(args)...);
}

template<class... ARGS> inline
void formatTo(fmt::format_context& ctx, const wchar_t* fmt, ARGS&&... args)
{
	fmt::format_to(ctx.out(), fmt, forward<ARGS>(args)...);
}

#if 0
#pragma mark --- FormatTrait-Impl ---
#endif // 0
#if 1

template<class T, class ENABLE = void>
struct FormatTrait;

template<class T>
struct FormatTrait<T, EnableIf< IsUInt<T> && sizeof(T)		<= sizeof(u32) > >
{
	static constexpr const char* s_formatStr = "%lu";
};

template<class T>
struct FormatTrait<T, EnableIf< IsUInt<T> && !(sizeof(T)	<= sizeof(u32)) > >
{
	static constexpr const char* s_formatStr = "%llu";
};

template<class T>
struct FormatTrait<T, EnableIf< IsInt<T> && sizeof(T)		<= sizeof(i32) > >
{
	static constexpr const char* s_formatStr = "%ld";
};

template<class T>
struct FormatTrait<T, EnableIf< IsInt<T> && !(sizeof(T)		<= sizeof(i32)) > >
{
	static constexpr const char* s_formatStr = "%lld";
};

template<class T>
struct FormatTrait<T, EnableIf< IsFloat<T> && sizeof(T)		<= sizeof(f32) > >
{
	static constexpr const char* s_formatStr = "%f";
};

template<class T>
struct FormatTrait<T, EnableIf< IsFloat<T> && !(sizeof(T)	<= sizeof(f32)) > >
{
	static constexpr const char* s_formatStr = "%lf";
};

#endif // 0

#if 0
#pragma mark --- nmspFormatter-Impl ---
#endif // 0
#if 1

#if NMSP_CPLUSPLUS_17 || NMSP_CPLUSPLUS_20

inline
std::string_view makeStdStrView(const char* cs)
{
	return { cs, ::strlen(cs) };
}

inline
std::wstring_view makeStdStrView(const wchar_t* cs)
{
	return { cs, ::wcslen(cs) };
}

#else

inline
const char* makeStdStrView(const char* cs)
{
	return cs;
}

inline
const wchar_t* makeStdStrView(const wchar_t* cs)
{
	return cs;
}

#endif // NMSP_CPLUSPLUS_20


template<class STR, class... ARGS> inline
void fmtTo(STR& outStr, const char* fmt, ARGS&&... args)
{
	fmt::vformat_to(std::back_inserter(outStr), makeStdStrView(fmt), fmt::make_format_args(std::forward<ARGS>(args)...) );
}

template<class STR, class... ARGS> inline
STR fmtAs_T(const char* fmt, ARGS&&... args)
{
	STR out;
	fmtTo(out, fmt, std::forward<ARGS>(args)...);
	return out;
}

template<class STR, class... ARGS> inline
void fmtTo(STR& outStr, const wchar_t* fmt, ARGS&&... args)
{
	fmt::vformat_to(std::back_inserter(outStr), makeStdStrView(fmt), fmt::make_format_args(std::forward<ARGS>(args)...));
}

template<class STR, class... ARGS> inline
STR fmtAs_T(const wchar_t* fmt, ARGS&&... args)
{
	STR out;
	fmtTo(out, fmt, std::forward<ARGS>(args)...);
	return out;
}

#endif






}