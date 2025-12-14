#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#include <mutex>
#include <shared_mutex>

namespace nmsp {

#if 0
#pragma mark --- Mutex_Std-Impl ---
#endif // 0
#if 1

using Mutex_Std		= std::mutex;
using SMutex_Std	= std::shared_mutex;


#endif

}