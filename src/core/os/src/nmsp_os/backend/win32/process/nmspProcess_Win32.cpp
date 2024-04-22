#include "nmsp_os-pch.h"
#include "nmspProcess_Win32.h"
#include "nmsp_os/file/nmspPath.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- Process_Win32-Impl
#endif // 0
#if 1

Process_Win32::Process_Win32(const CreateDesc& cd)
{
	NMSP_NOT_YET_SUPPORT();
}

Process_Win32::Process_Win32(StrViewA_T filename)
{
	_execute(filename, StrViewA_T{});
}

Process_Win32::Process_Win32(StrViewA_T filename, StrViewA_T args)
{
	_execute(filename, args);
}

Process_Win32::~Process_Win32()
{
	wait(INFINITE);
	kill();
}

void Process_Win32::execute(StrViewA_T filename, StrViewA_T args)
{
	_execute(filename, args);
}

void Process_Win32::wait(u64 timeoutMs)
{
	auto hnd = _procInfo.hProcess;
	if (hnd)
	{
		WaitForSingleObject(hnd, sCast<DWORD>(timeoutMs));
	}
}

void Process_Win32::kill()
{
	// Close process and thread handles. 
	if (_procInfo.hProcess)
	{
		CloseHandle(_procInfo.hProcess);
	}
	if (_procInfo.hThread)
	{
		CloseHandle(_procInfo.hThread);
	}

	_startupInfo	= { 0 };
	_procInfo		= { 0 };
}

void Process_Win32::_execute(StrViewA_T filename, StrViewA_T args)
{
	TempStringW_T<> filenameW;

	if (Path::isRealpath(filename))
	{
		UtfUtil::convert(filenameW, filename);
	}
	else
	{
		TempStringA_T<> temp;
		Path::realpathTo(temp, filename);
		UtfUtil::convert(filenameW, temp);
	}

	TempStringW_T<> argsW;
	UtfUtil::convert(argsW, args);

	_startupInfo.cb = sizeof(_startupInfo);

	auto ret = ::CreateProcess(
		filenameW.c_str(),		// No module name (use command line)
		(LPWSTR)argsW.c_str(),	// Command line
		NULL,					// Process_Win32 handle not inheritable
		NULL,					// Thread handle not inheritable
		FALSE,					// Set handle inheritance to FALSE
		0,						// No creation flags
		NULL,					// Use parent's environment block
		NULL,					// Use parent's starting directory 
		&_startupInfo,			// Pointer to STARTUPINFO structure
		&_procInfo				// Pointer to PROCESS_INFORMATION structure
	);

	Util::throwIf(!ret, "cannot execute process {}", filename);
}
#endif

}
#endif