#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- os_thread_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_BUILD_THREAD_STD


#elif NMSP_OS_BUILD_THREAD_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspNativeThread_Win32.h"

	namespace nmsp {

	using NativeThread_Impl	= NativeThread_Win32;

	}

	#else
	#error "unsupported os thread build"
	#endif // 0

#endif // 0



#endif

namespace nmsp {

using NativeThread_T = NativeThread_Impl;

}