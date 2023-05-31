#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspUIEvent.h"
#include "nmspUIKeyCode.h"

namespace nmsp {

enum class UIKeyboardEventType : u8
{
	None,
	Up,
	Down,
	Hold,
};
NMSP_ENUM_ALL_OPERATOR(UIKeyboardEventType)

#if 0
#pragma mark --- UIKeyboardEvent-Decl ---
#endif // 0
#if 1

struct UIKeyboardEvent
{
	using Type		= UIKeyboardEventType;
	using Modifier	= UIEventModifier;
	using Button	= UIKeyboardEventButton;

	bool isUp	()	const;
	bool isDown	()	const;
	bool isHold	()	const;

	bool isUp	(Button key_)	const;
	bool isDown	(Button key_)	const;
	bool isHold	(Button key_)	const;

public:
	Type		type		= Type::None;
	Modifier	modifier	= Modifier::None;
	Button		button		= Button::None;
};

#endif

#if 0
#pragma mark --- UIKeyboardEvent-Impl ---
#endif // 0
#if 1

inline bool UIKeyboardEvent::isUp	() const { return type == Type::Up; }
inline bool UIKeyboardEvent::isDown	() const { return type == Type::Down; }
inline bool UIKeyboardEvent::isHold	() const { return type == Type::Hold; }

inline bool UIKeyboardEvent::isUp	(Button key_) const { return button == key_ && type == Type::Up; }
inline bool UIKeyboardEvent::isDown	(Button key_) const { return button == key_ && type == Type::Down; }
inline bool UIKeyboardEvent::isHold	(Button key_) const { return button == key_ && type == Type::Hold; }


#endif



}