#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"

#include "nmsp_os/native_ui/base/nmspNativeUIWindow_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Win32-Decl ---
#endif // 0
#if 1

//struct NativeUIWindow_CreateDesc_Win32 : public NativeUIWindow_CreateDesc_Base
//{
//
//};
using NativeUIWindow_CreateDesc_Win32 = NativeUIWindow_CreateDesc_Base;

class NativeUIWindow_Win32 : public NativeUIWindow_Base
{
public:
	using This = NativeUIWindow_Win32;
	using Base = NativeUIWindow_Base;

	using CreateDesc	= NativeUIWindow_CreateDesc_Win32;

public:

public:
	static CreateDesc	makeCDesc();

public:
	NativeUIWindow_Win32() = default;
	NativeUIWindow_Win32(const CreateDesc& cd);

	virtual ~NativeUIWindow_Win32();

	virtual void onCloseButton	()				override;
	virtual void onActive		(bool isActive) override;
	virtual void onDraw			()				override;

	WndHnd wndHnd();

protected:
	virtual void onCreate			(const CreateDesc& cd)	override;
	virtual void onSetWindowTitle	(StrViewA_T title)		override;
	virtual void onClientRectChanged(const Rect2f& rect)	override;
	virtual void onDrawNeeded		()						override;


private:
	static LRESULT WINAPI s_wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static This* s_getThis(WndHnd hwnd);

private:
	WndHnd _wndHnd;
};


#endif

}

#endif