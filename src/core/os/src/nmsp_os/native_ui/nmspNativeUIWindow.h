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
	
	#include "nmsp_os/backend/win32/native_ui/nmspNativeUIWindow_Win32.h"

	namespace nmsp {

	using NativeUIWindow_CreateDesc_Impl	= NativeUIWindow_CreateDesc_Win32;
	using NativeUIWindow_Impl				= NativeUIWindow_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/native_ui/nmspNativeUIWindow_Linux.h"

	namespace nmsp {

	using NativeUIWindow_CreateDesc_Impl	= NativeUIWindow_CreateDesc_Linux;
	using NativeUIWindow_Impl				= NativeUIWindow_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_T-Decl ---
#endif // 0
#if 1
using NativeUIWindow_CreateDesc = NativeUIWindow_CreateDesc_Impl;
class NativeUIWindow_T : public NativeUIWindow_Impl
{
public:
	using This = NativeUIWindow_T;
	using Base = NativeUIWindow_Impl;

private:

};
#endif

}