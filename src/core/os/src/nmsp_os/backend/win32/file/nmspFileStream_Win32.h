#pragma once

#include "../common/nmspOs_Common_Win32.h"

#include "nmsp_os/file/nmspFileStream_Base.h"

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
	FileSize filesize();

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


#endif

}

#endif