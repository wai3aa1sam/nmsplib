#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include <mutex>
#include <shared_mutex>

namespace nmsp {

#if 0
#pragma mark --- Mutex-Impl ---
#endif // 0
#if 1

using Mutex_Std		= std::mutex;
using SMutex_Std	= std::shared_mutex;

template<class T> using ULock_Std = std::unique_lock<T>;
template<class T> using SLock_Std = std::shared_lock<T>;

#endif

}