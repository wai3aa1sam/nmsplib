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
	_NMSP_LOG("Warning: should test performance when the job count is low, the sleep / wake will overlap when it has job but get steal by main thread");
#endif // NMSP_JOB_SYSTEM_DEVELOPMENT

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

void JobSystem_T::waitForComplete(JobHandle job)
{
	NMSP_PROFILE_SCOPED();

	if (!job)
		return;

	NMSP_ASSERT(JobSystemTraits::isMainThread(), "");
	auto* jsys = this;
	auto& threadPool = this->_threadPool;
	auto& storage = jsys->threadStorage(); (void)storage;

	while (!job->isCompleted())
	{
		JobHandle tmp = nullptr;

		if (true && threadPool.tryGetJob(tmp))
		{
			threadPool.execute(tmp);
		}

		OsUtil::sleep_ms(JobSystemTraits::s_kBusySleepTimeMS);
	}

	//atomicLog("=== done waitForComplete()");
}

void JobSystem_T::submit(JobHandle job)
{
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

#endif


}