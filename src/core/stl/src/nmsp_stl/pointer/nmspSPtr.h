#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "nmsp/nmspSPtr_Std.h"

	namespace nmsp {


	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP || NMSP_STL_INTRUSIVE_S_PTR

	#include "nmsp/nmspSPtr_Nmsp.h"

	namespace nmsp {

	template<class T, class DELETER> using SPtr_Impl = SPtr_Nmsp<T, DELETER>;

	}

#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspSPtr_Eastl.h"

	namespace nmsp {

	template<class T, class DELETER> using SPtr_Impl = SPtr_Eastl<T>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T, class DELETER = DefaultDeleter<T> > using SPtr_T = SPtr_Impl<T, DELETER>;
template<class T, class... ARGS> inline
SPtr_T<T> 
makeSPtr_T(ARGS&&... args)
{
	T* p = NMSP_NEW(T)(nmsp::forward<ARGS>(args)...);
	return SPtr_T<T>{p};
}

template<class T> using SharedPtr_T = std::shared_ptr<T>;
template<class T, class... ARGS> inline
SharedPtr_T<T> 
makeSharedPtr_T(ARGS&&... args)
{
	return std::make_shared<T>(nmsp::forward<ARGS>(args)...);
	/*T* p = NMSP_NEW(T)(nmsp::forward<ARGS>(args)...);
	return SharedPtr_T<T>{p};*/
}

}