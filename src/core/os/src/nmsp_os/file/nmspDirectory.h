#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspFileUsage.h"

/*
references:
- src/core/file/Directory.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- Directory-Decl ---
#endif // 0
#if 1


struct Directory : public NonCopyable
{
public:
	using Util		= OsTraits::Util;

public:
	Directory() = delete;
	
public:
	static bool isExist(StrViewA_T filename);
	static void rename(StrViewA_T src, StrViewA_T dst);
	
	static void		setCurrent(StrViewA_T dir);
	static StringT	getCurrent();

};

#endif

}