#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- nmsp_os_atm_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_BUILD_CONDVAR_STD

	#include "nmsp_os/backend/std/atomic/nmspAtomicPrimitive_Std.h"

	namespace nmsp {

	template<class T> using Atm_Impl	= Atm_Std<T>;

	}

#elif NMSP_OS_BUILD_CONDVAR_NMSP

	#if NMSP_OS_WINDOWS

	#include "nmsp_os/backend/win32/atomic/nmspAtomicPrimitive_Win32.h"

	namespace nmsp {

	template<class T> using Atm_Impl	= Atm_Win32<T>;

	}

	#else
	#error "unsupported nmsp_os atm build"
	#endif // 0

#endif // 0


#else
	#error "unsupported nmsp_os atm build"
#endif // 0

namespace nmsp {

template<class T> using Atm_T = Atm_Impl<T>;

}