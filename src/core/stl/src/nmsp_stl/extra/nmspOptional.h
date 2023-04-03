#pragma once

#include "../common/nmsp_stl_common.h"

#include <EASTL/optional.h>

namespace nmsp {

template<class T> using Opt_T = ::eastl::optional<T>;

}