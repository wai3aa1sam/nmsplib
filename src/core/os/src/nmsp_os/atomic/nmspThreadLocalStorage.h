#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- nmsp_os_threadLS_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_BUILD_ATM_STD

	#include "nmsp_os/backend/std/atomic/nmspThreadLocalStorage_Std.h"

	namespace nmsp {

	template<class T> using ThreadLS_Impl	= ThreadLS_Std<T>;

	}

#elif NMSP_OS_BUILD_ATM_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspThreadLocalStorage_Win32.h"

	namespace nmsp {

	template<class T> using ThreadLS_Impl	= ThreadLS_Win32<T>;

	}

	#else
	#error "unsupported nmsp_os threadLS build"
	#endif // 0

#endif // 0


#else
#error "unsupported nmsp_os threadLS build"
#endif // 0

namespace nmsp {

template<class T> using ThreadLS_T = ThreadLS_Impl<T>;

}