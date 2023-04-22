#include "nmsp_os-pch.h"

#include "nmspNativeUIWindow_Win32.h"

#include "nmsp_stl/string/nmspUtfUtil.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Win32-Impl ---
#endif // 0
#if 1

NativeUIWindow_Win32::CreateDesc	NativeUIWindow_Win32::makeCDesc()
{
	return CreateDesc{};
}

NativeUIWindow_Win32::NativeUIWindow_Win32(const CreateDesc& cd)
{

}

NativeUIWindow_Win32::~NativeUIWindow_Win32()
{
	if (_wndHnd)
	{
		DestroyWindow(_wndHnd);
		_wndHnd = nullptr;
	}
}

void NativeUIWindow_Win32::onCloseButton()
{
	Base::onCloseButton();
}

void NativeUIWindow_Win32::onActive(bool isActive)
{
	Base::onActive(isActive);
}

void NativeUIWindow_Win32::onDraw	()
{
	Base::onDraw();
}

NativeUIWindow_Win32::WndHnd NativeUIWindow_Win32::wndHnd()
{
	return _wndHnd;
}

void NativeUIWindow_Win32::onCreate				(const CreateDesc& cd)
{
	Base::onCreate(cd);

	const wchar_t* clsName = L"NativeUIWindow";

	auto hInstance	= ::GetModuleHandle(nullptr);
	WNDCLASSEX wc	= {};
	wc.cbSize			= sizeof(wc);
	wc.style			= CS_HREDRAW | CS_VREDRAW; // | CS_DROPSHADOW;
	wc.lpfnWndProc		= &s_wndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground	= nullptr; //(HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= nullptr;
	wc.lpszClassName	= clsName;
	wc.hIconSm			= LoadIcon(hInstance, IDI_APPLICATION);

	if (!cd.hasCloseButton) {
		wc.style |= CS_NOCLOSE;
	}

	DWORD dwStyle = 0;
	DWORD dwExStyle = WS_EX_ACCEPTFILES;
	if (cd.isAlwaysOnTop)
		dwExStyle |= WS_EX_TOPMOST;

	switch (cd.type) 
	{
		case CreateDesc::Type::ToolWindow:
		case CreateDesc::Type::NormalWindow: 
		{
			dwStyle   |= WS_OVERLAPPED | WS_SYSMENU;

			if (cd.hasCloseButton) dwStyle |= WS_SYSMENU;
			if (cd.isResizable   ) dwStyle |= WS_THICKFRAME;
			if (cd.hasTitleBar   ) dwStyle |= WS_CAPTION;
			if (cd.hasMinButton  ) dwStyle |= WS_MINIMIZEBOX;
			if (cd.hasMaxButton  ) dwStyle |= WS_MAXIMIZEBOX;
		} break;

		case CreateDesc::Type::PopupWindow: 
		{
			dwStyle   |= WS_POPUP | WS_BORDER;
		} break;

		default: 
		{
			NMSP_ASSERT(false); 
		} break;
	}

	if (cd.type == CreateDesc::Type::ToolWindow) 
	{
		dwExStyle |= WS_EX_TOOLWINDOW;
	}

	WNDCLASSEX tmpWc;
	bool registered = (0 != ::GetClassInfoEx(hInstance, clsName, &tmpWc));
	if (!registered) 
	{
		if (!::RegisterClassEx(&wc)) {
			throw NMSP_ERROR("error RegisterClassEx");
		}
	}

	auto rect = cd.rect;
	if (cd.isCenterToScreen) 
	{
		auto screenSize = Vec2f((float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN));
		rect.pos = (screenSize - rect.size) / 2;
	}

	_wndHnd = ::CreateWindowEx(dwExStyle, clsName, clsName, dwStyle,
		(int)cd.rect.x,
		(int)cd.rect.y,
		(int)cd.rect.w,
		(int)cd.rect.h,
		nullptr, nullptr, hInstance, this);
	if (!_wndHnd) 
	{
		NMSP_THROW("cannot create native window");
	}

	ShowWindow(_wndHnd, SW_SHOW);
}

void NativeUIWindow_Win32::onSetWindowTitle		(StrViewA_T title)
{
	Base::onSetWindowTitle(title);

	if (!_wndHnd) 
		return;
	TempStringW_T<> tmp = UtfUtil::toStringW(title);
	::SetWindowText(_wndHnd, tmp.c_str());
}

void NativeUIWindow_Win32::onClientRectChanged	(const Rect2f& rect)
{
	NMSP_ASSERT(_wndHnd, "onClientRectChanged()");
	Base::onClientRectChanged(rect);

}

void NativeUIWindow_Win32::onDrawNeeded()
{
	Base::onDrawNeeded();

	::InvalidateRect(_wndHnd, nullptr, false);
}

LRESULT WINAPI NativeUIWindow_Win32::s_wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
		case WM_CREATE: 
		{
			auto cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			auto* thisObj = static_cast<This*>(cs->lpCreateParams);
			thisObj->_wndHnd = hwnd;
			::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)thisObj);
		} break;

		case WM_DESTROY: 
		{
			if (auto* thisObj = s_getThis(hwnd)) 
			{
				::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)nullptr);
				thisObj->_wndHnd = nullptr;
				//nmsp_delete(thisObj);
			}
		} break;

		case WM_PAINT: 
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			if (auto* thisObj = s_getThis(hwnd)) 
			{
				thisObj->onDraw();
			}
			EndPaint(hwnd, &ps);
			return 0;
		} break;

		case WM_CLOSE: 
		{
			if (auto* thisObj = s_getThis(hwnd)) 
			{
				thisObj->onCloseButton();
				return 0;
			}
		} break;

		case WM_SIZE: 
		{
			if (auto* thisObj = s_getThis(hwnd))
			{
				RECT clientRect;
				::GetClientRect(hwnd, &clientRect);
				Rect2f newClientRect = Util::toRect2f(clientRect);

				thisObj->onClientRectChanged(newClientRect);
				return 0;
			}
 		} break;

		case WM_ACTIVATE: 
		{
			if (auto* thisObj = s_getThis(hwnd)) 
			{
				u16 a = LOWORD(wParam);
				switch (a) {
					case WA_ACTIVE:		thisObj->onActive(true);  break;
					case WA_CLICKACTIVE:thisObj->onActive(true);  break;
					case WA_INACTIVE:	thisObj->onActive(false); break;
				}
			}
		} break;

		default: 
		{
			if (auto* thisObj = s_getThis(hwnd)) 
			{
				
			}
		} break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

NativeUIWindow_Win32::This* NativeUIWindow_Win32::s_getThis(WndHnd hwnd)
{
	return nullptr;
}



#endif

}

#endif // 0
