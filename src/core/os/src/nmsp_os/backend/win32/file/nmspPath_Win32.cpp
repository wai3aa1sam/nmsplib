#include "nmsp_os-pch.h"

#include "nmspPath_Win32.h"

#include "nmsp_os/file/nmspPath.h"

namespace nmsp {

void Path_Win32::setCurrentDir(StrViewA_T dir)
{
	auto dirW = UtfUtil::toTempStringW(dir);
	auto ret = ::SetCurrentDirectory(dirW.c_str());
	Util::throwIf(!ret, "currentDir: {} \n dir: {}", Path_Win32::getCurrentDir(), Path::realpath(dir));
}

StringT Path_Win32::getCurrentDir()
{
	StringT o;
	getCurrentDirTo(o);
	return o;
}

void Path_Win32::rename(StrViewA_T src, StrViewA_T dst)
{
	TempStringW_T<> srcW, dstW;
	UtfUtil::convert(srcW, src);
	UtfUtil::convert(dstW, dst);
	auto ret = ::_wrename(srcW.c_str(), dstW.c_str());
	Util::throwIf(ret != 0, "rename file {}->{}", src, dst);
}

bool Path_Win32::isExist(StrViewA_T path)
{
	TempStringW_T<> pathW;
	UtfUtil::convert(pathW, path);

	DWORD dwAttrib = ::GetFileAttributes(pathW.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES);
}

bool Path_Win32::isDirectory(StrViewA_T path)
{
	TempStringW_T<> pathW;
	UtfUtil::convert(pathW, path);

	DWORD dwAttrib = ::GetFileAttributes(pathW.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

bool Path_Win32::isFile(StrViewA_T path)
{
	TempStringW_T<> pathW;
	UtfUtil::convert(pathW, path);

	DWORD dwAttrib = ::GetFileAttributes(pathW.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES) && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

void Path_Win32::remove(StrViewA_T path)
{
	std::filesystem::remove(path.data());
}

void Path_Win32::removeAll(StrViewA_T path)
{
	std::filesystem::remove_all(path.data());
}

void Path_Win32::_create(StrViewA_T path)
{
	TempStringW_T<> pathW;
	UtfUtil::convert(pathW, path);
	auto ret = ::CreateDirectory(pathW.c_str(), nullptr);
	Util::throwIf(!ret, "ret: {}, create directory {}", ret, pathW);
}


}