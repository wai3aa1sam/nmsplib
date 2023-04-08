#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- stl_thread_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS

	#include "win32/nmspNativeThread_Win32.h"

	namespace nmsp {

	using NativeThread_Nmsp_Impl	= NativeThread_Win32;

	}

#else
	#error "unsupported stl thread build"
#endif // 0

#endif

namespace nmsp {

using NativeThread_Nmsp = NativeThread_Nmsp_Impl;

}