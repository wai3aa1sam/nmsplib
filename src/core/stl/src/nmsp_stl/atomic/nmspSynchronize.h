#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include <future>


#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

namespace nmsp {

template<class T> using Atomic_T	= std::atomic<T>;
template<class T> using Future_T	= std::future<T>;
template<class T> using Promise_T	= std::promise<T>;

}