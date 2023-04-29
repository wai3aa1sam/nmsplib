#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"

#include "nmsp_os/file/base/nmspPath_Base.h"

/*
references:
- src/core/file/Directory.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- Path_Win32-Decl ---
#endif // 0
#if 1

struct Path_Win32 : public Path_Base
{
public:
	using Base = Path_Base;

	using Util = typename Base::Util;

public:
	Path_Win32() = delete;

public:
	static void create(StrViewA_T path);

	static StrViewA_T	dirname		(StrViewA_T path);
	static StrViewA_T	basename	(StrViewA_T path);
	static StrViewA_T	extension	(StrViewA_T path);
	static StringT		realpath	(StrViewA_T path);
	
	template<size_t N> static void	realpathTo (StringA_T<N>& o, StrViewA_T path);
	//template<size_t N> static void	realpathToW(StringW_T<N>& o, StrViewW_T path);

	static bool isRealpath	(StrViewA_T path);

	//--- Platform Dependent
	static void		setCurrentDir(StrViewA_T dir);
	static StringT	getCurrentDir();

	static void rename(StrViewA_T src, StrViewA_T dst);

	static bool isExist		(StrViewA_T path);
	static bool isDirectory	(StrViewA_T path);
	static bool isFile		(StrViewA_T path);

	static void remove		(StrViewA_T path);
	static void removeAll	(StrViewA_T path);

protected:
	static void _create(StrViewA_T path);

	//template<class STR, class VIEW> static void realpathTo_T(STR& o, VIEW path);
};


#endif


}

#endif