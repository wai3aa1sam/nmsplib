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

	using Handle = ::HANDLE;

public:
	Process_Win32() = default;
	Process_Win32(const CreateDesc& cd);
	Process_Win32(StrViewA_T filename);
	Process_Win32(StrViewA_T filename, StrViewA_T args);

	~Process_Win32();

	//template<size_t N_CLI_ARGS>
	//Process(StrViewA_T filename, StrViewA_T(&args)[N_CLI_ARGS]);

	bool execute(StrViewA_T filename, StrViewA_T args);
	bool execute(StrViewA_T filename, StrViewA_T args, const CreateDesc& cd);
	void wait(u64 timeoutMs);
	void kill();

	u32 returncode();

	/*
	* ret: return code, -1 == still, TODO: ProcessStatus
	*/
	template<size_t N = 0, class ALLOC = DefaultAllocator> SizeType readStdout(		Vector_T<char, N, ALLOC>& oBuf, SizeType nBytesToRead);

public:
	u32 awaitReturncode(u64 msTimeout);
	template<size_t N = 0, class ALLOC = DefaultAllocator> u32		awaitAllStdout(	Vector_T<char, N, ALLOC>& oBuf, u64 msTimeout, SizeType startBufSize = 1024);

private:
	bool _execute(StrViewA_T filename, StrViewA_T args);
	bool _createPipe(Handle* oReadHnd, Handle* oWriteHnd, Handle handleForSetInfo, SECURITY_ATTRIBUTES& saAttr);

	SizeType _readStdout(char* oBuf, SizeType nBytesToRead);

protected:
	Handle processHandle();

private:
	STARTUPINFO			_startupInfo	= { 0 };
	PROCESS_INFORMATION _procInfo		= { 0 };

	Handle _stdoutRead	= nullptr;
	Handle _stdoutWrite	= nullptr;	// useless, it will close after create

	Handle _stdinRead	= nullptr;	// useless, it will close after create
	Handle _stdinWrite	= nullptr;
};

template<size_t N, class ALLOC> inline
Process_Win32::SizeType 
Process_Win32::readStdout(Vector_T<char, N, ALLOC>& oBuf, SizeType nBytesToRead)
{
	oBuf.clear();
	oBuf.resize(nBytesToRead);
	auto nBytesRead = _readStdout(oBuf.data(), nBytesToRead);
	oBuf.resize(nBytesRead);
	return nBytesRead;
}

template<size_t N, class ALLOC> inline
u32		
Process_Win32::awaitAllStdout(Vector_T<char, N, ALLOC>& oBuf, u64 msTimeout, SizeType startBufSize)
{
	u32 rtcode = awaitReturncode(msTimeout);

	Vector_T<char, N, ALLOC> buf;
	SizeType nBytesRead		= 0;
	SizeType nBytesToRead	= math::nextPow2(startBufSize);
	do
	{
		nBytesRead = readStdout(buf, nBytesToRead);
		oBuf.appendRange(buf);

		if (nBytesToRead <= NumLimit<DWORD>::max())
			nBytesToRead = math::nextPow2(nBytesToRead);
	} while (nBytesRead != 0);

	return rtcode;
}

inline Process_Win32::Handle Process_Win32::processHandle() { return _procInfo.hProcess; }


#endif
}
#endif