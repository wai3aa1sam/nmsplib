#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspUIEvent.h"

/*
references:
- src/core/input/UIEvent.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

enum class UIMouseEventType 
{
	None,
	Up,
	Down,
	Move,
	Scroll,
};
NMSP_ENUM_ALL_OPERATOR(UIMouseEventType)

enum class UIMouseEventButton 
{
	None,
	Left	= BitUtil::bit(0),
	Middle	= BitUtil::bit(1),
	Right	= BitUtil::bit(2),
	Button4 = BitUtil::bit(3),
	Button5 = BitUtil::bit(4),
};
NMSP_ENUM_ALL_OPERATOR(UIMouseEventButton)


#if 0
#pragma mark --- UIMouseEvent-Decl ---
#endif // 0
#if 1

struct UIMouseEvent 
{
public:
	using Type		= UIMouseEventType;
	using Modifier	= UIEventModifier;
	using Button	= UIMouseEventButton;
	using Vec2f		= OsTraits::Vec2f;

public:
	bool isUp()		const;
	bool isDown()	const;
	bool isMove()	const;
	bool isScroll() const;

	bool isDragging() const;

	bool isDown(Button but) const;

public:
	Type		type			= Type::None;
	Modifier	modifier		= Modifier::None;
	Button		button			= Button::None;
	Button		pressedButtons	= Button::None;

	Vec2f		pos		{0,0};
	Vec2f		deltaPos{0,0};
	Vec2f		scroll	{0,0};
};

#endif

#if 0
#pragma mark --- UIMouseEvent-Impl ---
#endif // 0
#if 1

inline bool UIMouseEvent::isUp()		const	{ return type == Type::Up; }
inline bool UIMouseEvent::isDown()		const	{ return type == Type::Down; }
inline bool UIMouseEvent::isMove()		const	{ return type == Type::Move; }
inline bool UIMouseEvent::isScroll()	const	{ return type == Type::Scroll; }

inline bool UIMouseEvent::isDragging() const	{ return type == Type::Move && pressedButtons != Button::None; }

inline bool UIMouseEvent::isDown(Button but) const
{
	return pressedButtons == but;
}

#endif

}
