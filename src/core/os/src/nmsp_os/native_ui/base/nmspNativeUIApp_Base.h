#pragma once

#include "nmsp_os/common/nmsp_os_common.h"
#include "nmsp_os/app/AppBase.h"

#include "nmsp_stl/view/nmspStringView.h"

/*
references:
- src/core/native_ui/NativeUIApp_Base.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {


#if 0
#pragma mark --- NativeUIApp_Base-Decl ---
#endif // 0
#if 1

struct NativeUIApp_CreateDesc_Base
{
public:
	using CreateDesc = NativeUIApp_CreateDesc_Base;

public:
	StrViewA_T title;
};

// interface only class
class NativeUIApp_Base : public AppBase_T
{
public:
	using Base = AppBase_T;
	
	using CreateDesc_Base	= NativeUIApp_CreateDesc_Base;
	using CreateDesc		= NativeUIApp_CreateDesc_Base;

	using Msg		 = OsTraits::Msg;
	using Util		 = OsTraits::Util;

public:
	static CreateDesc	makeCDesc();

public:
	NativeUIApp_Base() = default;

	virtual ~NativeUIApp_Base();

	i32  run (const CreateDesc_Base& cd);
	void quit(i32 exitCode);

protected:
	virtual void onCreate	(const CreateDesc_Base& cd);
	virtual void onRun		();
	virtual void onQuit		();
	virtual void willQuit	();

protected:
	i32 _exitCode = 0;
};

#endif

}