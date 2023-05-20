#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmsp_job_system/allocator/nmspJobAllocator.h"

namespace nmsp {


#if 0
#pragma mark --- FrameAllocator_T-Impl
#endif // 0
#if 1
template<size_t FRAME_IN_FLIGHT_COUNT> class FrameAllocatorFrameStorage_T;

template<size_t FRAME_IN_FLIGHT_COUNT = JobSystemTraits::s_kMaxFrameInFlightCount>
class FrameAllocator_T : public NonCopyable // Allocator_Base<FrameAllocator_T<FRAME_IN_FLIGHT_COUNT> >
{
public:
	using FrameAllocatorFrameStorage = FrameAllocatorFrameStorage_T<FRAME_IN_FLIGHT_COUNT>;

	using JobHandle		= JobHandle_T;
	using JobAllocator	= JobAllocator_T;

public:
	static constexpr size_t s_kMaxFrameInFlightCount = FRAME_IN_FLIGHT_COUNT;

public:
	FrameAllocator_T();
	~FrameAllocator_T();

	void clearAll();
	void nextFrame();

	JobHandle allocJob();
	JobHandle allocJobDep();

	// this will have race condiiton since the lock is f
	//JobAllocator& jobAllocator();
	//JobAllocator& jobDependencyAllocator();

private:
	template<class T> void clear(T& iFrame_data);

private:
	SMutexProtected_T<int>	_iFrame;
	JobAllocator			_jobAllocators[s_kMaxFrameInFlightCount];
	JobAllocator			_jobDepAllocators[s_kMaxFrameInFlightCount];

	// SMutexProtected_T<FrameAllocatorFrameStorage> _storage;
};

#endif


#if 0
#pragma mark --- FrameAllocatorFrameStorage_T-Impl
#endif // 0
#if 1

template<size_t FRAME_IN_FLIGHT_COUNT = JobSystemTraits::s_kMaxFrameInFlightCount>
class FrameAllocatorFrameStorage_T
{
public:
	using JobHandle		= JobHandle_T;
	using JobAllocator	= JobAllocator_T;

public:
	static constexpr size_t s_kMaxFrameInFlightCount = FRAME_IN_FLIGHT_COUNT;

public:
	void nextFrame();
	JobAllocator& jobAllocator();
	JobAllocator& jobDependencyAllocator();

private:
	int iFrame = 0;
	JobAllocator _jobAllocators[s_kMaxFrameInFlightCount];
	JobAllocator _jobDepAllocators[s_kMaxFrameInFlightCount];
};

#endif


#if 0
#pragma mark --- FrameAllocator_T-Impl
#endif // 0
#if 1

template<size_t FN> inline
FrameAllocator_T<FN>::FrameAllocator_T()
{
	for (size_t i = 0; i < s_kMaxFrameInFlightCount; i++)
	{
		//_jobAllocators->alloc
	}
}

template<size_t FN> inline
FrameAllocator_T<FN>::~FrameAllocator_T() { clearAll(); }

template<size_t FN> inline
void FrameAllocator_T<FN>::clearAll()
{
	auto iFrame_data = _iFrame.scopedULock();
	auto iFrame = *iFrame_data; (void)iFrame;

	for (size_t i = 0; i < s_kMaxFrameInFlightCount; i++)
	{
		_jobAllocators[i].clear();
		_jobDepAllocators[i].clear();
	}
}

template<size_t FN> inline
void FrameAllocator_T<FN>::nextFrame() 
{
	//NMSP_ASSERT(false, "currently have race condition, when the job is allocating job between frame.");
	// no share lock, then the job may allocating and clear immediately
	auto iFrame_data = _iFrame.scopedULock();
	auto& iFrame = *iFrame_data;

	//_iFrame.store((_iFrame.load() + 1) % s_kFrameCount);
	iFrame = (iFrame + 1) % s_kMaxFrameInFlightCount;

	// race condition (if no lock)
	clear(iFrame_data);
}

template<size_t FN> inline
typename FrameAllocator_T<FN>::JobHandle FrameAllocator_T<FN>::allocJob()	
{ 
	auto iFrame_data	= _iFrame.scopedSLock(); 
	int iFrame			= *iFrame_data; 
	return _jobAllocators[iFrame].alloc(); 
}

template<size_t FN> inline
typename FrameAllocator_T<FN>::JobHandle FrameAllocator_T<FN>::allocJobDep()	
{ 
	auto iFrame_data	= _iFrame.scopedSLock(); 
	int iFrame			= *iFrame_data; 
	return _jobAllocators[iFrame].alloc(); 
}

template<size_t FN> 
template<class T> inline
void FrameAllocator_T<FN>::clear(T& iFrame_data)
{
	auto iFrame = *iFrame_data;

	// don't lock
	_jobAllocators[iFrame].clear();
	_jobDepAllocators[iFrame].clear();
}

#endif

#if 0
#pragma mark --- FrameAllocatorFrameStorage_T-Impl
#endif // 0
#if 1

template<size_t FN> inline
void FrameAllocatorFrameStorage_T<FN>::nextFrame()
{
	iFrame = (iFrame + 1) % s_kMaxFrameInFlightCount;
}

template<size_t FN> inline
typename FrameAllocatorFrameStorage_T<FN>::JobAllocator& 
FrameAllocatorFrameStorage_T<FN>::jobAllocator()
{
	return _jobAllocators[iFrame];
}

template<size_t FN> inline
typename FrameAllocatorFrameStorage_T<FN>::JobAllocator& 
FrameAllocatorFrameStorage_T<FN>::jobDependencyAllocator()
{
	return _jobDepAllocators[iFrame];
}

#endif

}