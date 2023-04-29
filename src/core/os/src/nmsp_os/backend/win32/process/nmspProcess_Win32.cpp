#include "nmsp_os-pch.h"
#include "nmspProcess_Win32.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- Process_Win32-Impl
#endif // 0
#if 1

Process_Win32::Process_Win32(const CreateDesc& cd)
{
	_notYetSupported();
}

Process_Win32::Process_Win32(StrViewA_T filename)
{
	_init(filename, "");
}

Process_Win32::Process_Win32(StrViewA_T filename, StrViewA_T args)
{
	_init(filename, args);
}


Process_Win32::~Process_Win32()
{
	clear();
}

void Process_Win32::create(StrViewA_T filename, StrViewA_T args)
{
	_init(filename, args);
}

void Process_Win32::clear()
{
	WaitForSingleObject(_procInfo.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(_procInfo.hProcess);
	CloseHandle(_procInfo.hThread);

	_startupInfo	= { 0 };
	_procInfo		= { 0 };
}

void Process_Win32::_init(StrViewA_T filename, StrViewA_T args)
{
	clear();

	TempStringW_T<> filenameW;
	UtfUtil::convert(filenameW, filename);

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