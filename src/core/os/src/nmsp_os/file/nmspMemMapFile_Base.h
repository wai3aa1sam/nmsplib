#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspFileStream.h"

/*
references:
- src/core/file/MemMapFile.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- MemMapFile_Base-Decl ---
#endif // 0
#if 1

struct MemMapFile_CreateDesc_Base
{
	StrViewA_T		filename;
};

// interface only class
class MemMapFile_Base : public NonCopyable
{
public:
	using CreateDesc = MemMapFile_CreateDesc_Base;

	using Util		= OsTraits::Util;
	using NativeHnd	= OsTraits::NativeFd;
	using FileSize	= OsTraits::FileSize;
	using SizeType	= OsTraits::SizeType;

public:
	static NativeHnd	kInvalid();
	static CreateDesc	makeCDesc();

public:
	MemMapFile_Base() = default;
	MemMapFile_Base(const CreateDesc& cd);

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

protected:
	FileStream_T _fs;
};

#endif

}