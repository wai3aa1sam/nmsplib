#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

template <typename ITER>
struct Iter_Traits
{
	using ValueType = typename ITER::value_type;
};

template <typename T>
struct Iter_Traits<T*>
{
	using ValueType = T;
};

template <typename T>
struct Iter_Traits<const T*>
{
	using ValueType = T;
};


}