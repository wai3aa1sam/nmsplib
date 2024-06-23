#pragma once

#include "nmspUiMouseEvent.h"
#include "nmspUiKeyboardEvent.h"

namespace nmsp {


#if 0
#pragma mark --- nmspUiInput-Decl ---
#endif // 0
#if 1

struct UiInput
{
public:
	using Rect2f = OsTraits::Rect2f;
	using Vec2f  = OsTraits::Vec2f;

public:
	using Keys = Vector_T<UiKeyboardEventType, enumInt(UiKeyboardEventButton::_kCount)>;

public:
	UiMouseEventButton	pressedButtons	= UiMouseEventButton::None;
	Vec2f				pos				= Vec2f{0, 0};
	Keys				keyStates;

public:
	UiInput();
	~UiInput();

public:
	bool isKeyUp(		UiKeyboardEventButton key) const { return keyStates[enumInt(key)] == UiKeyboardEventType::Up; }
	bool isKeyDown(		UiKeyboardEventButton key) const { return keyStates[enumInt(key)] == UiKeyboardEventType::Down; }
	bool isKeyPressed(	UiKeyboardEventButton key) const { return isKeyDown(key) || keyStates[enumInt(key)] == UiKeyboardEventType::HoldDown; }
};

#endif


}