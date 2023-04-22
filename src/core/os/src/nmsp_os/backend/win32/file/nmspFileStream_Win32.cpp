#include "nmsp_os-pch.h"

#include "nmspFileStream_Win32.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- FileStream_Win32-Impl ---
#endif // 0
#if 1

FileStream_Win32::NativeFd		FileStream_Win32::kInvalid()
{
	return INVALID_HANDLE_VALUE;
}

FileStream_Win32::CreateDesc	FileStream_Win32::makeCD()
{
	return CreateDesc{};
}

FileStream_Win32::FileStream_Win32(const CreateDesc& cd)
{
	cd.filename;
}

FileStream_Win32::~FileStream_Win32()
{

}

#endif

}

#endif // 0
