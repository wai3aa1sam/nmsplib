#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"
#include "../nmspPointer_Common.h"

namespace nmsp {

#if 0
#pragma mark --- UPtr_Eastl-Decl ---
#endif // 0
#if 1

template<class T, class DELETER = eastl::default_delete<T> > using UPtr_Eastl = eastl::unique_ptr<T, DELETER>;

#endif


}