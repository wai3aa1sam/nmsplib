#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include "nmsp_job_system/thread/nmspThreadPool.h"
#include <nmsp_stl/extra/nmspSingleton.h>

namespace nmsp 
{

struct JobCluster;

#if 0
#pragma mark --- JobSystem_T-Decl ---
#endif // 0
#if 1

struct JobSystem_CreateDesc
{
public:
	using SizeType			= JobSystemTraits::SizeType;

public:
	SizeType threadTypeCount	= 1;
	SizeType workerCount		= JobSystemTraits::logicalThreadCount();
};

class JobSystem_T : public Singleton_T<JobSystem_T>
{
	friend class WorkerThread_T;
	friend class ThreadPool_T;
	friend class Job_T;
	NMSP_JOB_SYSTEM_JOB_TYPE_FRIEND_CLASS_DECLARE();
	friend struct JobCluster;

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
	using JobQueue			= JobQueue_T<>;

	using SizeType			= JobSystemTraits::SizeType;

public:
	static CreateDesc makeCDesc();
	static void submit(JobHandle job);
	static void waitForComplete(JobHandle job);

public:
	JobSystem_T();
	~JobSystem_T();

	void create(int workerCount, int threadTypeCount = 1);
	void create(const CreateDesc& cdesc);
	void destroy();

	JobHandle createEmptyJob();
	JobHandle createParentJob();

	SizeType	workerCount()		const;
	SizeType	threadCount()		const;
	StrViewA_T	threadName()		const;
	SizeType	workerStartIdx()	const;
	SizeType	workersEndIdx()		const;

	void setSingleThreadMode(bool v);
	bool isSingleThreadMode() const;

public:
	void _internal_nextFrame();

protected:
	void shutdown();

	static JobHandle		allocateJob();
	static FrameAllocator&  _defaultAllocator();

	WorkerThread& thread();
	const WorkerThread& thread() const;

	ThreadStorage& threadStorage();

	SizeType typedThreadCount() const;
	bool isTypedThread(int threadLocalId = JobSystemTraits::threadLocalId()) const;

private:
	void _checkError() const;
	void _createTypedThreads();


private:
	ThreadPool _threadPool;

	SizeType _typedThreadCount = 0;
	Vector_T<UPtr_T<WorkerThread>,	JobSystemTraits::s_kJobSystemLogicalThreadCount> _typedThreads;
	Vector_T<UPtr_T<ThreadStorage>, JobSystemTraits::s_kJobSystemLogicalThreadCount> _typedThreadStorages;

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager _dependencyManager;
	#endif // SGE_JOB_SYSTEM_DEBUG

	#if NMSP_JOB_SYSTEM_DEVELOPMENT

	struct SingleThreadMode
	{
		void waitComplete(JobHandle job);
		void submit(JobHandle job);

		//void keepExecuteIf(bool(*func)());
		void keepExecuteIf(const Function_T<bool()>& func);

		bool		isEnabled = false;
		JobQueue	jobs;
	};
	SingleThreadMode _stMode;
	
	#endif // 0

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

inline
JobSystem_T::WorkerThread& JobSystem_T::thread()
{
	NMSP_ASSERT(!JobSystemTraits::isMainThread(), "");
	_checkError();
	auto id = JobSystemTraits::threadLocalId();
	return isTypedThread(id) ? *_typedThreads[id] : _threadPool.workerThreads(id);
}

inline
const JobSystem_T::WorkerThread& JobSystem_T::thread() const
{
	NMSP_ASSERT(!JobSystemTraits::isMainThread(), "");
	_checkError();
	auto id = JobSystemTraits::threadLocalId();
	return isTypedThread(id) ? *_typedThreads[id] : _threadPool.workerThreads(id);
}

inline
JobSystem_T::ThreadStorage& JobSystem_T::threadStorage()
{
	_checkError();
	auto id = JobSystemTraits::threadLocalId();
	return isTypedThread(id) ? *_typedThreadStorages[id] : _threadPool.threadStroages(id);
}

#endif


}