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

FileStream_Win32::CreateDesc	FileStream_Win32::makeCDesc()
{
	return CreateDesc{};
}

FileStream_Win32::FileStream_Win32(const CreateDesc& cd)
{
	open(cd);
}

FileStream_Win32::~FileStream_Win32()
{
	close();
}

void FileStream_Win32::open(const CreateDesc& cd)
{
	close();
	_filename = cd.filename;

	DWORD	create_flags	= 0;
	DWORD	access_flags	= 0;
	DWORD	share_flags		= 0;

	switch (cd.mode) 
	{
		case FileMode::CreateNew: 		{ create_flags |= CREATE_NEW;	 } break;
		case FileMode::OpenExists:		{ create_flags |= OPEN_EXISTING; } break;
		case FileMode::OpenOrCreate:	{ create_flags |= OPEN_ALWAYS;	 } break;
	}

	switch (cd.access) 
	{
		case FileAccess::Read:			{ access_flags |= GENERIC_READ;					} break;
		case FileAccess::ReadWrite:		{ access_flags |= GENERIC_READ | GENERIC_WRITE;	} break;
		case FileAccess::WriteOnly:		{ access_flags |= GENERIC_WRITE;				} break;
	}

	switch (cd.shareMode) 
	{
		case FileShareMode::None:		{ } break;
		case FileShareMode::Read:		{ share_flags |= FILE_SHARE_READ;						} break;
		case FileShareMode::ReadWrite:	{ share_flags |= FILE_SHARE_READ | FILE_SHARE_WRITE;	} break;
		case FileShareMode::Write:		{ share_flags |= FILE_SHARE_WRITE;						} break;
	}

	TempStringW_T<> filenameW;
	UtfUtil::convert(filenameW, cd.filename);

	_fd = ::CreateFile(filenameW.c_str(), access_flags, share_flags, nullptr, create_flags, FILE_ATTRIBUTE_NORMAL, nullptr );
	Util::throwIf(_fd == kInvalid(), "filename: {}", cd.filename);
}

void FileStream_Win32::close()
{
	if (!isOpened()) 
		return;

	BOOL ret = ::CloseHandle(_fd);
	throwIf(!ret, "{}", NMSP_SRCLOC);
	
	_fd = kInvalid();
}

void FileStream_Win32::flush()
{
	_checkFd();

	auto ret = ::FlushFileBuffers(_fd);
	Util::throwIf(!ret);
}

void FileStream_Win32::setFileSize(FileSize newSize)
{
	_checkFd();
	FileSize oldPos = getPos();
	setPos(newSize);
	::SetEndOfFile(_fd);

	if (oldPos < newSize)
		setPos(oldPos);
}

FileStream_Win32::FileSize FileStream_Win32::fileSize()
{
	_checkFd();

	DWORD high = 0;
	DWORD low  = ::GetFileSize(_fd, &high);
	throwIf(low == INVALID_FILE_SIZE, "{}", NMSP_SRCLOC);

	auto fileSize = sCast<FileSize>(high) << 32 | low;
	return fileSize;
}

void FileStream_Win32::setPos(FileSize pos)
{
	_checkFd();
	LONG high = sCast<LONG>(pos >> 32);
	LONG low  = sCast<LONG>(pos);
	::SetFilePointer( _fd, low, &high, FILE_BEGIN);
}

void FileStream_Win32::setPosFromEnd(FileSize pos)
{
	_checkFd();
	LONG high = sCast<LONG>(pos >> 32);
	LONG low  = sCast<LONG>(pos);
	::SetFilePointer( _fd, low, &high, FILE_END);
}

FileStream_Win32::FileSize FileStream_Win32::getPos()
{
	_checkFd();
	LONG high = 0;
	LONG low  = ::SetFilePointer(_fd, 0, &high, FILE_CURRENT);
	throwIf(low < 0 || high < 0, "{}", NMSP_SRCLOC);

	auto pos = sCast<FileSize>(low) | sCast<FileSize>(high) << 32;
	return pos;
}

void FileStream_Win32::readBytes(Span_T<u8> data)
{
	_checkFd();
	if (data.size() <= 0)
		return;
	
	throwIf(data.size() >= NumLimit<u32>::max(), "{}", NMSP_SRCLOC);

	DWORD dwSize = Util::castDWord(data.size());
	DWORD result;
	BOOL ret = ::ReadFile(_fd, data.data(), dwSize, &result, nullptr);
	Util::throwIf(!ret);
}

void FileStream_Win32::writeBytes(ByteSpan_T data)
{
	_checkFd();
	if (data.size() <= 0)
		return;

	throwIf(data.size() >= NumLimit<u32>::max(), "{}", NMSP_SRCLOC);

	DWORD dwSize = Util::castDWord(data.size());
	DWORD result;
	BOOL ret = ::WriteFile(_fd, data.data(), dwSize, &result, nullptr);
	Util::throwIf(!ret);
}

bool FileStream_Win32::isOpened() const
{
	return _fd != kInvalid();
}

const StringT& FileStream_Win32::filename() const
{
	return _filename;
}

FileStream_Win32::NativeFd FileStream_Win32::nativeFd() const
{
	return _fd;
}

void FileStream_Win32::_checkFd()
{
	//NMSP_ASSERT(_fd != kInvalid(), NMSP_SRCLOC);
	throwIf(_fd == kInvalid(), "{}", NMSP_SRCLOC);
}

#endif

}

#endif // 0
