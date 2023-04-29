#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_os-config.h"
#include "nmsp_os/common/base/nmspOsTraits_Base.h"

#if 0
#pragma mark --- nmsp_os_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	
	#include "nmsp_os/backend/win32/common/nmspOsTraits_Win32.h"

	namespace nmsp {

	using OsDefaultTraits_Impl = OsDefaultTraits_Win32;

	}

#elif NMSP_OS_LINUX

	#include "nmsp_os/backend/linux/common/nmspOsTraits_Linux.h"

	namespace nmsp {

	using OsDefaultTraits_Impl = OsDefaultTraits_Linux;

	}

#else
	#error "--- error: nmsp_os_backend_switch"
#endif // NMSP_OS_NMSP

#endif


namespace nmsp {



#if 0
#pragma mark --- OsTraits-Impl ---
#endif // 0
#if 1

using OsDefaultTraits_T = OsDefaultTraits_Impl;

#if !NMSP_OS_CUSTOM_TRAITS

using OsTraits = OsDefaultTraits_T;

#else

#endif // 

#endif

}
