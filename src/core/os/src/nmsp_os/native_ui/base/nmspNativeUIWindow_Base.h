#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmsp_os/input/nmspUIInput.h"

#include "nmsp_stl/container/nmspString.h"

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
	using CreateDesc		= NativeUIWindow_CreateDesc_Base;
	using CreateDesc_Base	= NativeUIWindow_CreateDesc_Base;

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
	using CreateDesc		= NativeUIWindow_CreateDesc_Base;
	using CreateDesc_Base	= NativeUIWindow_CreateDesc_Base;

	using Rect2f = OsTraits::Rect2f;
	using Vec2f  = OsTraits::Vec2f;

	using Util	 = OsTraits::Util;
	using WndHnd = OsTraits::WndHnd;

public:
	static CreateDesc	makeCDesc();

public:
	NativeUIWindow_Base() = default;
	NativeUIWindow_Base(const CreateDesc& cd);

	virtual ~NativeUIWindow_Base();

	void create	(const CreateDesc_Base& cd);
	void destroy();

	void setWindowTitle	(StrViewA_T title);

	void drawNeeded();

	virtual void onCloseButton	() {};
	virtual void onActive		(bool isActive) {};
	virtual void onDraw			() {};

	const Rect2f& clientRect() const;

	virtual void onUiMouseEvent(UiMouseEvent& ev)		{};
	virtual void onUiKeyboardEvent(UiKeyboardEvent& ev) {};

	//bool isKeyDown(UIKeyEventButton button_)	{ return _keys[enumInt(button_)] == UiKeyboardEventType::Down || _keys[enumInt(button_)] == UiKeyboardEventType::Hold; }
	//bool isKeyUp(UIKeyEventButton button_)		{ return _keys[enumInt(button_)] == UiKeyboardEventType::Up; }

public:
	const StringT& title() const;

protected:
	virtual void onCreate			(const CreateDesc_Base& cd)	{};
	virtual void onDestroy			()							{};
	virtual void onSetWindowTitle	(StrViewA_T title)			{};
	virtual void onClientRectChanged(const Rect2f& rect)		  ;
	virtual void onDrawNeeded		()							{};

	virtual void onUiNativeMouseEvent(UiMouseEvent& ev);
	virtual void onUiNativeKeyboardEvent(UiKeyboardEvent& ev);

protected:
	Rect2f	_clientRect {0, 0, 0, 0};

	UiMouseEventButton	_pressedMouseButtons = UiMouseEventButton::None;
	Vec2f				_mousePos{0,0};

	StringT _title;
};

inline void NativeUIWindow_Base::onClientRectChanged(const Rect2f& rect)		{ _clientRect = rect; };

inline const StringT& NativeUIWindow_Base::title() const { return _title; }


#endif

}