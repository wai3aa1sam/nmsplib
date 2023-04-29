#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- nmsp_os_condvar_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_BUILD_CONDVAR_STD

	#include "nmsp_os/backend/std/atomic/nmspCondVar_Std.h"

	namespace nmsp {

	using CondVar_Impl	= CondVar_Std;
	using CondVarA_Impl	= CondVarA_Std;

	}

#elif NMSP_OS_BUILD_CONDVAR_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspCondVar_Win32.h"

	namespace nmsp {

	using CondVar_Impl	= CondVar_Win32;
	using CondVarA_Impl	= CondVarA_Win32;

	}

	#else
	#error "unsupported nmsp_os condvar build"
	#endif // 0

#endif // 0


#else
	#error "unsupported nmsp_os condvar build"
#endif // 0

namespace nmsp {

using CondVar_T		= CondVar_Impl;
using CondVarA_T	= CondVarA_Impl;

}