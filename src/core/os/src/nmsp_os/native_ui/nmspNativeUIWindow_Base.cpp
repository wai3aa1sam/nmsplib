#include "nmsp_os-pch.h"

#include "nmspNativeUIWindow_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Base-Impl ---
#endif // 0
#if 1

NativeUIWindow_Base::CreateDesc	NativeUIWindow_Base::makeCD()
{
	return CreateDesc{};
}

NativeUIWindow_Base::NativeUIWindow_Base(const CreateDesc& cd)
{

}

NativeUIWindow_Base::~NativeUIWindow_Base()
{

}

void NativeUIWindow_Base::create(const CreateDesc& cd)
{
	onCreate(cd);
}

void NativeUIWindow_Base::onCreate(const CreateDesc& cd)
{

}



#endif

}

#endif // 0
