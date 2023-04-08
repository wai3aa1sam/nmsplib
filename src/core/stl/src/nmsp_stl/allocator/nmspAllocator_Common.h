#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include "nmspAllocator_Base.h"

namespace nmsp {

static constexpr size_t s_kDefaultAlign = NMSP_ALIGN_OF(std::max_align_t);

template<class T>
static constexpr T _alignTo(T n, T a) 
{
	static_assert(IsUInt<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
}




}