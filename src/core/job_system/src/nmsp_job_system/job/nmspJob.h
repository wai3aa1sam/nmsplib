#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include <nmsp_stl/extra/nmspFunction.h>
#include <nmsp_stl/allocator/nmspLinearAllocator.h>
#include <nmsp_stl/extra/nmspPaddedData.h>

namespace nmsp 
{

class JobDispatch_Base;
class JobFlow_T;

#if 0
#pragma mark --- Job_T-Decl ---
#endif // 0
#if 1

struct JobArgs
{
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

	JobSizeT loopIndex		= 0;		// SV_DispatchThreadID
	JobSizeT batchId		= 0;		// SV_GroupID
	JobSizeT batchIndex	= 0;		// SV_GroupIndex
};

struct JobInfo
{
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

	JobSizeT batchId		= 0;
	JobSizeT batchOffset	= 0;
	JobSizeT batchEnd		= 0;

	void clear() { batchId = 0; batchOffset = 0; batchEnd = 0; }
};

using JobFunction = Function_T<void(const JobArgs&), 32, JobSystemTraits::s_kDefaultAlign, NoFallbackAllocator_Policy>;

class Job_T : public NonCopyable
{
	NMSP_JOB_SYSTEM_JOB_TYPE_FRIEND_CLASS_DECLARE();
	friend class WorkerThread_T;
	friend class ThreadPool_T;
	friend class JobSystem_T;
	friend class JobFlow_T;
	friend struct JobCluster;

public:
	using Priority			= JobPriority;
	using Info				= JobInfo;
	using JobHandle			= JobHandle_T;
	using LinearAllocator	= LinearAllocator_T;

	using SizeType	= JobSystemTraits::SizeType;

	using  Task = JobFunction;

	using JobCountType = int;

public:
	static Task s_emptyTask;

	static constexpr SizeType s_kTargetSize = JobSystemTraits::s_kCacheLineSize * 2;

public:
	Job_T();
	~Job_T();

	void setEmpty();
	void createParentJob();

	bool			isCompleted		() const;
	JobCountType	jobRemainCount	() const;
	JobCountType	dependencyCount	() const;
	SizeType		runAfterCount	() const;

	const Info& info() const;
	void print() const;

	// only useful when enable SGE_JOB_SYSTEM_DEBUG
	JobHandle setName(const char* name);
	const char* name() const;

	void setParent(JobHandle parent);

	template<class... JOB> void runAfter (JOB&&... job);
	template<class... JOB> void runBefore(JOB&&... job);

	const JobDispatch_Base* dispatchJob() const;

protected:
	void	_runAfter(JobHandle job);
	void	_runBefore(JobHandle job);
	void*	_allocate(size_t n);

	JobCountType decrRemainJobCount();

	void setDispatchJob(JobDispatch_Base* dispatchJob);

	JobHandle			parent();
	JobDispatch_Base*	_dispatchJob();

private:
	void clear();

	void init(const Task& func, const Info& info, JobHandle parent = nullptr, JobCountType remainCount = 1);
	void init(const Task& func, const Info& info, JobDispatch_Base* dispatchJob, JobHandle parent);
	void init(const Task& func, const Info& info, JobDispatch_Base* dispatchJob, bool forceBeginEnd, JobHandle parent);

	void _setInfo(const Info& info);

	void			addJobCount();
	JobCountType	decrDependencyCount();

	void invokeOnEnd();

	void setIsForceOnBeginEnd(bool v);
	bool isForceOnBeginEnd() const;

private:
	#if 0
	#pragma mark --- Storage-Impl ---
	#endif // 0
	#if 1
	struct NormalData
	{
		friend class Job_T;

		NormalData()
			:
			_jobRemainCount(1), _priority(Priority::Cirtical)
		{
			#if NMSP_JOB_SYSTEM_DEVELOPMENT
			_resetDebugCheck();
			#endif // _DEBUG
		}

		#if NMSP_JOB_SYSTEM_DEVELOPMENT
		void _resetDebugCheck()
		{
			_isAllowAddDeps.store(true);
			_isExecuted.store(false);
			_isSubmitted.store(false);
		}
		#endif // _DEBUG

		void setPriority(Priority pri)	{ _priority.store(pri); }
		Priority priority()				{ return _priority.load(); }

	public:
		Task				_task;
		Info				_info;

		// concept of parent and DepData::runAfterThis is a little bit different.
		// parent may run before the child but DepData::runAfterThis must run after this job
		JobHandle			_parent				= nullptr;		
		Atm_T<JobCountType>	_jobRemainCount		= 1;

		//void*				_jobExtension		= nullptr;

		JobDispatch_Base*	_dispatchJob		= nullptr;
		//Atm_T<bool>			_hasExecutedOnEnd	= false;
		bool				_hasExecutedOnEnd	= false;
		bool				_isForceOnBeginEnd	= false;
		
		#if NMSP_JOB_SYSTEM_DEVELOPMENT
		Atm_T<bool>		_isAllowAddDeps = true;
		Atm_T<bool>		_isExecuted		= false;
		Atm_T<bool>		_isSubmitted	= false;
		#endif // _DEBUG

	private:
		Atm_T<Priority>	_priority;
		//Priority			_priority;
	};
	struct DepData
	{
		friend class Job_T;

		static constexpr size_t s_kSizeWithoutDeps = sizeof(NormalData);
		//static constexpr size_t s_kLocalDepsCount = (s_kTargetSize - s_kSizeWithoutDeps - sizeof(Vector<JobHandle>)) / sizeof(JobHandle) - 1;
		static constexpr size_t s_kLocalDepsCount = 1;

		using DepList = Vector_T<JobHandle, 0, LinearAllocator&>;

		DepData();

		template<class T, class FUNC>
		void runAfterThis_for_each_ifNoDeps(T& pool, FUNC&& func)
		{
			using Func = Decay<FUNC>;

			for (auto& job : _runAfterThis)
			{
				JobCountType count = job->decrDependencyCount();
				if (count == 0)
				{
					invoke(nmsp::forward<Func>(func), pool, job);
				}
			}
		}

		template<class FUNC>
		void runAfterThis_for_each_ifNoDeps(FUNC&& func)
		{
			using Func = Decay<FUNC>;

			for (auto& job : _runAfterThis)
			{
				JobCountType count = job->decrDependencyCount();
				if (count == 0)
				{
					invoke(nmsp::forward<Func>(func), job);
				}
			}
		}

		JobCountType	decrDependencyCount()	
		{ 
			auto ret = _dependencyCount.fetch_sub(1) - 1; 
			return ret;
		}

		bool couldRun() const		{ return _dependencyCount.load() == 0; }

	private:
		Atm_T<JobCountType>	_dependencyCount = 0;	// this depends on others
		DepList		_runAfterThis;
	};
	struct Data : public NormalData
	{
		DepData dep;
	};
	struct Storage : public PaddedData_T<Data, JobSystemTraits::s_kCacheLineSize>
	{
		Storage()
		{
			sizeof(Storage);
			static_assert(sizeof(Storage) % JobSystemTraits::s_kCacheLineSize == 0);
		}
	};
	#endif // 1

private:
	Storage _storage;

	#if NMSP_JOB_SYSTEM_DEVELOPMENT || NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	StringT _name;
	#endif // SGE_JOB_SYSTEM_DEBUG
};

#endif


#if 0
#pragma mark --- Job_T-Impl ---
#endif // 0
#if 1

template<class... JOB> inline 
void Job_T::runAfter(JOB&&... job)
{
	(_runAfter(nmsp::forward<JOB>(job)), ...);
}

template<class... JOB> inline 
void Job_T::runBefore(JOB&&... job)
{
	(_runBefore(nmsp::forward<JOB>(job)), ...);
}

#endif

}