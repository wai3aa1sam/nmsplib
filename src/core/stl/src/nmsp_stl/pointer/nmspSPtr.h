#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_CONTAINER

	#include "nmsp/nmspSPtr_Std.h"

	namespace nmsp {


	}

#elif NMSP_BUILD_STL_NMSP_CONTAINER || NMSP_STL_INTRUSIVE_S_PTR

	#include "nmsp/nmspSPtr_Nmsp.h"

	namespace nmsp {

	template<class T> using SPtr_Impl = SPtr_Nmsp<T>;

	}

#elif NMSP_BUILD_STL_EASTL_CONTAINER

	#include "eastl/nmspSPtr_Eastl.h"

	namespace nmsp {

	template<class T> using SPtr_Impl = SPtr_Eastl<T>;

	}

#else
	#error "unsupported stl build container"
#endif // 0

#endif

namespace nmsp {

template<class T> using SPtr_T = SPtr_Impl<T>;

template<class T> using SharedPtr_T = std::shared_ptr<T>;
template<class T, class... ARGS>
SharedPtr_T<T> makeShared(ARGS... args)
{
	T* p = NMSP_ALLOC(p, _alignTo(sizeof(T), NMSP_ALIGN_OF(T)));
	new (p) T(nmsp::forward<ARGS>(args)...);
	return SharedPtr_T<T>{p};
}

}