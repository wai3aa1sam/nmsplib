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
	using T = u32;

	T loopIndex		= 0;		// SV_DispatchThreadID
	T batchID		= 0;		// SV_GroupID
	T batchIndex	= 0;		// SV_GroupIndex
};

struct JobInfo
{
	using T = u32;
	T batchID		= 0;
	T batchOffset	= 0;
	T batchEnd		= 0;

	void clear() { batchID = 0; batchOffset = 0; batchEnd = 0; }
};

using JobFunction = Function_T<void(const JobArgs&), 32, JobSystemTraits::s_kDefaultAlign, NoFallbackAllocator_Policy>;

class Job_T : public NonCopyable
{
	NMSP_JOB_SYSTEM_JOB_TYPE_FRIEND_CLASS_DECLARE();
	friend class WorkerThread_T;
	friend class ThreadPool_T;
	friend class JobSystem_T;
	friend class JobFlow_T;

public:
	using Priority			= JobPriority;
	using Info				= JobInfo;
	using JobHandle			= JobHandle_T;
	using LinearAllocator	= LinearAllocator_T;

	using SizeType	= JobSystemTraits::SizeType;

	using  Task = JobFunction;
	static Task s_emptyTask;

	static constexpr SizeType s_kTargetSize = JobSystemTraits::s_kCacheLineSize * 2;

public:
	~Job_T() = default;

	void setEmpty();

	bool		isCompleted		()const;
	int			jobRemainCount	() const;
	int			dependencyCount	() const;
	SizeType	runAfterCount	() const;

	const Info& info() const;
	void print() const;

	// only useful when enable SGE_JOB_SYSTEM_DEBUG
	JobHandle setName(const char* name);
	const char* name() const;

	void setParent(JobHandle parent);

	template<class... JOB> void runAfter (JOB&&... job);
	template<class... JOB> void runBefore(JOB&&... job);

protected:

	void	_runAfter(JobHandle job);
	void	_runBefore(JobHandle job);
	void*	_allocate(size_t n);

	void setDispatchJob(JobDispatch_Base* dispatchJob);

	JobHandle			parent();
			JobDispatch_Base* dispatchJob();
	const	JobDispatch_Base* dispatchJob() const;

private:
	void clear();

	void init(const Task& func, const Info& info, JobHandle parent = nullptr);
	void init(const Task& func, const Info& info, JobDispatch_Base* dispatchJob, JobHandle parent);

	void _setInfo(const Info& info);

	void addJobCount();
	int	decrDependencyCount();

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
		JobDispatch_Base*	_dispatchJob		= nullptr;
		Atm_T<int>			_jobRemainCount		= 1;
		Atm_T<bool>			_hasExecutedOnEnd	= false;

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
				int count = job->decrDependencyCount();
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
				int count = job->decrDependencyCount();
				if (count == 0)
				{
					invoke(nmsp::forward<Func>(func), job);
				}
			}
		}

		int	decrDependencyCount()	
		{ 
			auto ret = _dependencyCount.fetch_sub(1) - 1; 
			return ret;
		}

		bool couldRun() const		{ return _dependencyCount.load() == 0; }

	private:
		Atm_T<int>	_dependencyCount = 0;	// this depends on others
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

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
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