#pragma once

#include "nmsp_os/common/nmsp_os_common.h"


namespace nmsp {
#if 0
#pragma mark --- OsUtil_Win32-Decl ---
#endif // 0
#if 1

struct OsUtil_Win32 : public OsUtil
{
public:
	using Base = OsUtil;

	using Rect2f = typename Base::Rect2f;

public:
	OsUtil_Win32() = delete;

public:
	static Rect2f toRect2f(const ::RECT& rect);

	static void throwIf(bool cond);

	template<class T>
	static DWORD castDWord(T v);

};

template<class T>
DWORD OsUtil_Win32::castDWord(T v)
{
	return sCast<DWORD>(v);
}

#endif

}