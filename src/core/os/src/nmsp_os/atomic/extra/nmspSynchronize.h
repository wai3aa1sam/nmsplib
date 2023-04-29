#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#include <future>

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

#if NMSP_OS_BUILD_SYNC_STD

namespace nmsp {

template<class T> using Future_T	= std::future<T>;
template<class T> using Promise_T	= std::promise<T>;

}

#elif NMSP_OS_BUILD_SYNC_NMSP



#else

#error "nmsp_os build sync"

#endif // NMSP_OS_BUILD_SYNC_STD
