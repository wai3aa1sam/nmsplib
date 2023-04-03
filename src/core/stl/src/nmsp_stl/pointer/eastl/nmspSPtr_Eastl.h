#pragma once

#include "../nmspPointer_Common.h"

#include <EASTL/shared_ptr.h>

namespace nmsp {

#if 0
#pragma mark --- SPtr_Eastl-Decl ---
#endif // 0
#if 1

template<class T> using SPtr_Eastl = eastl::shared_ptr<T>;

#endif


}