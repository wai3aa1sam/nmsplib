#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmsp_os/file/nmspFileUsage.h"

/*
references:
- src/core/file/FileStream.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- FileStream_Base-Decl ---
#endif // 0
#if 1

struct FileStream_CreateDesc_Base
{
	StrViewA_T		filename;
	FileMode		mode;
	FileAccess		access;
	FileShareMode	shareMode;
};

// interface only class
class FileStream_Base : public NonCopyable
{
public:
	using CreateDesc = FileStream_CreateDesc_Base;

	using Util		= OsTraits::Util;
	using NativeFd	= OsTraits::NativeFd;
	using FileSize	= OsTraits::FileSize;


public:
	static NativeFd		kInvalid();
	static CreateDesc	makeCDesc();

public:
	FileStream_Base() = default;
	FileStream_Base(const CreateDesc& cd);

	void openRead	(StrViewA_T filename);
	void openAppend	(StrViewA_T filename);
	void openWrite	(StrViewA_T filename, bool truncate);

	void open	(const CreateDesc& cd);
	void close	();
	void flush	();

	void		setFileSize(FileSize newSize);
	FileSize	fileSize();

	void		setPos		 (FileSize pos);
	void		setPosFromEnd(FileSize pos);
	FileSize	getPos();

	void readBytes	(Span_T<u8> data);
	void writeBytes	(ByteSpan_T data);

	bool isOpened() const;

	const StringT&	filename() const;
	NativeFd		nativeFd() const;

private:
	void _checkFd();

protected:
	StringT		_filename;
};

#endif

}