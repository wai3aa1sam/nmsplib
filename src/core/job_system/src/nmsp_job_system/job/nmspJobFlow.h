#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmspJob.h"

#include <nmsp_stl/extra/nmspTuple.h>

namespace nmsp 
{

class JobSystem_T;

#if 0
#pragma mark --- JobFlow_T-Decl ---
#endif // 0
#if 1

class JobFlow_T : public NonCopyable
{
public:
	using Traits = JobSystemTraits;

	using Priority			= JobPriority;
	using JobHandle			= JobHandle_T;
	using LinearAllocator	= LinearAllocator_T;

	using JobSystem			= JobSystem_T;

	using SizeType = Traits::SizeType;

public:
	static constexpr SizeType s_kLocalSize = 12;

public:
	JobFlow_T();
	~JobFlow_T();

	template<class... JOB> auto emplace(JOB&&... job);
	template<class... JOB> void xDependOnY(JobHandle x, JOB&&... y);

	void runAndWait();

	void run();
	void wait();

private:
	JobHandle _emplace(JobHandle job);

private:
	JobSystem* _jsys = nullptr;

	Vector_T<JobHandle, s_kLocalSize> _jobs;
	Vector_T<JobHandle, s_kLocalSize> _waitForjobs;
	Vector_T<JobHandle, s_kLocalSize> _submitJobs;
};


template<class... JOB>
auto JobFlow_T::emplace(JOB&&... job)
{
	//static_assert(IsSame<GetElement<sizeof...(JOB) - 1>, JobHandle>);
	return std::make_tuple(_emplace(eastl::forward<JOB>(job))...);
}

template<class... JOB>
void JobFlow_T::xDependOnY(JobHandle x, JOB&&... y)
{
	(x->runAfter(nmsp::forward<JOB>(y)), ...);
}

inline
JobFlow_T::JobHandle 
JobFlow_T::_emplace(JobHandle job)
{
	return _jobs.emplace_back(job);
}


#endif

}


