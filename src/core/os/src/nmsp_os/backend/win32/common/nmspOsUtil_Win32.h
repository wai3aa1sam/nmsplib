#pragma once

#include "nmsp_os/common/base/nmspOsUtil_Base.h"

namespace nmsp {
#if 0
#pragma mark --- OsUtil_Win32-Decl ---
#endif // 0
#if 1

struct OsUtil_Win32 : public OsUtil_Base
{
public:
	using Base = OsUtil_Base;

	using Rect2f = typename Base::Rect2f;

public:
	OsUtil_Win32() = delete;

public:
	static void sleep_ms(int ms);
	static void sleep(int sec);

};
#endif

#if 0
#pragma mark --- OsUtil_Win32-Impl ---
#endif // 0
#if 1

inline
void OsUtil_Win32::sleep_ms(int ms)
{
	::Sleep(ms);
}

inline
void OsUtil_Win32::sleep(int sec)
{
	sleep_ms(sec * 1000);
}

#endif

}