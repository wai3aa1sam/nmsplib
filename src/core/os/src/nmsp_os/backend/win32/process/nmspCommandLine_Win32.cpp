#include "nmsp_os-pch.h"

#include "nmspCommandLine_Win32.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- CmdLine_Win32-Impl ---
#endif // 0
#if 1


CmdLine_Win32::CmdLine_Win32(const CreateDesc& cd)
{
	NMSP_NOT_YET_SUPPORT();
}

CmdLine_Win32::CmdLine_Win32(StrViewA_T cmd, bool isCloseAfterExecute)
{
	execute(cmd);
}

void CmdLine_Win32::execute(StrViewA_T cmd, bool isCloseAfterExecute)
{
	StringT tmp;
	tmp += isCloseAfterExecute ? "/c " : "/k ";
	tmp += cmd;
	_proc.create(OsTraits::s_cmdExePath, tmp);
}

CmdLine_Win32::~CmdLine_Win32()
{

}

#endif

}
#endif