#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspUiEvent.h"
#include "nmspUiKeyCode.h"

namespace nmsp {

enum class UiKeyboardEventType : u8
{
	None,
	Up,
	Down,
	HoldDown,
};
NMSP_ENUM_ALL_OPERATOR(UiKeyboardEventType)

#if 0
#pragma mark --- UiKeyboardEvent-Decl ---
#endif // 0
#if 1

struct UiKeyboardEvent
{
	using Type		= UiKeyboardEventType;
	using Modifier	= UiEventModifier;
	using Button	= UiKeyboardEventButton;

	bool isUp()			const;
	bool isDown()		const;
	bool isHoldDown()	const;
	bool isPressed()	const;

	bool isUp(		Button key_)	const;
	bool isDown(	Button key_)	const;
	bool isHoldDown(Button key_)	const;
	bool isPressed( Button key_)	const;

public:
	Type		type		= Type::None;
	Modifier	modifier	= Modifier::None;
	Button		button		= Button::None;
};

#endif

#if 0
#pragma mark --- UiKeyboardEvent-Impl ---
#endif // 0
#if 1

inline bool UiKeyboardEvent::isUp()			const { return type == Type::Up; }
inline bool UiKeyboardEvent::isDown()		const { return type == Type::Down; }
inline bool UiKeyboardEvent::isHoldDown()	const { return type == Type::HoldDown; }
inline bool UiKeyboardEvent::isPressed()	const { return isDown() || isHoldDown(); }

inline bool UiKeyboardEvent::isUp(		Button key_) const { return button == key_ && type == Type::Up; }
inline bool UiKeyboardEvent::isDown(	Button key_) const { return button == key_ && type == Type::Down; }
inline bool UiKeyboardEvent::isHoldDown(Button key_) const { return button == key_ && type == Type::HoldDown; }
inline bool UiKeyboardEvent::isPressed( Button key_) const { return isDown(key_) || isHoldDown(key_); }

#endif



}