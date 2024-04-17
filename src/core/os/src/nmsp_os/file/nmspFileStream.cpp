#include "nmsp_os-pch.h"

#include "nmspFileStream.h"

namespace nmsp {

void FileStream_T::openRead(StrViewA_T filename)
{
	auto cd = makeCDesc();
	cd.filename		= filename;
	cd.mode			= FileMode::OpenExists;
	cd.access		= FileAccess::Read;
	cd.shareMode	= FileShareMode::Read;
	open(cd);
}

void FileStream_T::openAppend(StrViewA_T filename)
{
	auto cd = makeCDesc();
	cd.filename		= filename;
	cd.mode			= FileMode::OpenOrCreate;
	cd.access		= FileAccess::ReadWrite;
	cd.shareMode	= FileShareMode::Read;
	open(cd);
}

void FileStream_T::openWrite(StrViewA_T filename, bool truncate)
{
	auto cd = makeCDesc();
	cd.filename		= filename;
	cd.mode			= FileMode::OpenOrCreate;
	cd.access		= FileAccess::ReadWrite;
	cd.shareMode	= FileShareMode::Read;
	open(cd);
	if (truncate)
	{
		setFileSize(0);
	}
}

ScopedFileStreamLock_T 
FileStream_T::scopedLock()
{
	return ScopedFileStreamLock_T(this);
}


}