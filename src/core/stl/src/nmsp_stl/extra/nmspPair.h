#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

template<class T1, class T2> using Pair_T = eastl::pair<T1, T2>;

//template<class T1, class T2> inline
//Pair<T1, T2> makePair(T1 t1, T2 t2)		{ return Pair<T1, T2>{t1, t2}; }

template<class T1, class T2> inline
Pair_T<Decay<T1>, Decay<T2>> makePair(T1&& t1, T2&& t2) 
{
	using T1_ = Decay<T1>;
	using T2_ = Decay<T2>;
	//return Pair<T1_, T2_>{forward(t1), forward(t2)}; 
	return eastl::make_pair(forward<T1>(t1), forward<T2>(t2)); 

}

}