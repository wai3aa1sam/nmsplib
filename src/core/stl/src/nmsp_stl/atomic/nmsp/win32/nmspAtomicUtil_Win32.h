#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- AtomicUtil_Win32-Decl ---
#endif // 0
#if 1

void sleep_ms(int ms);
void sleep(int sec);

#endif

#if 0
#pragma mark --- AtomicUtil_Win32-Impl ---
#endif // 0
#if 1

inline void sleep_ms(int ms)
{
	::Sleep(ms);
}

inline void sleep(int sec)
{
	sleep_ms(sec * 1000);
}


}
#endif

#else
	#error "platform is not window"
#endif // NMSP_OS_WINDOWS


