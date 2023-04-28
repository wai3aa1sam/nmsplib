#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/file/nmspMemMapFile_Win32.h"

	namespace nmsp {

	using MemMapFile_CreateDesc_Impl	= MemMapFile_CreateDesc_Win32;
	using MemMapFile_Impl				= MemMapFile_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/file/nmspMemMapFile_Linux.h"

	namespace nmsp {

	using MemMapFile_CreateDesc_Impl	= MemMapFile_CreateDesc_Linux;
	using MemMapFile_Impl				= MemMapFile_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

using MemMapFile_CreateDesc = MemMapFile_CreateDesc_Impl;
using MemMapFile_T			= MemMapFile_Impl;

}