#include "nmsp_os-pch.h"

#include "nmspNativeUIApp_Base.h"

namespace nmsp {

#if 0
#pragma mark --- NativeUIApp_Base-Impl ---
#endif // 0
#if 1

NativeUIApp_Base::CreateDesc NativeUIApp_Base::makeCDesc()
{
	return CreateDesc{};
}

NativeUIApp_Base::~NativeUIApp_Base()
{
}

i32 NativeUIApp_Base::run(const CreateDesc_Base& cd)
{
	onCreate(cd);

	onRun();

	return _exitCode;
}

void NativeUIApp_Base::quit(i32 exitCode)
{
	_exitCode = exitCode;
	onQuit();
}

void NativeUIApp_Base::onCreate(const CreateDesc_Base& cd)
{
}

void NativeUIApp_Base::onRun()
{

}

void NativeUIApp_Base::onQuit()
{
}

void NativeUIApp_Base::willQuit()
{

}

#endif


}