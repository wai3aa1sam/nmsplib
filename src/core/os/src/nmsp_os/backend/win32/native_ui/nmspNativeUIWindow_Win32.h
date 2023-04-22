#pragma once

#include "nmsp_os/native_ui/nmspNativeUIWindow_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeUIWindow_Win32-Decl ---
#endif // 0
#if 1

//struct NativeUIWindow_CreateDesc_Win32 : public NativeUIWindow_CreateDesc_Base
//{
//
//};
using NativeUIWindow_CreateDesc_Win32 = NativeUIWindow_CreateDesc_Base;

class NativeUIWindow_Win32 : public NativeUIWindow_Base
{
public:
	using Base = NativeUIWindow_Base;

	using CreateDesc = NativeUIWindow_CreateDesc_Win32;

public:
	static CreateDesc	makeCD();

public:
	NativeUIWindow_Win32() = default;
	NativeUIWindow_Win32(const CreateDesc& cd);

	virtual ~NativeUIWindow_Win32();

protected:
	virtual void onCreate(const CreateDesc& cd) override;

private:

};


#endif

}

#endif