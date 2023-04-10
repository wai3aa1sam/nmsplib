#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include <thread>
#include <mutex>

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


class CallOnce;


#endif

#if 0
#pragma mark --- AtomicUtil-Impl ---
#endif // 0
#if 1


#if 0
#pragma mark --- CallOnce-Impl ---
#endif // 0
#if 1

class CallOnce
{
public:
	CallOnce() = default;

	template<class CALLABLE, class... ARGS>
	CallOnce(CALLABLE&& f, ARGS&&... args)
	{
		callOnce(f, std::forward<ARGS>(args)...);
	}

	template<class CALLABLE, class... ARGS>
	void callOnce(CALLABLE&& f, ARGS&&... args)
	{
		std::call_once(_flag, f, std::forward<ARGS>(args)...);
	}

private:
	std::once_flag _flag;
};

#endif

#endif

}
