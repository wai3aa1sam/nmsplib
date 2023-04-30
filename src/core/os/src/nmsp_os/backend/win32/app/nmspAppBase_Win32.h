#pragma once

#include "nmsp_os/backend/win32/common/nmspOs_Common_Win32.h"
//#include "nmsp_os/app/AppBase_Base.h"

namespace nmsp {

class AppBase_Win32 : public NonCopyable {
public:
	using Util = OsTraits::Util;

public:
	StringT	getExecutableFilename();

protected:

};

}