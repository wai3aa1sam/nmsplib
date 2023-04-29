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

	template<class T> using ULock_Impl = ULock_Std<T>;
	template<class T> using SLock_Impl = SLock_Std<T>;

	}

#elif NMSP_OS_BUILD_MUTEX_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspMutex_Win32.h"

	namespace nmsp {

	using Mutex_Impl	= Mutex_Win32;
	using SMutex_Impl	= SMutex_Win32;

	template<class T> using ULock_Impl = ULock_Win32<T>;
	template<class T> using SLock_Impl = SLock_Win32<T>;

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

template<class T> using ULock_T = ULock_Impl<T>;
template<class T> using SLock_T = SLock_Impl<T>;

}