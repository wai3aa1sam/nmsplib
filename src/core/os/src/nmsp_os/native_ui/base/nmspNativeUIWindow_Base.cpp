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

void NativeUIWindow_Base::onCloseButton()
{

}

void NativeUIWindow_Base::onActive(bool isActive)
{

}

void NativeUIWindow_Base::onDraw()
{

}

const NativeUIWindow_Base::Rect2f& NativeUIWindow_Base::clientRect() const
{
	return _clientRect;
}

void NativeUIWindow_Base::onCreate(const CreateDesc& cd)
{

}

void NativeUIWindow_Base::onSetWindowTitle(StrViewA_T title)
{

}

void NativeUIWindow_Base::onClientRectChanged(const Rect2f& rect)
{

}

void NativeUIWindow_Base::onDrawNeeded()
{

}

#endif

}
