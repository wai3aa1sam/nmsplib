#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

/*
references:
- src/core/app/AppBase.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/app/nmspAppBase_Win32.h"

	namespace nmsp {

	using AppBase_Impl = AppBase_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/app/nmspAppBase_Linux.h"

	namespace nmsp {

	using AppBase_Impl = AppBase_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- AppBase_T-Decl ---
#endif // 0
#if 1

using AppBase_T = AppBase_Impl;

#endif

}
