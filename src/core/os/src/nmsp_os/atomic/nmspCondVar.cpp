
#include "nmspCondVar.h"

#if NMSP_OS_BUILD_MUTEX_STD

namespace nmsp
{

#if 0
#pragma mark --- nmspCondVar_T-Impl ---
#endif // 0
#if 1

void
CondVar_T::broadcast()
{
	_cv.notify_all();
}

void
CondVar_T::signal()
{
	_cv.notify_one();
}

void
CondVar_T::wait(ScopedLock& lock)
{
	lock.mutex();
	_cv.wait(lock._lock);
}

bool
CondVar_T::timed_wait(ScopedLock& lock, Int waitMs)
{
	auto t = std::chrono::milliseconds(waitMs);
	return _cv.wait_for(lock._lock, t) == std::cv_status::no_timeout;
}

#endif // 1

}

#endif // NMSP_OS_BUILD_MUTEX_STD
