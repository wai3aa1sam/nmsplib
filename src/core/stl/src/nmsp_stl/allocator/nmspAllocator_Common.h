#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

static constexpr size_t s_kDefaultAlign = 8;

template<class T>
static constexpr T _alignTo(T n, T a) 
{
	static_assert(IsUnsigned<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
}

template<class T1, class T2> using CompressedPair = std::pair<T1, T2>;

}