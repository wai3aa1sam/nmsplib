#pragma once

#include "nmsp_os/common/base/nmspOsUtil_Base.h"

namespace nmsp {
#if 0
#pragma mark --- Util_Win32-Decl ---
#endif // 0
#if 1

struct Util_Win32 : public OsUtil_Base
{
public:
	using Base = OsUtil_Base;

	using Base::Vec2_T;
	using Base::Rect2f;

public:
	Util_Win32() = delete;

public:
	static Rect2f	toRect2f(const ::RECT& rect);
	static u64		toU64(const LARGE_INTEGER& v);

	template<class... ARGS>
	static void throwIf(bool cond, const char* fmt = "", ARGS&&... args);

	template<class T> static DWORD		castDWord	(T v);
	template<class T> static POINT		castPoint	(const Vec2_T<T>& v);
	template<class T> static Vec2_T<T>	castVec2	(const POINT& pt);

	static StringT getLastErrorMsg();

};
#endif

#if 0
#pragma mark --- OsUtil_Win32-Impl ---
#endif // 0
#if 1

template<class... ARGS> inline
void Util_Win32::throwIf(bool cond, const char* fmt, ARGS&&... args)
{
	if (cond)
	{
		_NMSP_LOG(fmt, nmsp::forward<ARGS>(args)...);
		auto msg = getLastErrorMsg();
		_NMSP_LOG("--- Error: win32 - {}", msg); std::cout << std::flush;
		//nmsp::throwIf(cond, fmt, nmsp::forward<ARGS>(args)...);
	}
}


template<class T> inline
DWORD Util_Win32::castDWord(T v)
{
	return sCast<DWORD>(v);
}

template<class T> inline
POINT Util_Win32::castPoint(const Vec2_T<T>& v)
{
	POINT o;
	o.x = sCast<LONG>(v.x);
	o.y = sCast<LONG>(v.y);
	return o;
}

template<class T> inline
Util_Win32::Vec2_T<T> Util_Win32::castVec2(const POINT& pt)
{
	return Vec2_T<T>{sCast<T>(pt.x), sCast<T>(pt.y)};
}

#endif

}