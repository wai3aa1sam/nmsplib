#pragma once

#include "../common/nmspOs_Common_Win32.h"

#include "nmsp_os/file/nmspMemMapFile_Base.h"

/*
references:
- src/core/file/MemMapFile.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- MemMapFile_Win32-Decl ---
#endif // 0
#if 1

using MemMapFile_CreateDesc_Win32 = MemMapFile_CreateDesc_Base;

class MemMapFile_Win32 : public MemMapFile_Base
{
public:
	using Base = MemMapFile_Base;

	using CreateDesc = MemMapFile_CreateDesc_Win32;

public:
	static NativeHnd	kInvalid();
	static CreateDesc	makeCDesc();

public:
	MemMapFile_Win32() = default;
	MemMapFile_Win32(const CreateDesc& cd);
	
	~MemMapFile_Win32();

	void open	(StrViewA_T filename);
	void open	(const CreateDesc& cd);
	void close	();

	const u8*	data() const;
	SizeType	size() const;

	ByteSpan_T span() const;
	operator ByteSpan_T();

	StrViewA_T strview() const;

	const StringT&	filename() const;

private:
	void _checkHnd();

private:
	NativeHnd _hnd = kInvalid();
	ByteSpan_T _span;
};


#endif

}

#endif