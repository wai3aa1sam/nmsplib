#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"
#include "nmsp_os/process/base/nmspCommandLine_Base.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- CmdLine_Win32-Decl ---
#endif // 0
#if 1
struct CmdLine_CreateDesc_Win32 : public CmdLine_CreateDesc_Base
{

};

class CmdLine_Win32 : public CmdLine_Base
{
public:
	using CreateDesc = CmdLine_CreateDesc_Base;

	using Util		= OsTraits::Util;
	using NativeHnd	= OsTraits::NativeFd;
	using FileSize	= OsTraits::FileSize;
	using SizeType	= OsTraits::SizeType;

public:
	CmdLine_Win32() = default;
	CmdLine_Win32(const CreateDesc& cd);
	CmdLine_Win32(StrViewA_T cmd, bool isCloseAfterExecute = true);

	~CmdLine_Win32();

	void execute(const CreateDesc& cd);
	void execute(StrViewA_T cmd, bool isCloseAfterExecute = true);

private:
	
};
#endif

}
#endif