#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmspJob.h"

namespace nmsp 
{

class JobSystem_T;

template<class JOB_BASE> class JobCluster_Base;

struct JobClusterInfo
{
public:
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

public:
	static constexpr JobSizeT s_kDefault = ~JobSizeT(0);

public:
	void set(const JobClusterInfo& info)
	{
		clusterCount			= info.clusterCount;
		batchSizePerThread		= info.batchSizePerThread;
	}

public:
	JobSizeT clusterCount		= s_kDefault;
	JobSizeT batchSizePerThread	= s_kDefault;
};

struct JobClusterArgs
{
public:
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;
	using SizeType	= Traits::SizeType;

public:
	static constexpr JobSizeT s_kDefault = ~JobSizeT(0);

public:
	void set(const JobClusterArgs& info)
	{
		clusterId		= info.clusterId;		
		clusterOffset	= info.clusterOffset;
		clusterSize		= info.clusterSize;
	}

public:
	JobSizeT clusterId		= s_kDefault;
	JobSizeT clusterOffset	= s_kDefault;
	JobSizeT clusterSize	= s_kDefault;
};

struct JobCluster
{
	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;

	using JobHandle = JobHandle_T;
	using JobSystem = JobSystem_T;
	using Args		= JobClusterArgs;

public:
	template<class T, class ALLOC = DefaultAllocator, size_t N = JobSystemTraits::s_kEstLogicalThreadCount, class... ARGS>
	static NMSP_NODISCARD JobHandle_T dispatch(Vector_T<UPtr_T<T>, N, ALLOC>& outJobClusters, JobSizeT loopCount, JobSizeT minBatchSize, ARGS&&... ctor_args);

	template<class T, class ALLOC = DefaultAllocator, size_t N = JobSystemTraits::s_kEstLogicalThreadCount, class... ARGS>
	static NMSP_NODISCARD JobHandle_T prepare(Vector_T<UPtr_T<T>, N, ALLOC>& outJobClusters, JobSizeT loopCount, JobSizeT minBatchSize, ARGS&&... ctor_args);

	template<class T, class U>	static constexpr JobClusterInfo clusterInfo(T loopCount, U minBatchSize);


private:
	template<class T>
	static JobHandle _prepareDispatch(T* jobCluster, JobSizeT batchSize);

	template<class T>
	static JobHandle _makeJobHnd(T* jobCluster, JobSizeT& remain, JobSizeT iBatchGroup, JobSizeT batchSizePerThread, JobHandle parent);
};

#if 0
#pragma mark --- nmspJobCluster-Decl ---
#endif // 0
#if 1

template<class JOB_BASE>
class JobCluster_Base : public JOB_BASE
{
	friend struct JobCluster;
public:
	using JobBase	= JOB_BASE;
	using Base		= JobCluster_Base<JobBase>;	// for dverived class
	using This		= JobCluster_Base<JobBase>;

	using Traits	= JobSystemTraits;
	using JobSizeT	= Traits::JobSizeT;
	using SizeType	= Traits::SizeType;
	using Args		= JobClusterArgs;

	using JobHandle = JobHandle_T;

public:
	JobCluster_Base();
	virtual ~JobCluster_Base();

	void setClusterArgs(const Args& info);

	const Args& clusterArgs() const;

	virtual void onSetup(JobHandle) {}

protected:
	Args _args;
};

template<class JOB_BASE> inline
JobCluster_Base<JOB_BASE>::JobCluster_Base()
{

}


template<class JOB_BASE> inline
JobCluster_Base<JOB_BASE>::~JobCluster_Base()
{

}

template<class JOB_BASE> inline
void 
JobCluster_Base<JOB_BASE>::setClusterArgs(const Args& args)
{
	_args.set(args);
}

template<class JOB_BASE> inline 
const typename JobCluster_Base<JOB_BASE>::Args& 
JobCluster_Base<JOB_BASE>::clusterArgs() const
{
	return _args;
}

#endif

#if 0
#pragma mark --- nmspJobCluster-Impl ---
#endif // 0
#if 1

template<class T, class ALLOC, size_t N, class... ARGS> inline
JobHandle_T 
JobCluster::dispatch(Vector_T<UPtr_T<T>, N, ALLOC>& outJobClusters, JobSizeT loopCount, JobSizeT minBatchSize, ARGS&&... ctor_args)
{
	static_assert( IsBaseOf<JobCluster_Base<Job_Base>,			T>
				|| IsBaseOf<JobCluster_Base<JobFor_Base>,		T>
				|| IsBaseOf<JobCluster_Base<JobParFor_Base>,	T>
		);

	using Base		= typename T::Base;

	const auto clusterInfo			= JobCluster::clusterInfo(loopCount, minBatchSize);
	const auto batchSizePerThread	= clusterInfo.batchSizePerThread;
	const auto clusterCount			= clusterInfo.clusterCount;

	outJobClusters.clear();
	outJobClusters.resize(clusterCount);

	JobHandle parent = JobSystem::instance()->createEmptyJob();

	JobSizeT remain = loopCount;

	for (JobSizeT iBatchGroup = 0; iBatchGroup < clusterCount; iBatchGroup++)
	{
		auto& jobCluster = outJobClusters[iBatchGroup];
		jobCluster = makeUPtr<T>(nmsp::forward<ARGS>(ctor_args)...);

		JobHandle jobHnd = _makeJobHnd(jobCluster.ptr(), remain, iBatchGroup, batchSizePerThread, parent);
		JobSystem::submit(jobHnd);
	}
	return parent;
}

template<class T, class ALLOC, size_t N, class... ARGS> inline
JobHandle_T 
JobCluster::prepare(Vector_T<UPtr_T<T>, N, ALLOC>& outJobClusters, JobSizeT loopCount, JobSizeT minBatchSize, ARGS&&... ctor_args)
{
	static_assert( IsBaseOf<JobCluster_Base<Job_Base>,			T>
				|| IsBaseOf<JobCluster_Base<JobFor_Base>,		T>
				|| IsBaseOf<JobCluster_Base<JobParFor_Base>,	T>
		);

	using Base		= typename T::Base;

	const auto clusterInfo			= JobCluster::clusterInfo(loopCount, minBatchSize);
	const auto clusterCount			= clusterInfo.clusterCount;

	outJobClusters.clear();
	outJobClusters.resize(clusterCount);

	for (JobSizeT iBatchGroup = 0; iBatchGroup < clusterCount; iBatchGroup++)
	{
		auto& jobCluster = outJobClusters[iBatchGroup];
		jobCluster = makeUPtr<T>(nmsp::forward<ARGS>(ctor_args)...);
	}

	JobHandle spawnJobHnd = JobSystem::allocateJob();
	auto spawnTask = [spawnJobHnd, &outJobClusters, loopCount, minBatchSize](const JobArgs& args)
	{
		const auto clusterInfo			= JobCluster::clusterInfo(loopCount, minBatchSize);
		const auto batchSizePerThread	= clusterInfo.batchSizePerThread;
		const auto clusterCount			= clusterInfo.clusterCount;

		JobSizeT remain = loopCount;

		for (JobSizeT iBatchGroup = 0; iBatchGroup < clusterCount; iBatchGroup++)
		{
			auto& jobCluster = outJobClusters[iBatchGroup];

			JobHandle jobHnd = _makeJobHnd(jobCluster.ptr(), remain, iBatchGroup, batchSizePerThread, spawnJobHnd);
			JobSystem::submit(jobHnd);
		}
	};

	{
		JobInfo info;
		info.batchEnd = 1;
		spawnJobHnd->init(spawnTask, info, nullptr, nullptr);
	}

	return spawnJobHnd;
}

template<class T, class U> inline constexpr 
JobClusterInfo JobCluster::clusterInfo(T loopCount, U minBatchSize)
{
	JobClusterInfo o;
	o.batchSizePerThread	= math::max(sCast<JobSizeT>(minBatchSize), sCast<JobSizeT>(loopCount) / sCast<JobSizeT>(OsTraits::logicalThreadCount()));
	o.clusterCount			= sCast<JobSizeT>(math::ceil((float)loopCount / o.batchSizePerThread));
	return o;
}

template<class T> inline
typename JobCluster::JobHandle 
JobCluster::_prepareDispatch(T* jobCluster, JobSizeT batchSize)
{
	if constexpr(T::s_kType == JobDispatchType::Job_Base)
	{
		return jobCluster->prepareDispatch(nullptr, nullptr);
	}
	else if constexpr(T::s_kType == JobDispatchType::JobFor_Base)
	{
		return jobCluster->prepareDispatch(batchSize);
	}
	else if constexpr(T::s_kType == JobDispatchType::JobParFor_Base)
	{
		JobSizeT parForBatchSize = batchSize > 1024 * 4 ? 64 : 32;
		return jobCluster->prepareDispatch(batchSize, parForBatchSize);
	}
	else
	{
		NMSP_CORE_ASSERT(false, "cannot find Job Base Type");
	}
}

template<class T> inline
typename JobCluster::JobHandle 
JobCluster::_makeJobHnd(T* jobCluster, JobSizeT& remain, JobSizeT iBatchGroup, JobSizeT batchSizePerThread, JobHandle parent)
{
	Args args;

	auto batchSize = math::min(batchSizePerThread, remain);
	remain -= batchSize;

	args.clusterId		= iBatchGroup;
	args.clusterOffset	= iBatchGroup * batchSizePerThread;
	args.clusterSize	= batchSize;
	jobCluster->setClusterArgs(args);

	JobHandle jobHnd = _prepareDispatch(jobCluster, batchSize);
	jobHnd->setParent(parent);
	jobHnd->setIsForceOnBeginEnd(true);
	jobCluster->onSetup(jobHnd);

	return jobHnd;
}

template<class T, class ALLOC = DefaultAllocator, size_t N = JobSystemTraits::s_kEstLogicalThreadCount, class... ARGS>
inline NMSP_NODISCARD 
JobHandle_T 
dispatchJobCluster(Vector_T<UPtr_T<T>, N, ALLOC>& jobClusters, JobCluster::JobSizeT loopCount, JobCluster::JobSizeT minBatchSize, ARGS&&... ctor_args)
{
	return JobCluster::dispatch(jobClusters, loopCount, minBatchSize, nmsp::forward<ARGS>(ctor_args)...);
}

template<class T, class ALLOC = DefaultAllocator, size_t N = JobSystemTraits::s_kEstLogicalThreadCount, class... ARGS>
inline NMSP_NODISCARD 
JobHandle_T 
prepareJobCluster(Vector_T<UPtr_T<T>, N, ALLOC>& jobClusters, JobCluster::JobSizeT loopCount, JobCluster::JobSizeT minBatchSize, ARGS&&... ctor_args)
{
	return JobCluster::prepare(jobClusters, loopCount, minBatchSize, nmsp::forward<ARGS>(ctor_args)...);
}


#endif

}