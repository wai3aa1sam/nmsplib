#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspFileUsage.h"

/*
references:
- src/core/file/File.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- File-Decl ---
#endif // 0
#if 1

struct File : public NonCopyable
{
public:
	using Util		= OsTraits::Util;

public:
	File() = delete;

public:
	static bool exists(StrViewA_T filename);
	static void rename(StrViewA_T src, StrViewA_T dst);

	static void	writeBytes(StrViewA_T filename, ByteSpan_T data);
	static void writeText (StrViewA_T filename, StrViewA_T text);

	static char writeFile(StrViewA_T filename, ByteSpan_T data, bool createDir, bool logResult = true);
	static char writeFile(StrViewA_T filename, StrViewA_T data, bool createDir, bool logResult = true);

	template<size_t N>	static void readFile (StrViewA_T filename, Vector_T<u8, N>&	outData);
	template<size_t N>	static void readFile (StrViewA_T filename, StringA_T<N>&	outData);

	static char writeFileIfChanged(	StrViewA_T filename, 
		ByteSpan_T data, 
		bool createDir, 
		bool logResult = true, 
		bool logNoChange = false);

	static char writeFileIfChanged(	StrViewA_T filename, 
		StrViewA_T data, 
		bool createDir, 
		bool logResult = true, 
		bool logNoChange = false);

private:
	template<class T> static void _readFile (StrViewA_T filename, T& outData);
};

#endif


#if 0
#pragma mark --- File-Decl ---
#endif // 0
#if 1

template<size_t N> inline
void readFile(StrViewA_T filename, Vector_T<u8, N>& outData)
{
	_readFile(filename, outData);
}

template<size_t N> inline
void File::readFile(StrViewA_T filename, StringA_T<N>& outData)
{
	_readFile(filename, outData);
}

template<class T> inline
void File::_readFile(StrViewA_T filename, T& outData)
{
	FileStream_T fs;
	fs.openRead(filename);
	auto size = fs.fileSize();
	throwIf(size > NumLimit<OsTraits::FileSize>::max(), "{}", NMSP_SRCLOC);

	outData.resize(size);

	size_t sizeInBytes = sizeof(typename T::ValueType) * outData.size();
	Span_T<u8> span{reinCast<u8*>(outData.data(), sizeInBytes)};
	fs.readBytes(span);
}

#endif


}

