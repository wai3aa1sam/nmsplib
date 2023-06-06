#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

/*
references:
- src/core/native_ui/NativeUI.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/native_ui/nmspNativeUIApp_Win32.h"

	namespace nmsp {

	using NativeUIApp_CreateDesc_Impl	= NativeUIApp_CreateDesc_Win32;
	using NativeUIApp_Impl				= NativeUIApp_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/native_ui/nmspNativeUIApp_Linux.h"

	namespace nmsp {

	using NativeUIApp_CreateDesc_Impl	= NativeUIApp_CreateDesc_Linux;
	using NativeUIApp_Impl				= NativeUIApp_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- NativeUIApp_T-Decl ---
#endif // 0
#if 1
using NativeUIApp_CreateDesc = NativeUIApp_CreateDesc_Impl;
class NativeUIApp_T : public NativeUIApp_Impl
{
public:
	using This = NativeUIApp_T;
	using Base = NativeUIApp_Impl;

private:
};
#endif

}