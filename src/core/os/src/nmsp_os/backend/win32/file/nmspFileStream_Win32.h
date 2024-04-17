#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"

#include "nmsp_os/file/base/nmspFileStream_Base.h"

/*
references:
- src/core/file/FileStream.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

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

	void openRead	(StrViewA_T filename);
	void openAppend	(StrViewA_T filename);
	void openWrite	(StrViewA_T filename, bool truncate);

	void open	(const CreateDesc& cd);
	void close	();
	void flush	();

	void setFileSize(FileSize newSize);
	FileSize fileSize();

	void		setPos		 (FileSize pos);
	void		setPosFromEnd(FileSize pos);
	FileSize getPos();

	void readBytes	(Span_T<u8> data);
	void writeBytes	(ByteSpan_T data);

	bool isOpened() const;

	const StringT&	filename() const;
	NativeFd		nativeFd() const;

private:
	void _checkFd();

private:
	NativeFd	_fd = kInvalid();
};

#if 0
#pragma mark --- ScopedFileStreamLock_Win32-Decl ---
#endif // 0
#if 1

/*
	TODO: temporary
*/
class ScopedFileStreamLock_Win32 : public NonCopyable
{
public:
	using Util		= Util_Win32;
	using FileSize	= FileStream_Win32::FileSize;

public:
	ScopedFileStreamLock_Win32(FileStream_Win32* fs_);
	~ScopedFileStreamLock_Win32();

private:
	FileStream_Win32*	_fs = nullptr;
	FileSize			_size = 0;
};

#endif

#endif

}

#endif