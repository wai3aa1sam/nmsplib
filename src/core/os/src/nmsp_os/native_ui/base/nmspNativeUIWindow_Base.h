#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmsp_os/input/nmspUIInput.h"

/*
references:
- src/core/native_ui/NativeUIWindow_Base.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {


#if 0
#pragma mark --- NativeUIWindow_Base-Decl ---
#endif // 0
#if 1

struct NativeUIWindow_CreateDesc_Base
{
public:
	using CreateDesc = NativeUIWindow_CreateDesc_Base;

	using Rect2 = OsTraits::Rect2f;

	enum class Type
	{
		None,
		NormalWindow,
		ToolWindow,
		PopupWindow,
		_kCount,
	};
	CreateDesc()
		: hasTitleBar		(true)
		, isMainWindow		(false)
		, isVisible			(true)
		, isResizable		(true)
		, hasCloseButton	(true)
		, hasMinButton		(true)
		, hasMaxButton		(true)
		, isCenterToScreen	(true)
		, isAlwaysOnTop		(false)
	{}


public:
	Type	type = Type::NormalWindow;
	Rect2	rect = {10, 10, 800, 600};

	bool		hasTitleBar			: 1;
	bool		isMainWindow		: 1;
	bool		isVisible			: 1;
	bool		isResizable			: 1;
	bool		hasCloseButton		: 1;
	bool		hasMinButton		: 1;
	bool		hasMaxButton		: 1;
	bool		isCenterToScreen	: 1;
	bool		isAlwaysOnTop		: 1;
};

// interface only class
class NativeUIWindow_Base : public NonCopyable
{
public:
	using CreateDesc = NativeUIWindow_CreateDesc_Base;

	using Rect2f = OsTraits::Rect2f;
	using Vec2f  = typename Rect2f::Vec2;

	using Util	 = OsTraits::Util;
	using WndHnd = OsTraits::WndHnd;

public:
	static CreateDesc	makeCDesc();

public:
	NativeUIWindow_Base() = default;
	NativeUIWindow_Base(const CreateDesc& cd);

	virtual ~NativeUIWindow_Base();

	void create			(const CreateDesc& cd);
	void setWindowTitle	(StrViewA_T title);

	void drawNeeded();

	virtual void onCloseButton	() {};
	virtual void onActive		(bool isActive) {};
	virtual void onDraw			() {};

	const Rect2f& clientRect() const;

	virtual void onUIMouseEvent(UIMouseEvent& ev)		{};
	virtual void onUIKeyboardEvent(UIKeyboardEvent& ev) {};

	//bool isKeyDown(UIKeyEventButton button_)	{ return _keys[enumInt(button_)] == UIKeyboardEventType::Down || _keys[enumInt(button_)] == UIKeyboardEventType::Hold; }
	//bool isKeyUp(UIKeyEventButton button_)		{ return _keys[enumInt(button_)] == UIKeyboardEventType::Up; }

protected:
	virtual void onCreate			(const CreateDesc& cd)	{};
	virtual void onSetWindowTitle	(StrViewA_T title)		{};
	virtual void onClientRectChanged(const Rect2f& rect)	{};
	virtual void onDrawNeeded		()						{};

	virtual void onUINativeMouseEvent(UIMouseEvent& ev);
	virtual void onUINativeKeyboardEvent(UIKeyboardEvent& ev);

protected:
	Rect2f	_clientRect;

	UIMouseEventButton	_pressedMouseButtons = UIMouseEventButton::None;
	Vec2f				_mousePos{0,0};
};

#endif

}