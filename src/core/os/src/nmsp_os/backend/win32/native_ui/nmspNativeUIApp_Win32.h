#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"

#include "nmsp_os/native_ui/base/nmspNativeUIApp_Base.h"

/*
references:
- src/core/native_ui/NativeUIApp_Win32.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIApp_Win32-Decl ---
#endif // 0
#if 1

//struct NativeUIApp_CreateDesc_Win32 : public NativeUIApp_CreateDesc_Base
//{
//
//};
using NativeUIApp_CreateDesc_Win32 = NativeUIApp_CreateDesc_Base;

class NativeUIApp_Win32 : public NativeUIApp_Base
{
public:
	using This = NativeUIApp_Win32;
	using Base = NativeUIApp_Base;

	using CreateDesc = NativeUIApp_CreateDesc_Win32;

public:
	static CreateDesc	makeCDesc();

public:
	NativeUIApp_Win32() = default;

	virtual ~NativeUIApp_Win32();

	void pollMsg();

	Msg msg();

protected:
	virtual void onCreate	(const CreateDesc& cd)	override;
	virtual void onRun		() override;
	virtual	void onQuit		() override;
	virtual void willQuit	() override;

protected:
	Msg _win32Msg;
};


#endif

}

#endif