#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmsp_job_system/job/nmspJob.h"

#include <nmsp_stl/allocator/nmspLinearAllocator.h>

namespace nmsp {

#if 0
#pragma mark --- JobAllocator_T-Impl
#endif // 0
#if 1

class JobAllocator_T : public Allocator_Base<JobAllocator_T>
{
public:
	using Job				= Job_T;
	using JobHandle			= JobHandle_T;
	using LinearAllocator	= LinearAllocator_T;

	using SizeType			= JobSystemTraits::SizeType;

public:
	void clear();

	JobHandle alloc(SizeType n = sizeof(Job));

private:
	LinearAllocator _allocator;
};


#endif


#if 0
#pragma mark --- JobAllocator_T-Impl
#endif // 0
#if 1

inline
void JobAllocator_T::clear()
{
	_allocator.clear();
}

inline
JobAllocator_T::JobHandle JobAllocator_T::alloc(SizeType n)
{
	return sCast<JobHandle>(_allocator.alloc(n));
}


#endif

}