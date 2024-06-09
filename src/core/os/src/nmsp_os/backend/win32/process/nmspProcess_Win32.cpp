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

bool
Process_Win32::execute(StrViewA_T filename, StrViewA_T args)
{
	return _execute(filename, args);
}

bool 
Process_Win32::execute(StrViewA_T filename, StrViewA_T args, const CreateDesc& cd)
{
	{
		// This structure specifies the STDIN and STDOUT handles for redirection.
		// Set the bInheritHandle flag so pipe handles are inherited. 
		SECURITY_ATTRIBUTES saAttr; 
		saAttr.nLength				= sizeof(SECURITY_ATTRIBUTES); 
		saAttr.bInheritHandle		= TRUE; 
		saAttr.lpSecurityDescriptor = NULL;
		if (cd.isCreateStdout)
			_createPipe(&_stdoutRead, &_stdoutWrite, _stdoutRead, saAttr);

		if (cd.isCreateStdin)
			_createPipe(&_stdinRead, &_stdinWrite, _stdinWrite, saAttr);

		if (cd.isCreateStdout || cd.isCreateStdin)
		{
			_startupInfo.hStdError	= _stdoutWrite;
			_startupInfo.hStdOutput	= _stdoutWrite;
			_startupInfo.hStdInput	= _stdinRead;
			_startupInfo.dwFlags   |= STARTF_USESTDHANDLES;
		}
	}

	return _execute(filename, args);
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
	Util::closeHandleAndSetNull(_procInfo.hProcess);
	Util::closeHandleAndSetNull(_procInfo.hThread);
	Util::closeHandleAndSetNull(_stdoutRead);
	Util::closeHandleAndSetNull(_stdoutWrite);
	Util::closeHandleAndSetNull(_stdinRead);
	Util::closeHandleAndSetNull(_stdinWrite);

	_startupInfo	= { 0 };
	_procInfo		= { 0 };
}

u32 
Process_Win32::returncode()
{
	DWORD exitCode = 0;
	BOOL ret;
	ret = GetExitCodeProcess(processHandle(), &exitCode);
	Util::throwIf(!ret);
	//else if (ret == STILL_ACTIVE)

	return exitCode;
}

u32 
Process_Win32::awaitReturncode(u64 msTimeout)
{
	wait(msTimeout);
	DWORD exitCode = returncode();
	return exitCode;
}

bool 
Process_Win32::_execute(StrViewA_T filename, StrViewA_T args)
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
		TRUE,					// Set handle inheritance to FALSE
		0,						// No creation flags
		NULL,					// Use parent's environment block
		NULL,					// Use parent's starting directory 
		&_startupInfo,			// Pointer to STARTUPINFO structure
		&_procInfo				// Pointer to PROCESS_INFORMATION structure
	);

	Util::throwIf(!ret, "cannot execute process {}", filename);

	if (ret)
	{
		// Close handles to the stdin and stdout pipes no longer needed by the child process.
		// If they are not explicitly closed, there is no way to recognize that the child process has ended.
		Util::closeHandleAndSetNull(_stdoutWrite);
		Util::closeHandleAndSetNull(_stdinRead);
	}

	return ret;
}


bool 
Process_Win32::_createPipe(Handle* oReadHnd, Handle* oWriteHnd, Handle handleForSetInfo, SECURITY_ATTRIBUTES& saAttr)
{
	BOOL isSuccess;
	isSuccess = ::CreatePipe(oReadHnd, oWriteHnd, &saAttr, 0);
	// Create a pipe for the child process's STDOUT. 
	if (!isSuccess)
	{
		Util_Win32::throwIf(!isSuccess);
		return false;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (handleForSetInfo)
	{
		isSuccess = ::SetHandleInformation(handleForSetInfo, HANDLE_FLAG_INHERIT, 0);
		Util_Win32::throwIf(!isSuccess);
		return false;
	}

	 return true;
}

Process_Win32::SizeType 
Process_Win32::_readStdout(char* oBuf, SizeType nBytesToRead)
{
	NMSP_CORE_ASSERT(_stdoutRead, "stdout has not created");

	DWORD	nBytesRead	= 0;
	BOOL	bSuccess	= FALSE;

	bSuccess = ReadFile(_stdoutRead, oBuf, sCast<DWORD>(nBytesToRead), &nBytesRead, nullptr);
	if (!bSuccess)
	{
		auto err = Util::getLastErrorCode();
		Util::throwIf(err != ERROR_BROKEN_PIPE && err != ERROR_IO_PENDING);
	}

	#if 0
	// Read output from the child process's pipe for STDOUT
	// and write to the parent process's pipe for STDOUT. 
	// Stop when there is no more data. 
	{ 
		DWORD dwRead, dwWritten; 
		CHAR chBuf[BUFSIZE]; 
		BOOL bSuccess = FALSE;
		HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		for (;;) 
		{ 
			bSuccess = ReadFile( g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
			if( ! bSuccess || dwRead == 0 ) break; 

			bSuccess = WriteFile(hParentStdOut, chBuf, 
				dwRead, &dwWritten, NULL);
			if (! bSuccess ) break; 
		} 
	} 
	#endif // 0

	return nBytesRead;
}


#endif

}
#endif