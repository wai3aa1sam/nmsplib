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

	using Rect2f = typename Base::Rect2f;

public:
	Util_Win32() = delete;

public:
	static Rect2f toRect2f(const ::RECT& rect);

	template<class... ARGS>
	static void throwIf(bool cond, const char* fmt = "", ARGS&&... args);

	template<class T>
	static DWORD castDWord(T v);

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
		auto msg = getLastErrorMsg();
		_NMSP_LOG("--- Error: win32 - {}", msg);
		nmsp::throwIf(cond, fmt, nmsp::forward<ARGS>(args)...);
	}
}

template<class T> inline
DWORD Util_Win32::castDWord(T v)
{
	return sCast<DWORD>(v);
}

#endif

}