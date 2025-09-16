#pragma once

#include "../common/nmsp_stl_common.h"


#if 0
#pragma mark --- stl_container_backend_switch_incl-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

#elif NMSP_STL_BUILD_CONTAINER_NMSP

#elif NMSP_STL_BUILD_CONTAINER_EASTL

#include "EASTL/sort.h"

#else
#error "nmspAlgorithm.h should have backend switch"
#endif // NMSP_STL_BUILD_CONTAINER_EASTL

#endif

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

namespace nmsp 
{

#if NMSP_STL_BUILD_CONTAINER_STD



#elif NMSP_STL_BUILD_CONTAINER_NMSP


template<class T> inline
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

template<class IN_ITER, class T> inline
IN_ITER 
find(IN_ITER first, IN_ITER last, const T& v)
{
	return eastl::find(first, last, v);
}

template<class IN_ITER, class PRED> inline
IN_ITER 
find_if(IN_ITER first, IN_ITER last, PRED pred)
{
	return eastl::find_if(first, last, nmsp::move(pred));
}

template<class BI_DIR_ITER> inline
void 
reverse(BI_DIR_ITER first, BI_DIR_ITER last)
{
	return eastl::reverse(first, last);
}

template<class FORWARD_ITER, class T> inline
void 
remove(FORWARD_ITER first, FORWARD_ITER last, const T& v)
{
	eastl::remove(first, last, v);
}

template<class TRndAccessIter> inline
void 
sort(TRndAccessIter first, TRndAccessIter last)
{
	eastl::sort(first, last);
}

template<class TRndAccessIter, class TComparePred> inline
void 
sort(TRndAccessIter first, TRndAccessIter last, TComparePred compare)
{
	eastl::sort(first, last, compare);
}

#else
	#error "nmspAlgorithm.h should have backend switch"
#endif // NMSP_STL_BUILD_CONTAINER_EASTL

#endif
}

