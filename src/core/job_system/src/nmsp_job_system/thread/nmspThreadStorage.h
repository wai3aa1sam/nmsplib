#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmsp_job_system/allocator/nmspFrameAllocator.h"

namespace nmsp {

#if 0
#pragma mark --- ThreadStorage_T-Decl ---
#endif // 0
#if 1

class ThreadStorage_T
{
public:
	using JobHandle			= JobHandle_T;
	using FrameAllocator	= FrameAllocator_T<JobSystemTraits::s_kMaxFrameInFlightCount>;
	using JobAllocator		= FrameAllocator::JobAllocator;

public:
	friend class JobSystem_T;

public:
	ThreadStorage_T() = default;
	~ThreadStorage_T() = default;
	
	void nextFrame();

	Random_T& random();
	FrameAllocator& frameAllocator();

private:
	Random_T _rnd;

	// allocators
	FrameAllocator _frameAllocator;
};
#endif

#if 0
#pragma mark --- ThreadStorage_T-Impl ---
#endif // 0
#if 1

//inline ThreadStorage_T::JobHandle ThreadStorage_T::allocateJob()			{ return jobAllocator().alloc(); }


inline
void ThreadStorage_T::nextFrame()
{
	_frameAllocator.nextFrame();
}

inline
Random_T& ThreadStorage_T::random()
{
	return _rnd;
}

inline
ThreadStorage_T::FrameAllocator& ThreadStorage_T::frameAllocator()
{
	return _frameAllocator;
}

#endif

}