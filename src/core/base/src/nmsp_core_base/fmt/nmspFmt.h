#pragma once

#include "fmt/format.h"

#include "nmsp_core_base/common/nmspDataType_Common.h"
#include "nmsp_core_base/common/nmspTypeTrait_Common.h"

namespace nmsp {

#if 0
#pragma mark --- FormatTrait-Impl ---
#endif // 0
#if 1

template<class T, class ENABLE = void>
struct FormatTrait
{
	FormatTrait() { static_assert(false, "FormatTrait cannot deduce type"); }
	static constexpr const char* s_formatStr = nullptr;
};

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

template<class STR, class... ARGS> inline
void fmtTo(STR& outStr, ARGS&&... args)
{
	fmt::format_to(std::back_inserter(outStr), std::forward<ARGS>(args)...);
}

template<class STR, class... ARGS> inline
STR fmtAs_T(ARGS&&... args)
{
	STR out;
	fmtTo(out, std::forward<ARGS>(args)...);
	return out;
}

#endif



}