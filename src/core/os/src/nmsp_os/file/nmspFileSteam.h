#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/file/nmspFileStream_Win32.h"

	namespace nmsp {

	using FileStream_CreateDesc_Impl	= FileStream_CreateDesc_Win32;
	using FileStream_Impl				= FileStream_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/win32/file/nmspFileStream_Linux.h"

	namespace nmsp {

	using FileStream_CreateDesc_Impl	= FileStream_CreateDesc_Linux;
	using FileStream_Impl				= FileStream_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

using FileStream_CreateDesc = FileStream_CreateDesc_Impl;
using FileStream_T			= FileStream_Impl;

}