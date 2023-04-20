#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#if 0
#pragma mark --- stl_sync_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_SYNC

	#include "std/nmspCondVar_Std.h"

	namespace nmsp {

	using CondVar_Impl	= CondVar_Std;
	using CondVarA_Impl	= CondVarA_Std;

	}

#elif NMSP_STL_BUILD_NMSP_SYNC

	#include "nmsp/nmspCondVar_Nmsp.h"

	namespace nmsp {

	}


#elif NMSP_STL_BUILD_EASTL_SYNC

	#include "eastl/nmspCondVar_Eastl.h"

	namespace nmsp {


	}

#else
	#error "unsupported stl sync build"
#endif // 0

#endif

namespace nmsp {

using CondVar_T		= CondVar_Impl;
using CondVarA_T	= CondVarA_Impl;

}