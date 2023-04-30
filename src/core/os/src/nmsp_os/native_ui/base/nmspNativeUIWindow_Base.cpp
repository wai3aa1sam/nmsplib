#include "nmsp_os-pch.h"

#include "nmspNativeUIWindow_Base.h"

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Base-Impl ---
#endif // 0
#if 1

NativeUIWindow_Base::CreateDesc	NativeUIWindow_Base::makeCDesc()
{
	return CreateDesc{};
}

NativeUIWindow_Base::NativeUIWindow_Base(const CreateDesc& cd)
{
	_clientRect = cd.rect;
}

NativeUIWindow_Base::~NativeUIWindow_Base()
{

}

void NativeUIWindow_Base::create			(const CreateDesc& cd)
{
	onCreate(cd);
}

void NativeUIWindow_Base::setWindowTitle	(StrViewA_T title)
{

}


const NativeUIWindow_Base::Rect2f& NativeUIWindow_Base::clientRect() const
{
	return _clientRect;
}

void NativeUIWindow_Base::onUINativeMouseEvent(UIMouseEvent& ev)
{
	using Button = UIMouseEventButton;
	using Type   = UIMouseEventType;

	switch (ev.type) 
	{
		case Type::Down: { BitUtil::set		(_pressedMouseButtons, ev.button); } break;
		case Type::Up:   { BitUtil::unset	(_pressedMouseButtons, ev.button); } break;
	}

	ev.pressedButtons = _pressedMouseButtons;

	ev.deltaPos = ev.pos - _mousePos;
	_mousePos	= ev.pos;

	onUIMouseEvent(ev);
}

void NativeUIWindow_Base::onUINativeKeyboardEvent(UIKeyboardEvent& ev)
{
	using Button = UIKeyboardEventButton;
	using Type   = UIKeyEventType;

	onUIKeyboardEvent(ev);
}

#endif

}
