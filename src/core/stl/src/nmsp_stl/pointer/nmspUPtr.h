#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_CONTAINER

	#include "nmsp/nmspUPtr_Std.h"

	namespace nmsp {


	}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

	#include "nmsp/nmspUPtr_Nmsp.h"

	namespace nmsp {

	}

#elif NMSP_BUILD_STL_EASTL_CONTAINER

	#include "eastl/nmspUPtr_Eastl.h"

	namespace nmsp {

	template<class T, class DELETER = eastl::default_delete<T> > using UPtr_Impl = UPtr_Eastl<T, DELETER>;

	}

#else
	#error "unsupported stl build container"
#endif // 0

#endif

namespace nmsp {

template<class T, class DELETER = eastl::default_delete<T>> using UPtr_T = UPtr_Impl<T, DELETER>;

}