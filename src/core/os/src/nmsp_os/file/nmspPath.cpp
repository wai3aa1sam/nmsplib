#include "nmsp_os-pch.h"

#include "nmspPath.h"

namespace nmsp {

#if 0
#pragma mark --- Path-Impl ---
#endif // 0
#if 1

void Path::create(StrViewA_T path)
{
	if (isExist(path)) 
		return;

	auto parent = dirname(path);
	if (parent.size()) 
	{
		create(parent); // create recursively
	}

	_create(path);
}

StrViewA_T Path::dirname(StrViewA_T path)
{
	auto* end	= path.end();
	auto* begin = path.begin();

	if (end == nullptr) 
		return StrViewA_T{};

	auto* p = end - 1;
	for (; p >= begin; p--) 
	{
		if (*p == '/' || *p == '\\') 
		{
			return StrViewA_T(begin, p - begin);
		}
	}

	return StrViewA_T{};
}

StrViewA_T Path::basename(StrViewA_T path)
{
	auto* end	= path.end();
	auto* begin = path.begin();

	if (end == nullptr) 
		return StrViewA_T();

	auto* p = end - 1;
	for (; p >= begin; p--) 
	{
		if (*p == '/' || *p == '\\') 
		{
			p++;
			return StrViewA_T(p, end - p);
		}
	}

	return StrViewA_T();
}

StrViewA_T Path::extension(StrViewA_T path)
{
	auto* end	= path.end();
	auto* begin = path.begin();

	if (end == nullptr) 
		return StrViewA_T{};

	auto* p = end - 1;
	for (; p >= begin; p--) 
	{
		if (*p == '.') 
		{
			p++;
			return StrViewA_T(p, end - p);
		}
	}

	return StrViewA_T{};
}

bool Path::isRealpath(StrViewA_T path)
{
	if (path.size() < 1)	return false;
	if (path[0] == '/')		return true;

	if (path.size() < 2)	return false;
	if (std::isalpha(path[0]) && path[1] == ':') return true;

	return false;
}


StringT 
Path::relative(StrViewA_T path, StrViewA_T base)
{
	StringT o;
	relativeTo(o, path, base);
	return o;
}

#endif // 1


}