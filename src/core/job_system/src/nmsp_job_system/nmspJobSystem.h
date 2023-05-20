#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include "nmsp_job_system/thread/nmspThreadPool.h"
#include <nmsp_stl/extra/nmspSingleton.h>

namespace nmsp {

#if 0
#pragma mark --- JobSystem_T-Decl ---
#endif // 0
#if 1

struct JobSystem_CreateDesc
{
public:
	using SizeType			= JobSystemTraits::SizeType;

public:
	SizeType threadTypeCount = 1;
	SizeType workerCount = 0;
};

class JobSystem_T : public StackSingleton_T<JobSystem_T>
{
public:
	friend class WorkerThread_T;
	friend class ThreadPool_T;
	NMSP_JOB_SYSTEM_JOB_TYPE_FRIEND_CLASS_DECLARE();

public:
	using Base			= StackSingleton_T<JobSystem_T>;
	using CreateDesc	= JobSystem_CreateDesc;

	using Job				= Job_T;
	using Task				= Job::Task;
	using JobHandle			= JobHandle_T;
	using ThreadPool		= ThreadPool_T;
	using WorkerThread		= WorkerThread_T;
	using ThreadStorage		= ThreadStorage_T;
	using JobAllocator		= JobAllocator_T;
	using FrameAllocator	= FrameAllocator_T<JobSystemTraits::s_kMaxFrameInFlightCount>;

	using SizeType			= JobSystemTraits::SizeType;

public:
	JobSystem_T() = default;
	JobSystem_T(int workerCount, int threadTypeCount);
	JobSystem_T(const CreateDesc& cdesc);
	~JobSystem_T();

	static CreateDesc makeCDesc();
	static void submit(JobHandle job);

	void create(const CreateDesc& cdesc);
	void destroy();

	void waitForComplete(JobHandle job);

	JobHandle createEmptyJob();

	SizeType	workerCount()		const;
	SizeType	threadCount()		const;
	StrViewA_T	threadName()		const;
	SizeType	workerStartIdx()	const;
	SizeType	workersEndIdx()		const;

public:
	void _internal_nextFrame();

protected:
	static JobHandle allocateJob();

	static FrameAllocator& _defaultAllocator();
	ThreadStorage& _threadStorage();

	SizeType typedThreadCount() const;
	bool isTypedThread(int threadLocalId = JobSystemTraits::threadLocalId()) const;

private:
	void _createTypedThreads();

	bool _tryGetJob(JobHandle& job);
	void _checkError() const;

	static void _execute(JobHandle job);
	static void _complete(JobHandle job);

private:
	ThreadPool _threadPool;

	SizeType _typedThreadCount = 0;
	Vector_T<UPtr_T<WorkerThread>,	JobSystemTraits::s_kJobSystemLogicalThreadCount> _typedThreads;
	Vector_T<UPtr_T<ThreadStorage>, JobSystemTraits::s_kJobSystemLogicalThreadCount> _typedThreadStorages;

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager _dependencyManager;
	#endif // SGE_JOB_SYSTEM_DEBUG
};


#endif


#if 0
#pragma mark --- JobSystem_T-Decl ---
#endif // 0
#if 1

inline
JobSystem_T::CreateDesc JobSystem_T::makeCDesc()
{
	return CreateDesc{};
}

inline
JobSystem_T::JobHandle JobSystem_T::allocateJob()
{
	return instance()->_defaultAllocator().allocJob();
}

inline JobSystem_T::SizeType JobSystem_T::workerStartIdx()	const	{ return _typedThreadCount; }
inline JobSystem_T::SizeType JobSystem_T::workersEndIdx()  const	{ return JobSystemTraits::s_kJobSystemLogicalThreadCount - 1; }
inline JobSystem_T::SizeType JobSystem_T::workerCount() const		{ return _threadPool.workerCount(); }
inline JobSystem_T::SizeType JobSystem_T::threadCount() const		{ return _threadPool.threadCount(); }

inline JobSystem_T::SizeType JobSystem_T::typedThreadCount() const	{ return _typedThreads.size(); }

inline bool JobSystem_T::isTypedThread(int threadLocalId) const { return threadLocalId < _typedThreadCount; }

#endif


}