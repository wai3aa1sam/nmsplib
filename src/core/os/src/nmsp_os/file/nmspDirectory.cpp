#include "nmsp_os-pch.h"

#include "nmspDirectory.h"

#include "nmspPath.h"

namespace nmsp {

bool Directory::isExist(StrViewA_T filename)
{
	return Path::isDirectory(filename);
}

void Directory::rename(StrViewA_T src, StrViewA_T dst)
{
	Path::rename(src, dst);
}

void Directory::setCurrent(StrViewA_T dir)
{
	Path::setCurrentDir(dir);
}

StringT Directory::getCurrent()
{
	return Path::getCurrentDir();
}

}
