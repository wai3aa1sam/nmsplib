#pragma once

#include "nmsp_os/process/base/nmspProcess_Base.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/process/nmspProcess_Win32.h"

	namespace nmsp {

	using Process_CreateDesc_Impl	= Process_CreateDesc_Win32;
	using Process_Impl				= Process_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/process/nmspProcess_Linux.h"

	namespace nmsp {

	using Process_CreateDesc_Impl	= Process_CreateDesc_Linux;
	using Process_Impl				= Process_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- Process_T-Decl ---
#endif // 0
#if 1

using Process_CreateDesc	= Process_CreateDesc_Impl;
using Process_T				= Process_Impl;

#endif

}