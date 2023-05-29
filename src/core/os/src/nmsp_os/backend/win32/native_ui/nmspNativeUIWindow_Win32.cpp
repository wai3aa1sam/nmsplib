#include "nmsp_os-pch.h"

#include "nmspNativeUIWindow_Win32.h"

#include <nmsp_stl/string/nmspUtfUtil.h>

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
				//NMSP_DELETE(thisObj);
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
				thisObj->_handleNativeEvent(hwnd, msg, wParam, lParam);
			}
		} break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

NativeUIWindow_Win32::This* NativeUIWindow_Win32::s_getThis(WndHnd hwnd)
{
	auto	data	= ::GetWindowLongPtr(hwnd, GWLP_USERDATA);
	auto*	thisObj = reinterpret_cast<This*>(data);
	return thisObj;
}

LRESULT NativeUIWindow_Win32::_handleNativeEvent		(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (_handleNativeUIKeyEvent(hwnd, msg, wParam, lParam))		return 0;
	if (_handleNativeUIMouseEvent(hwnd, msg, wParam, lParam))	return 0;
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool	NativeUIWindow_Win32::_handleNativeUIMouseEvent	(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UIMouseEvent ev;

	ev.modifier = _getWin32Modifier();

	using Button = UIMouseEventButton;
	using Type   = UIMouseEventType;

	POINT curPos;
	::GetCursorPos(&curPos);
	::ScreenToClient(hwnd, &curPos);

	ev.pos = Util::castVec2<f32>(curPos);

	auto button = Button::None;
	switch (HIWORD(wParam)) 
	{
		case XBUTTON1: { button = Button::Button4; } break;
		case XBUTTON2: { button = Button::Button5; } break;
	}

	switch (msg) 
	{
		case WM_LBUTTONUP:		{ ev.type = Type::Up;	ev.button = Button::Left;	} break;
		case WM_MBUTTONUP:		{ ev.type = Type::Up;	ev.button = Button::Middle;	} break;
		case WM_RBUTTONUP:		{ ev.type = Type::Up;	ev.button = Button::Right;	} break;

		case WM_LBUTTONDOWN:	{ ev.type = Type::Down;	ev.button = Button::Left;	} break;
		case WM_MBUTTONDOWN:	{ ev.type = Type::Down;	ev.button = Button::Middle;	} break;
		case WM_RBUTTONDOWN:	{ ev.type = Type::Down;	ev.button = Button::Right;	} break;

		case WM_MOUSEMOVE:		{ ev.type = Type::Move;	} break;

		#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		// vertical  scroll wheel 
		case WM_MOUSEWHEEL:		{ ev.type = Type::Scroll;	ev.scroll.set(0,GET_WHEEL_DELTA_WPARAM(wParam)); } break;
		#endif

		#if (_WIN32_WINNT >= 0x0600)
		// horizontal scroll wheel 
		case WM_MOUSEHWHEEL:	{ ev.type = Type::Scroll;	ev.scroll.set(GET_WHEEL_DELTA_WPARAM(wParam),0); } break;
		#endif

		default:
			return false;
	}

	switch (ev.type) 
	{
		case Type::Down:	::SetCapture(hwnd); break;
		case Type::Up:		::ReleaseCapture(); break;
	}

	onUINativeMouseEvent(ev);
	return true;
}

bool	NativeUIWindow_Win32::_handleNativeUIKeyEvent	(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UIKeyboardEvent ev;

	using Button = UIKeyboardEventButton;
	using Type   = UIKeyEventType;

	ev.modifier = _getWin32Modifier();

	switch (msg) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			int keycode = sCast<UINT>(wParam);
			ev.type = ((HIWORD(lParam) & KF_UP) == KF_UP) ? Type::Up : Type::Down;

			// check if is repeat
			if ((lParam & (0x1 << 30)) && ev.type == Type::Down)
				ev.type = Type::Hold;

			ev.button = sCast<Button>(keycode);
		}break;

		case WM_CHAR:
		case WM_SYSCHAR:
		case WM_UNICHAR:
		{

		} break;

		default:
			return false;
	}

	onUINativeKeyboardEvent(ev);
	return true;
}

UIEventModifier NativeUIWindow_Win32::_getWin32Modifier()
{
	auto o = UIEventModifier::None;
	if (::GetAsyncKeyState(VK_CONTROL)) { o |= UIEventModifier::Ctrl;	}
	if (::GetAsyncKeyState(VK_SHIFT  )) { o |= UIEventModifier::Shift;	}
	if (::GetAsyncKeyState(VK_MENU   )) { o |= UIEventModifier::Atl;	}
	if (::GetAsyncKeyState(VK_LWIN) || ::GetAsyncKeyState(VK_RWIN)) 
	{
		o |= UIEventModifier::Cmd;
	}
	return o;
}

#endif

}

#endif // 0
