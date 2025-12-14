#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- nmsp_os_mutex_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_BUILD_MUTEX_STD

	#include "nmsp_os/backend/std/atomic/nmspMutex_Std.h"

	namespace nmsp {

	using Mutex_Impl	= Mutex_Std;
	using SMutex_Impl	= SMutex_Std;

	}

#elif NMSP_OS_BUILD_MUTEX_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspMutex_Win32.h"

	namespace nmsp {

	using Mutex_Impl	= Mutex_Win32;
	using SMutex_Impl	= SMutex_Win32;

	}

	#else
	#error "unsupported nmsp_os mutex build"
	#endif // 0

#endif // 0


#else
	#error "unsupported nmsp_os mutex build"
#endif // 0

namespace nmsp {

using Mutex_T	= Mutex_Impl;
using SMutex_T	= SMutex_Impl;

}