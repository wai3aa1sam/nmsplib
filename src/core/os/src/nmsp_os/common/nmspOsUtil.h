#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#if NMSP_OS_WINDOWS

#include "nmsp_os/backend/win32/common/nmspOsUtil_Win32.h"

namespace nmsp {

using OsUtil_Impl	= OsUtil_Win32;

}

#else
#error "unsupported nmsp_os util build"
#endif // 0


namespace nmsp {

#if 0
#pragma mark --- OsUtil-Decl ---
#endif // 0
#if 1

struct OsUtil : public OsUtil_Impl
{
public:
	using Base = OsUtil_Impl;

	using Rect2f = Base::Rect2f;

public:
	OsUtil() = delete;

public:


};


#endif

}
