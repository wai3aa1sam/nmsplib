#pragma once

#include "../common/nmsp_stl_common.h"

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