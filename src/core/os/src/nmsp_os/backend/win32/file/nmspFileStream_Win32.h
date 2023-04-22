#pragma once

#include "nmsp_os/file/nmspFileStream_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- FileStream_Win32-Decl ---
#endif // 0
#if 1

using FileStream_CreateDesc_Win32 = FileStream_CreateDesc_Base;

class FileStream_Win32 : public FileStream_Base
{
public:
	using Base = FileStream_Base;

	using CreateDesc = FileStream_CreateDesc_Win32;

public:
	static NativeFd		kInvalid();
	static CreateDesc	makeCDesc();

public:
	FileStream_Win32() = default;
	FileStream_Win32(const CreateDesc& cd);

	~FileStream_Win32();

	bool isOpened() const;

private:
	NativeFd	_fd = kInvalid();
};


#endif

}

#endif