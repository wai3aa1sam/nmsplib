#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- stl_sync_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_SYNC

	#include "std/nmspMutex_Std.h"

	namespace nmsp {

	using Mutex_Impl	= Mutex_Std;
	using SMutex_Impl	= SMutex_Std;

	template<class T> using ULock_Impl = ULock_Std<T>;
	template<class T> using SLock_Impl = SLock_Std<T>;

	}

#elif NMSP_BUILD_STL_NMSP_SYNC

	#include "nmsp/nmspMutex_Nmsp.h"

	namespace nmsp {

	}


#elif NMSP_BUILD_STL_EASTL_SYNC

	#include "eastl/nmspMutex_Eastl.h"

	namespace nmsp {


	}

#else
	#error "unsupported stl sync build"
#endif // 0

#endif

namespace nmsp {

using Mutex_T	= Mutex_Impl;
using SMutex_T	= SMutex_Impl;

template<class T> using ULock_T = ULock_Impl<T>;
template<class T> using SLock_T = SLock_Impl<T>;

}