#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include <thread>

#if 0
#pragma mark --- stl_sync_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	#include "nmsp/win32/nmspAtomicUtil_Win32.h"
#else
	#error "unsupported stl sync build"
#endif // 0

#endif

namespace nmsp {

#if 0
#pragma mark --- AtomicUtil-Decl ---
#endif // 0
#if 1

size_t logicalThreadCount();

#endif

#if 0
#pragma mark --- AtomicUtil-Impl ---
#endif // 0
#if 1

NMSP_NODISCARD inline size_t logicalThreadCount()
{
	return std::thread::hardware_concurrency();
}

}
#endif
