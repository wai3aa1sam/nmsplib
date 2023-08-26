#pragma once

#include "nmsp_os/common/nmsp_os_common.h"
//#include "nmsp_os/HiResTimer/base/nmspHiResTimer_Base.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/utility/nmspHiResTimer_Win32.h"

	namespace nmsp {

	using HiResTimer_Impl				= HiResTimer_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/HiResTimer/nmspHiResTimer_Linux.h"

	namespace nmsp {

	using HiResTimer_Impl				= HiResTimer_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- HiResTimer_T-Decl ---
#endif // 0
#if 1

//using HiResTimer_CreateDesc	= HiResTimer_CreateDesc_Impl;
using HiResTimer_T				= HiResTimer_Impl;

#endif

}