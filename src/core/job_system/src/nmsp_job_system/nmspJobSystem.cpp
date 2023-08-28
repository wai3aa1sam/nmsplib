#include "nmsp_job_system-pch.h"
#include "nmspJobSystem.h"

#include "thread/nmspThreadStorage.h"

namespace nmsp {

#if 0
#pragma mark --- JobSystem_T-Impl ---
#endif // 0
#if 1

JobSystem_T* Singleton_T<JobSystem_T>::s_instance = nullptr;

JobSystem_T::JobSystem_T()
{
#if NMSP_JOB_SYSTEM_DEVELOPMENT
	_NMSP_LOG("JobSystem Warning: should test performance when the job count is low, the sleep / wake will overlap when it has job but get steal by main thread");
#endif // NMSP_JOB_SYSTEM_DEVELOPMENT

	_NMSP_LOG("JobSystem TODO: add a re-submit");
	/*
	- the below implement when need resubmit job
	- ThreadPool::execute(), make a helper for JobArgs calculate, move it original calculate to one JobXX_Base responsibity (impl in task lambda of each job)
	- remove JobXX_Base onBegin / onEnd, only JobCluster_Base has onBegin/onEnd()
	- after we moved all JobArgs to each JobXX_Base, we could call onBegin when in task (even in JobParFor_Base)
	- since the JobCluster make n JobCluster_Base, the hasExecutedOnXX can store to the JobCluster_Base instead of JobHandle (since we do not need to check in each complete now)
	- The JobCluster_Base<JobParFor_Base> should has extra overload only instead of all other type incur the overhead, 
		after JobCluster_Base<JobParFor_Base> complete, we should make a extra job with highest priority call onEnd() which runAfter the dispatch, and wait for this job
	- resubmit could make a new UploadJob base on cluster, after onBegin, check the resubmit condition, 
		if yes, then reset the job handle (maybe only the debug params, except its parent and its dependency) and resubmit, the UploadJob could store the isByPassOnBegin,
	*/
}

JobSystem_T::~JobSystem_T()
{
	destroy();
}

void JobSystem_T::create(int workerCount, int threadTypeCount)
{
	auto cDesc = makeCDesc();
	cDesc.workerCount = workerCount;
	cDesc.threadTypeCount = threadTypeCount;
	create(cDesc);
}

void JobSystem_T::create(const CreateDesc& cDesc)
{
	destroy();

	auto threadTypeCount	= cDesc.threadTypeCount;
	auto workerCount		= cDesc.workerCount;

	NMSP_ASSERT(JobSystemTraits::logicalThreadCount() == JobSystemTraits::s_kJobSystemLogicalThreadCount, "please set marco NMSP_JOB_SYSTEM_LOGICAL_THREAD_COUNT to correct number");
	NMSP_ASSERT(threadTypeCount > 0 && threadTypeCount <= OsTraits::logicalThreadCount());

	auto total_thread = OsTraits::logicalThreadCount();
	_typedThreadCount = threadTypeCount;
	auto nWorkers = threadTypeCount > 1 ? total_thread - threadTypeCount : workerCount;
	NMSP_ASSERT(nWorkers >= 0 && nWorkers<= OsTraits::logicalThreadCount(), "workerCount + threadTypeCount > logicalThreadCount");

	JobSystemTraits::resetThreadLocalId();
	JobSystemTraits::setMainThread();

	_createTypedThreads();

	ThreadPool_CreateDesc desc;
	desc.typedThreadCount	= _typedThreadCount;
	desc.workerCount		= nWorkers;
	_threadPool.create(desc);
}

void JobSystem_T::destroy()
{
	if (!s_instance)
	{
		return;
	}

	//JobSystemTraits::resetThreadLocalId();
	_threadPool.destroy();
	shutdown();
}


void JobSystem_T::submit(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	if (instance()->isSingleThreadMode())
		return instance()->_stMode.submit(job);
	#endif // NMSP_JOB_SYSTEM_DEVELOPMENT
	
	//NMSP_ASSERT(JobSystemTraits::isMainThread(), "only can submit job in main thread");
	//throwIf(!JobSystemTraits::isMainThread(), "only can submit job in main thread");
	/*
		- since Unity JobSystem cannot submit job in main thread only, however, we cannot follow it, 
		since the job delayDispatch() in current implementation is create the actual job within a job. 
		If want follow it, then we must found another implementation for delay dispatch  
		(no job within job, then FrameAllocator will have no problem, 
		currently I believe there is some rare bug when the frame run very fast 
		and some job may allocate in the next frame since it may still doing stuff in previous frame, this may have bug
	*/

	auto& threadPool = instance()->_threadPool;
	threadPool.submit(job);
}

void JobSystem_T::waitForComplete(JobHandle job)
{
	NMSP_PROFILE_SCOPED();

	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	if (instance()->isSingleThreadMode())
		return instance()->_stMode.waitComplete(job);
	#endif // NMSP_JOB_SYSTEM_DEVELOPMENT

	if (!job)
		return;

	NMSP_ASSERT(JobSystemTraits::isMainThread(), "");
	auto* jsys = instance();
	auto& threadPool = jsys->_threadPool;
	auto& storage = jsys->threadStorage(); (void)storage;

	while (!job->isCompleted())
	{
		JobHandle tmp = nullptr;

		if (threadPool.tryGetJob(tmp))
		{
			threadPool.execute(tmp);
		}

		OsUtil::sleep_ms(JobSystemTraits::s_kBusySleepTimeMS);
	}

	//atomicLog("=== done waitForComplete()");
}


void JobSystem_T::_internal_nextFrame()
{
	NMSP_PROFILE_SCOPED();

	NMSP_ASSERT(JobSystemTraits::isMainThread());

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::nextFrame();
	#endif // 0

	for (auto& ts : _typedThreadStorages)
	{
		ts->nextFrame();
	}
	_threadPool.nextFrame();
}


JobSystem_T::JobHandle JobSystem_T::createEmptyJob()
{
	auto* job = JobSystem_T::allocateJob();
	job->setEmpty();
	return job;
}

void JobSystem_T::shutdown()
{
	for (auto& t : _typedThreads)
	{
		if (!t)
			continue;
		t->join();
	}
	_typedThreadStorages.clear();
	_typedThreads.clear();
}

JobSystem_T::FrameAllocator& JobSystem_T::_defaultAllocator()
{
	auto* jsys = JobSystem_T::instance();
	jsys->_checkError();

	auto& frameAlloc = jsys->threadStorage().frameAllocator();
	return frameAlloc;
}

void JobSystem_T::_checkError() const
{
	//if (!(JobSystemTraits::threadLocalId() >= 0 && JobSystemTraits::threadLocalId() < _threadPool.threadCount()))
	{
		//atomicLog("=== threadLocalId() {}, localId {} _checkError()", threadLocalId(), this->_threadStorages[threadLocalId()]->localId());
	}

	//NMSP_ASSERT(JobSystemTraits::threadLocalId() >= 0 && JobSystemTraits::threadLocalId() < _threadPool.threadCount());
}

void JobSystem_T::_createTypedThreads()
{
	_typedThreads.reserve(_typedThreadCount);
	_typedThreadStorages.reserve(_typedThreadCount);

	// Main Thread
	_typedThreadStorages.emplace_back(NMSP_NEW(ThreadStorage));
	_typedThreads.emplace_back(nullptr);

	for (size_t i = 1; i < _typedThreadCount; i++)
	{
		_typedThreadStorages.emplace_back(NMSP_NEW(ThreadStorage));
		_typedThreads.emplace_back(/*NMSP_NEW(WorkerThread)(workerCDesc)*/);
	}
}


#if 0
#pragma mark --- nmspJobSystem_T::SingleThreadMode-Impl ---
#endif // 0
#if 1

void 
JobSystem_T::setSingleThreadMode(bool v)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	_stMode.isEnabled = v;

	if (!_stMode.isEnabled)
	{
		_stMode.waitComplete(nullptr);
	}
	#endif // NMSP_JOB_SYSTEM_DEVELOPMENT
}

bool 
JobSystem_T::isSingleThreadMode() const
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	return _stMode.isEnabled;
	#else
	return false;
	#endif
}

void 
JobSystem_T::SingleThreadMode::waitComplete(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(JobSystemTraits::isMainThread(), "");

	if (!job)
	{
		keepExecuteIf( [&]() { return isEnabled || !jobs.isEmpty(); } );
		return;
	}

	keepExecuteIf( [&]() 
		{ 
			return isEnabled && !job->isCompleted();
		} );

	#endif
}

void 
JobSystem_T::SingleThreadMode::submit(JobHandle job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT

	instance()->_threadPool.preSubmitCheck(job);
	jobs.push(job);

	#endif
}

void
JobSystem_T::SingleThreadMode::keepExecuteIf(const Function_T<bool()>& func)
{
	auto& threadPool = instance()->_threadPool;
	
	while (func())
	{
		JobHandle temp = nullptr;
		if (jobs.try_pop(temp))
		{
			threadPool.preExecuteCheck(temp);
			threadPool._execute(temp);
		}
	}
}

#endif

#endif


}