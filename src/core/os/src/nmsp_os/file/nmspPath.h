#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/file/nmspPath_Win32.h"

	namespace nmsp {

	using Path_Impl				= Path_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/file/nmspPath_Linux.h"

	namespace nmsp {

	using Path_Impl				= Path_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif

namespace nmsp {

#if 0
#pragma mark --- Path-Decl ---
#endif // 0
#if 1

struct Path : public Path_Impl
{
public:
	using Base = Path_Impl;

public:
	using Util = typename Base::Util;

public:
	static void create(StrViewA_T path);

	static StrViewA_T	dirname		(StrViewA_T path);
	static StrViewA_T	basename	(StrViewA_T path);
	static StrViewA_T	extension	(StrViewA_T path);
	static StringT		realpath	(StrViewA_T path);

	template<size_t N, class ALLOC = DefaultAllocator> static void realpathTo(StringA_T<N, ALLOC>& o, StrViewA_T path);

	template<class STR> static void relativeTo(STR& out, StrViewA_T path, StrViewA_T base);
	StringT relative(StrViewA_T path, StrViewA_T base);

	static bool isRealpath(StrViewA_T path);
};

#endif

#if 0
#pragma mark --- Path-Impl ---
#endif // 0
#if 1

inline
StringT 
Path::realpath(StrViewA_T path)
{
	StringT o;
	realpathTo(o, path);
	return o;
}

template<size_t N, class ALLOC> inline 
void 
Path::realpathTo(StringA_T<N, ALLOC>& o, StrViewA_T path)
{
	o.clear();

	if (!path.size())
		return;

	auto& outStr = o;

	bool needSlash = false;
	if (isRealpath(path)) 
	{
		needSlash = (path[0] == '/'); //UNIX path need '/' at beginning
	}
	else
	{
		getCurrentDirTo(outStr);
		needSlash = true;
	}

	StrViewA_T p = path;
	while (p.size()) 
	{
		auto s = StrUtil::splitByChar(p, toStrView("\\/"));
		if (s.first == ".") 
		{
			//skip '.'
		}
		else if (!s.first.size()) 
		{
			//skip '/'
		}
		else if (s.first == "..") 
		{
			auto* parent = StrUtil::findCharFromEnd(outStr, toStrView("\\/"), false);
			if (parent == nullptr) 
			{
				outStr.clear(); //no more parent folder
				return;
			}

			outStr.resize(parent - outStr.data());
		}
		else
		{
			if (needSlash) 
			{
				outStr += '/';
			}
			outStr += s.first;
			needSlash = true;
		}
		p = s.second;
	}
}

template<class STR> inline 
void 
Path::relativeTo(STR& out, StrViewA_T path, StrViewA_T base)
{
	NMSP_TODO("replace std::filesystem impl");

	using FsPath = std::filesystem::path;
	FsPath fspath;
	fspath.assign(path.begin(), path.end());

	FsPath fsbase;
	fsbase.assign(base.begin(), base.end());

	FsPath dst = std::filesystem::relative(fspath, fsbase);

	out.clear();
	UtfUtil::convert(out, toStrViewW(dst.wstring()));
}


#endif


}