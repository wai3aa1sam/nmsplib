#pragma once

#include "../common/nmsp_stl_common.h"


#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1


namespace nmsp 
{

#if NMSP_STL_BUILD_CONTAINER_STD



#elif NMSP_STL_BUILD_CONTAINER_NMSP


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


#elif NMSP_STL_BUILD_CONTAINER_EASTL

template<class IN_ITER, class PRED>
IN_ITER find_if(IN_ITER first, IN_ITER last, PRED pred)
{
	return eastl::find_if(first, last, nmsp::move(pred));
}

#else
	#error "nmspAlgorithm.h should have backend switch"
#endif // NMSP_STL_BUILD_CONTAINER_EASTL

#endif
}

