#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"
#include "nmspScopedLock.h"

namespace nmsp
{

#if 0
#pragma mark --- nmspCondVar_T-Impl ---
#endif // 0
#if 1

class CondVar_T : public NonCopyable
{
public:
	using This			= CondVar_T;
	using Mutex			= Mutex_T;
	using ScopedLock	= ScopedLock_Base<Mutex>;
	using Int			= i64;

public:
	void	broadcast();
	void	signal();

	void	wait(		ScopedLock& locked);
	bool	timed_wait(	ScopedLock& locked, Int waitMs);

private:
	// use struct CondVar_Data_Std : public std::condition_variable {} instead? 
	// it is good when teamwork to separate file, but CondVar_Interface is shit
	#if NMSP_OS_BUILD_MUTEX_STD
	std::condition_variable _cv;
	#else
	#error "unsupported nmsp_os CondVar_T build"
	#endif // 0
};

#endif // 1

}