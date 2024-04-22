#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"
#include "nmsp_os/process/base/nmspProcess_Base.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- Process_Win32-Impl ---
#endif // 0
#if 1

struct Process_CreateDesc_Win32 : public Process_CreateDesc_Base
{

};

class Process_Win32 : public Process_Base
{
public:
	using CreateDesc = Process_CreateDesc_Win32;

public:
	Process_Win32() = default;
	Process_Win32(const CreateDesc& cd);
	Process_Win32(StrViewA_T filename);
	Process_Win32(StrViewA_T filename, StrViewA_T args);

	~Process_Win32();

	//template<size_t N_CLI_ARGS>
	//Process(StrViewA_T filename, StrViewA_T(&args)[N_CLI_ARGS]);

	void execute(StrViewA_T filename, StrViewA_T args);
	void wait(u64 timeoutMs);
	void kill();

private:
	void _execute(StrViewA_T filename, StrViewA_T args);


private:
	STARTUPINFO			_startupInfo	= { 0 };
	PROCESS_INFORMATION _procInfo		= { 0 };
};

#endif
}
#endif