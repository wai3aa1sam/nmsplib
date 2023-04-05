#pragma once

#include "../common/nmsp_stl_common.h"


#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_CONTAINER



#elif NMSP_BUILD_STL_NMSP_CONTAINER

	namespace nmsp {

	template<class T>
	T min(const T& a_, const T& b_)
	{
		return b_ < a_ ? b_ : a_;
	}

	template<class ITER, class T> inline
	ITER find(ITER beg, ITER end, const T& v)
	{
		using ValueType = typename Iter_Traits<ITER>::ValueType;

		for (; beg != end; ++beg)
			if (*beg == v)
				break;
		return beg;
	}

	}

#elif NMSP_BUILD_STL_EASTL_CONTAINER


#else
	#error "nmspAlgorithm.h should have backend switch"
#endif // NMSP_BUILD_STL_EASTL_CONTAINER

#endif

