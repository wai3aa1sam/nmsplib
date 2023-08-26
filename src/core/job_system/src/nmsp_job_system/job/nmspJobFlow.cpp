#include "nmsp_job_system-pch.h"
#include "nmspJobFlow.h"

#include "nmsp_job_system/nmspJobSystem.h"

namespace nmsp
{

#if 0
#pragma mark --- JobFlow_T-Decl ---
#endif // 0
#if 1

JobFlow_T::JobFlow_T()
{
	_jsys = JobSystem::instance();
	NMSP_CORE_ASSERT(_jsys, "JobSystem is not yet init()");
}

JobFlow_T::~JobFlow_T()
{

}

void 
JobFlow_T::runAndWait()
{
	run();
	for (auto& job : _waitForjobs)
	{
		_jsys->waitForComplete(job);
	}
}

void 
JobFlow_T::run()
{
	// only submit job that has no dependency
	for (auto& job : _jobs)
	{
		if (!job->runAfterCount())
		{
			_waitForjobs.emplace_back(job);
		}

		if (!job->dependencyCount())
			_jsys->submit(job);
	}
}

#endif

}
