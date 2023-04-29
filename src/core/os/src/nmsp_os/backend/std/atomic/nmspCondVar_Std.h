#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#include <condition_variable>

namespace nmsp {

#if 0
#pragma mark --- CondVar_Std-Impl ---
#endif // 0
#if 1

using CondVar_Std	= std::condition_variable;
using CondVarA_Std	= std::condition_variable_any;

#endif


}