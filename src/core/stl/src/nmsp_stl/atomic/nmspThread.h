#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- stl_thread_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_THREAD

	#include "std/nmspThread_Std.h"

	namespace nmsp {

	using Thread_Impl	= Thread_Std;
	using ThreadA_Impl	= ThreadA_Std;

	}

#elif NMSP_BUILD_STL_NMSP_THREAD

	#include "nmsp/nmspThread_Nmsp.h"

	namespace nmsp {

	using Thread_Impl = Thread_Nmsp;

	}


#elif NMSP_BUILD_STL_EASTL_THREAD

	#include "eastl/nmspThread_Eastl.h"

	namespace nmsp {


	}

#else
	#error "unsupported stl sync build"
#endif // 0

#endif

namespace nmsp {

using BasicThread = Thread_Impl;

#if 0
#pragma mark --- Thread-Decl ---
#endif // 0
#if 1

class Thread : public BasicThread
{
public:
	using Base = BasicThread;
	using This = Thread;
public:
	using Base::CreateDesc;

public:

private:

};

#endif


#if 0
#pragma mark --- Thread-Impl ---
#endif // 0
#if 1



#endif

}
