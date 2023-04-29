#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include <nmsp_stl/string/nmspStrUtil.h>

/*
references:
- src/core/file/Directory.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- Path_Base-Decl ---
#endif // 0
#if 1

struct Directory;

// interface only class
struct Path_Base : public NonCopyable
{
public:
	using Util		= OsTraits::Util;
	
public:
	Path_Base() = delete;
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