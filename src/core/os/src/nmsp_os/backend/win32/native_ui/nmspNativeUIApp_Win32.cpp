#include "nmsp_os-pch.h"

#include "nmspNativeUIApp_Win32.h"

#include <nmsp_stl/string/nmspUtfUtil.h>

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIApp_Win32-Impl ---
#endif // 0
#if 1

NativeUIApp_Win32::CreateDesc	NativeUIApp_Win32::makeCDesc()
{
	return CreateDesc{};
}

NativeUIApp_Win32::~NativeUIApp_Win32()
{
}

void NativeUIApp_Win32::pollMsg()
{
	while (::PeekMessage(&_win32Msg, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&_win32Msg);
		::DispatchMessage(&_win32Msg);
	}
}

NativeUIApp_Win32::Msg NativeUIApp_Win32::msg()
{
	return _win32Msg;
}

void NativeUIApp_Win32::onCreate(const CreateDesc& cd)
{
	Base::onCreate(cd);

}

void NativeUIApp_Win32::onRun()
{
	Base::onRun();

	while (::GetMessage(&_win32Msg, NULL, 0, 0)) {
		::TranslateMessage(&_win32Msg);
		::DispatchMessage(&_win32Msg);
	}

	willQuit();
}

void NativeUIApp_Win32::onQuit()
{
	Base::onQuit();
	::PostQuitMessage(_exitCode);
}

void NativeUIApp_Win32::willQuit()
{
	Base::willQuit();
}

#endif


}

#endif