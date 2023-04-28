#include "nmsp_os-pch.h"

#include "nmspMemMapFile_Win32.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- MemMapFile_Win32-Impl ---
#endif // 0
#if 1

MemMapFile_Win32::NativeHnd nmsp::MemMapFile_Win32::kInvalid()
{
	return nullptr;
}

MemMapFile_Win32::CreateDesc MemMapFile_Win32::makeCDesc()
{
	return CreateDesc{};
}

MemMapFile_Win32::MemMapFile_Win32(const CreateDesc& cd)
{
	open(cd);
}

MemMapFile_Win32::~MemMapFile_Win32()
{
	close();
}

void MemMapFile_Win32::open(StrViewA_T filename)
{
	auto cd = makeCDesc();
	cd.filename = filename;
	open(cd);
}

void MemMapFile_Win32::open(const CreateDesc& cd)
{
	close();
	_fs.openRead(cd.filename);

	throwIf(_fs.fileSize() >= NumLimit<SizeType>::max(), "memmap file size too larget");

	auto size = sCast<SizeType>(_fs.fileSize());
	if (size <= 0) 
		return;

	_hnd = ::CreateFileMapping(_fs.nativeFd(), nullptr, PAGE_READONLY, 0, 0, nullptr);
	throwIf(!_hnd, "{}", NMSP_SRCLOC);

	auto* data = reinterpret_cast<u8*>(::MapViewOfFile(_hnd, FILE_MAP_READ, 0, 0, 0));
	throwIf(!data, "{}", NMSP_SRCLOC);

	_span = ByteSpan_T(data, size);
}

void MemMapFile_Win32::close()
{
	if (_span.size() <= 0) 
		return;

	::UnmapViewOfFile(_span.data());

	if (_hnd) 
	{
		::CloseHandle(_hnd);
		_hnd = nullptr;
	}

	_span = ByteSpan_T{};
	_fs.close();
}

const u8* MemMapFile_Win32::data() const
{
	return _span.data();
}

MemMapFile_Win32::SizeType MemMapFile_Win32::size() const
{
	return _span.size();
}

ByteSpan_T MemMapFile_Win32::span() const
{
	return _span;
}

MemMapFile_Win32::operator ByteSpan_T()
{
	return _span;
}

StrViewA_T MemMapFile_Win32::strview() const
{
	return makeStrView(_span);
}

const StringT& MemMapFile_Win32::filename() const
{
	return _fs.filename();
}

void MemMapFile_Win32::_checkHnd()
{
	NMSP_ASSERT(_hnd != kInvalid(), "{}", NMSP_SRCLOC);
}

#endif

}

#endif // 0
