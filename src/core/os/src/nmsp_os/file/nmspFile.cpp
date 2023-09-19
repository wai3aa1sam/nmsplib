#include "nmsp_os-pch.h"

#include "nmspFile.h"

#include "nmspMemMapFile.h"
#include "nmspPath.h"

namespace nmsp {

bool File::exists(StrViewA_T filename)
{
	return Path::isFile(filename);
}

void File::rename(StrViewA_T src, StrViewA_T dst)
{
	Path::rename(src, dst);
}

void File::writeBytes(StrViewA_T filename, ByteSpan_T data)
{
	FileStream_T fs;
	fs.openWrite(filename, true);
	fs.writeBytes(data);
}

void File::writeText(StrViewA_T filename, StrViewA_T text)
{
	FileStream_T fs;
	fs.openWrite(filename, true);
	fs.writeBytes(makeByteSpan(text));
}

char File::writeFile(StrViewA_T filename, ByteSpan_T data, bool createDir, bool logResult)
{
	char ret = '+';
	
	auto realPath = Path::realpath(filename);
	
	if (Path::isExist(realPath))
	{
		ret = 'U';
	}

	if (logResult)
	{
		_NMSP_LOG("[{}] {}, size={}", ret, realPath, data.size());
	}

	if (createDir)
	{
		auto dir = Path::dirname(realPath);
		if (!dir.is_empty())
		{
			Path::create(dir);
		}
	}
	
	writeBytes(filename, data);

	return ret;
}

char File::writeFile(StrViewA_T filename, StrViewA_T data, bool createDir, bool logResult)
{
	return writeFile(filename, makeByteSpan(data), createDir, logResult);
}

char File::writeFileIfChanged(StrViewA_T filename, ByteSpan_T data, bool createDir, bool logResult, bool logNoChange)
{
	char ret = '+';

	auto realPath = Path::realpath(filename);

	if (Path::isExist(realPath))
	{
		MemMapFile_T mmf;
		mmf.open(realPath);

		if (mmf.span() == data)
		{
			ret = '=';
		}
		else
		{
			ret = 'U';
		}
	}

	if (logResult)
	{
		if (ret != '=' || logNoChange)
		{
			_NMSP_LOG("[{}] {}, size={}", ret, realPath, data.size());
		}
	}

	if (ret == '=')
		return ret;
	return writeFile(filename, data, createDir, logResult);
}

char File::writeFileIfChanged(StrViewA_T filename, StrViewA_T data, bool createDir, bool logResult, bool logNoChange)
{
	return writeFileIfChanged(filename, makeByteSpan(data), createDir, logResult, logNoChange);
}



}

