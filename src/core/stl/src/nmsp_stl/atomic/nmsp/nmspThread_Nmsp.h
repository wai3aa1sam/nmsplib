#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- stl_thread_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS

	#include "win32/nmspThread_Win32.h"

	namespace nmsp {

	using Thread_Nmsp_Impl	= Thread_Win32;

	}

#else
	#error "unsupported stl thread build"
#endif // 0

#endif

namespace nmsp {

using Thread_Nmsp = Thread_Nmsp_Impl;

}