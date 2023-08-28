#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmspJob.h"

namespace nmsp 
{

class Job_T;
class ThreadPool_T;
class JobSystem_T;

class Job_Base;			/* void execute(); */
class JobFor_Base;		/* void execute(const JobArgs& args); */
class JobParFor_Base;	/* void execute(const JobArgs& args); */ 

#define JobDispatchType_ENUM_LIST(E) \
	E(None, = 0) \
	E(Job_Base,) \
	E(JobFor_Base,) \
	E(JobParFor_Base,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(JobDispatchType, u8);

#if 0
#pragma mark --- JobDispatcher-Decl ---
#endif // 0
#if 1

struct JobDispatcher
{
public:
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

	using JobHandle = JobHandle_T;
	using JobSystem = JobSystem_T;

public:
	JobDispatcher();

	template<bool IS_PREPARE, class T, class... DEPEND_ON> static JobHandle _dispatch(T* obj, JobSizeT loopCount, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps);
	static JobHandle _dispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize);
	template<class... DEPEND_ON> static JobHandle _prepareDispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps);

	template<class K> static void static_check();
};

#endif

class JobDispatch_Base : public NonCopyable
{
	friend class Job_T;
	friend class ThreadPool_T;

public:
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

public:
	#if NMSP_JOB_SYSTEM_DEVELOPMENT

	JobDispatch_Base() 
	{
		_devCheckHasExecutedOnBegin = false;
		_devCheckHasExecutedOnEnd	= false;
	};

	virtual void onBegin()	
	{ 
		NMSP_ASSERT(!_devCheckHasExecutedOnBegin, "onBegin() shd only execute once");	
		_devCheckHasExecutedOnBegin = true; 
	};

	virtual void onEnd()	
	{ 
		NMSP_ASSERT(!_devCheckHasExecutedOnEnd, "onEnd() shd only execute once");	
		_devCheckHasExecutedOnEnd = true; 

	};
	#else

	JobDispatch_Base() 
	{

	};

	virtual void onBegin()	{};
	virtual void onEnd()	{};

	#endif

	virtual ~JobDispatch_Base() = default;


private:
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	volatile bool _devCheckHasExecutedOnBegin;
	volatile bool _devCheckHasExecutedOnEnd;
	#endif // maybe no need Atm, if want to change better wrap with a CheckExclusive 
};

class Job_Base : public JobDispatch_Base
{ 
public:
	using This = Job_Base;
	using Base = JobDispatch_Base;

	using JobHandle = JobHandle_T;
	using JobSystem = JobSystem_T;

public:
	static constexpr JobDispatchType s_kType = JobDispatchType::Job_Base;

private:
	static constexpr const char* s_checkTypeMsg = "T is not base of Job_Base";

public:
	friend struct JobDispatcher;

public:
	virtual void execute() = 0;

	JobHandle dispatch()
	{
		return dispatch(this);
	}

	template<class... DEPEND_ON>
	JobHandle prepareDispatch(JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		return prepareDispatch(this, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}

private:
	static JobHandle dispatch(This* obj)
	{
		return JobDispatcher::_dispatch<false>(obj, 1, nullptr);
	}

	template<class... DEPEND_ON>
	static JobHandle prepareDispatch(This* obj, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		return JobDispatcher::_dispatch<true>(obj, 1, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}
};

class JobFor_Base : public JobDispatch_Base
{ 
public:
	using This = JobFor_Base;
	using Base = JobDispatch_Base;

	using JobHandle = JobHandle_T;
	using JobSystem = JobSystem_T;

public:
	static constexpr JobDispatchType s_kType = JobDispatchType::JobFor_Base;

private:
	static constexpr const char* s_checkTypeMsg = "T is not base of JobFor_Base";

public:
	friend struct JobDispatcher;

public:
	virtual void execute(const JobArgs& args) = 0;

	JobHandle dispatch(JobSizeT loopCount)
	{
		return dispatch(this, loopCount);
	}

	template<class... DEPEND_ON>
	JobHandle prepareDispatch(JobSizeT loopCount, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		return prepareDispatch(this, loopCount, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}

public:
	static JobHandle dispatch(This* obj, JobSizeT loopCount)
	{
		return JobDispatcher::_dispatch<false>(obj, loopCount, nullptr);
	}

	template<class... DEPEND_ON>
	static JobHandle prepareDispatch(This* obj, JobSizeT loopCount, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		return JobDispatcher::_dispatch<true>(obj, loopCount, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}
};

class JobParFor_Base : public JobDispatch_Base
{ 
public:
	using This = JobParFor_Base;
	using Base = JobDispatch_Base;

	using JobHandle = JobHandle_T;
	using JobSystem = JobSystem_T;

public:
	static constexpr JobDispatchType s_kType = JobDispatchType::JobParFor_Base;

private:
	static constexpr const char* s_checkTypeMsg = "T is not base of JobParFor_Base";

public:
	virtual void execute(const JobArgs& args) = 0;

	JobHandle dispatch(JobSizeT loopCount, JobSizeT batchSize)
	{
		return dispatch(this, loopCount, batchSize);
	}

	template<class... DEPEND_ON>
	JobHandle prepareDispatch(JobSizeT loopCount, JobSizeT batchSize, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		return prepareDispatch(this, loopCount, batchSize, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}

public:
	static JobHandle dispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize)
	{
		return JobDispatcher::_dispatch(obj, loopCount, batchSize);
	}

	template<class... DEPEND_ON>
	static JobHandle prepareDispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize, JobHandle dependOn = nullptr, DEPEND_ON&&... moreDeps)
	{
		//NMSP_CORE_ASSERT(!dependOn, "use job flow to delcare job dependency");
		return JobDispatcher::_prepareDispatch(obj, loopCount, batchSize, dependOn, nmsp::forward<DEPEND_ON>(moreDeps)...);
	}
};


#if 0
#pragma mark --- JobDispatcher-Impl ---
#endif // 0
#if 1

inline
JobDispatcher::JobDispatcher()
{
	//NMSP_S_ASSERT(IsBaseOf<NMSP_ARGS(Job_Base, T)>,			"T is not base of Job_Base");		// TYPE 0
	//NMSP_S_ASSERT(IsBaseOf<NMSP_ARGS(JobFor_Base, T)>,		"T is not base of JobFor_Base");	// TYPE 1
	//NMSP_S_ASSERT(IsBaseOf<NMSP_ARGS(JobParFor_Base, T)>,	"T is not base of JobParFor_Base");	// TYPE 2
}

template<bool IS_PREPARE, class T, class... DEPEND_ON> inline
typename JobDispatcher::JobHandle JobDispatcher::_dispatch(T* obj, JobSizeT loopCount, JobHandle dependOn, DEPEND_ON&&... moreDeps)
{
	//static_assert(IsBaseOf<Job_Base<T>, T> || IsBaseOf<JobFor_Base<T>, T>, "T is not base of Job_Base or JobFor_Base");
	if (loopCount == 0)
		return nullptr;

	JobFunction task;
	if constexpr (T::s_kType == JobDispatchType::Job_Base)
	{
		NMSP_ASSERT(loopCount == 1);
		static_check<Job_Base>();
		task = [obj](const JobArgs& args) 
			{ 
				return obj->execute(); // no args is correct
			};		
	}
	else if constexpr (T::s_kType == JobDispatchType::JobFor_Base)
	{
		static_check<JobFor_Base>();
		task = [obj](const JobArgs& args) 
			{ 
				return obj->execute(args); 
			};
	}

	JobHandle job = JobSystem::allocateJob();
	{
		JobInfo info;
		info.batchId	 = 0;
		info.batchOffset = 0 * 0;
		info.batchEnd	 = loopCount;

		job->init(task, info, obj, nullptr);
	}

	if constexpr (!IS_PREPARE)
	{
		JobSystem::submit(job);
	}
	else
	{
		if (dependOn)
		{
			job->runAfter(dependOn);
		}
		(job->runAfter(nmsp::forward<DEPEND_ON>(moreDeps)), ...);
	}

	return job;
}

inline
typename JobDispatcher::JobHandle JobDispatcher::_dispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize)
{
	if (loopCount == 0 || batchSize == 0)
		return nullptr;

	const JobSizeT nBatchGroup	= math::divideTo(loopCount, batchSize);

	JobFunction task = [obj](const JobArgs& args) { return obj->execute(args); };

	JobInfo info;
	JobHandle parent = JobSystem::allocateJob();
	parent->setEmpty();
	parent->setDispatchJob(obj);

	for (JobSizeT iBatchGroup = 0; iBatchGroup < nBatchGroup; iBatchGroup++)
	{
		JobHandle job = JobSystem::allocateJob();

		info.batchId	 = iBatchGroup;
		info.batchOffset = iBatchGroup * batchSize;
		info.batchEnd	 = math::min(info.batchOffset + batchSize, loopCount);

		job->init(task, info, obj, parent);

		/*if (iBatchGroup == 0)
		parent = job;*/

		JobSystem::submit(job);
	}

	JobSystem::submit(parent);

	return parent;
}

template<class... DEPEND_ON> inline
typename JobDispatcher::JobHandle JobDispatcher::_prepareDispatch(JobParFor_Base* obj, JobSizeT loopCount, JobSizeT batchSize, JobHandle dependOn, DEPEND_ON&&... moreDeps)
{
	//NMSP_CORE_ASSERT(!dependOn, "use job flow to delcare job dependency");

	if (loopCount == 0 || batchSize == 0)
		return nullptr;

	JobHandle spawnJobHnd 	= JobSystem::allocateJob();

	auto spawnTask = [spawnJobHnd, obj, loopCount, batchSize](const JobArgs& args)
		{
			const JobSizeT nBatchGroup	= math::divideTo(loopCount, batchSize);
			JobFunction task = [obj](const JobArgs& args) { return obj->execute(args); };

			JobInfo info;

			for (JobSizeT iBatchGroup = 0; iBatchGroup < nBatchGroup; iBatchGroup++)
		{
			JobHandle job = JobSystem::allocateJob();

			info.batchId	 = iBatchGroup;
			info.batchOffset = iBatchGroup * batchSize;
			info.batchEnd	 = math::min(info.batchOffset + batchSize, loopCount);

			job->init(task, info, obj, spawnJobHnd);

			JobSystem::submit(job);
		}
	};
	{
		JobInfo info;
		info.batchEnd = 1;
		spawnJobHnd->init(spawnTask, info, obj, nullptr);
	}

	if (dependOn)
	{
		spawnJobHnd->runAfter(dependOn);
	}
	(spawnJobHnd->runAfter(nmsp::forward<DEPEND_ON>(moreDeps)), ...);

	return spawnJobHnd;
}

template<class K> inline
void JobDispatcher::static_check()
{
	//TypeDisplayer<BASE> a;
	/*if		constexpr (IsSame<Job_Base<T>,		 K>)	{ static_assert(IsBaseOf<Job_Base<T>,		T>,	"T is not base of Job_Base"); }
	else if constexpr (IsSame<JobFor_Base<T>,	 K>)	{ static_assert(IsBaseOf<JobFor_Base<T>,	T>,	"T is not base of JobFor_Base"); }
	else if constexpr (IsSame<JobParFor_Base<T>, K>)	{ static_assert(IsBaseOf<JobParFor_Base<T>,	T>,	"T is not base of JobParFor_Base"); }
	else
	{
	static_assert(false,	"T is not base of Job_Base or JobFor_Base or JobParFor_Base");
	}*/
}

#endif

}