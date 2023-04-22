#include "nmsp_os-pch.h"

#include "nmspNativeUIWindow_Win32.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Win32-Impl ---
#endif // 0
#if 1

NativeUIWindow_Win32::CreateDesc	NativeUIWindow_Win32::makeCD()
{
	return CreateDesc{};
}

NativeUIWindow_Win32::NativeUIWindow_Win32(const CreateDesc& cd)
{

}

NativeUIWindow_Win32::~NativeUIWindow_Win32()
{

}

void NativeUIWindow_Win32::onCreate(const CreateDesc& cd)
{
	Base::onCreate(cd);


}


#endif

}

#endif // 0
