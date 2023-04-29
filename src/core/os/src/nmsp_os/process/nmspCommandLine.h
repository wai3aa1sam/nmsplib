#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include <nmsp_stl/string/nmspUtfUtil.h>

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/process/nmspCommandLine_Win32.h"

	namespace nmsp {

	using CmdLine_CreateDesc_Impl	= CmdLine_CreateDesc_Win32;
	using CmdLine_Impl				= CmdLine_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/process/nmspCommandLine_Linux.h"

	namespace nmsp {

	using CmdLine_CreateDesc_Impl	= CmdLine_CreateDesc_Linux;
	using CmdLine_Impl				= CmdLine_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- CmdLine_T-Decl ---
#endif // 0
#if 1

using CmdLine_CreateDesc	= CmdLine_CreateDesc_Impl;
using CmdLine_T				= CmdLine_Impl;

#endif

}