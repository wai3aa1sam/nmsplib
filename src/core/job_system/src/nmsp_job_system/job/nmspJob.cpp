#include "nmsp_job_system-pch.h"
#include "nmspJob.h"

#include "nmsp_job_system/nmspJobSystem.h"
#include "nmsp_job_system/job/nmspJobDispatch.h"

namespace nmsp {

#if 0
#pragma mark --- Job_T-Impl ---
#endif // 0
#if 1

Job_T::Task Job_T::s_emptyTask = [](const JobArgs& args) {};

Job_T::Job_T()
{
	NMSP_TODO("make bool member data to 1 bit");
}

Job_T::~Job_T()
{

}

void Job_T::clear()
{
	_storage.dep._dependencyCount.store(0);
	_storage.dep._runAfterThis.clear();

	_storage._task = nullptr;
	_storage._info.clear();

	_storage._parent = nullptr;
	_storage._jobRemainCount.store(1);
	_storage._hasExecutedOnEnd = false;

	_storage.setPriority(Job_T::Priority::Cirtical);

	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	_storage._resetDebugCheck();
	#endif // _DEBUG
}

void Job_T::setParent(Job_T* parent)		
{ 
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(!_storage._isSubmitted);
	NMSP_ASSERT(!_storage._isExecuted);
	#endif // 0

	// maybe shd set recursively
	if (!parent)
		return;
	parent->addJobCount(); 
	_storage._parent = parent; 
}

void 
Job_T::setDispatchJob(JobDispatch_Base* dispatchJob)
{
	NMSP_ASSERT(!_storage._dispatchJob, "");
	_storage._dispatchJob = dispatchJob;
}

Job_T::JobCountType 
Job_T::decrRemainJobCount()
{
	auto ret = _storage._jobRemainCount.fetch_sub(1); // i--
	return ret - 1;
}

bool 
Job_T::isCompleted() const		
{
	bool jobCompleted		= _storage._jobRemainCount.load() == 0 ;				NMSP_UNUSED(jobCompleted);
	//bool normalCompleted	= jobCompleted && !dispatchJob();						NMSP_UNUSED(normalCompleted);
	//bool isBypass			= this == nullptr || _storage._task == nullptr;			NMSP_UNUSED(isBypass);

	bool correctCompleted	= (jobCompleted && _storage._hasExecutedOnEnd)
								|| (jobCompleted && !_storage._dispatchJob);			NMSP_UNUSED(correctCompleted);
	
	return correctCompleted;
}

Job_T::JobCountType  
Job_T::jobRemainCount() const	
{ 
	return _storage._jobRemainCount.load(); 
}

void Job_T::_runAfter(Job_T* job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(job->_storage._isAllowAddDeps);
	NMSP_ASSERT(_storage._isAllowAddDeps);
	#endif // 0

	NMSP_ASSERT(job != this);
	//NMSP_ASSERT(isMainThread(), "must only add job dependency in main thread");

	this->_storage.dep._dependencyCount.fetch_add(1);
	job->_storage.dep._runAfterThis.emplace_back(this);	// _runAfterThis is correct, not worng

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::instance()->XRunBeforeY(job, this);
	DependencyManager::instance()->XRunAfterY(this, job);
	#endif // NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
}

void Job_T::_runBefore(Job_T* job)
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	NMSP_ASSERT(job->_storage._isAllowAddDeps);
	NMSP_ASSERT(_storage._isAllowAddDeps);
	#endif // 0

	NMSP_ASSERT(job != this);
	//NMSP_ASSERT(isMainThread(), "must only add job dependency in main thread");

	job->_storage.dep._dependencyCount.fetch_add(1);
	this->_storage.dep._runAfterThis.emplace_back(job);	// _runAfterThis is correct, not worng

	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	DependencyManager::instance()->XRunBeforeY(this, job);
	DependencyManager::instance()->XRunAfterY(job, this);
	#endif // NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
}

void* Job_T::_allocate(size_t n)
{
	NMSP_NOT_YET_SUPPORT();
	return nullptr /*this->_storage._localBuf.allocate(n)*/;
}

Job_T::JobHandle Job_T::parent()
{
	return _storage._parent;
}

JobDispatch_Base* Job_T::_dispatchJob()
{
	return _storage._dispatchJob;
}

const JobDispatch_Base* 
Job_T::dispatchJob() const 
{ 
	return _storage._dispatchJob; 
}

void 
Job_T::_setInfo(const Info& info)
{
	_storage._info = info;
}

Job_T::JobCountType	
Job_T::dependencyCount() const		
{ 
	return _storage.dep._dependencyCount.load(); 
}

size_t 
Job_T::runAfterCount() const		
{ 
	return _storage.dep._runAfterThis.size(); 
}

void Job_T::print() const
{
	//atomicLog("job -> jobRemainCount: {}", _storage._jobRemainCount);
	//atomicLog("job -> dependencyCount: {}", dependencyCount());
}

void Job_T::init(const Task& func, const Info& info, Job_T* parent, JobCountType remainCount)
{
	clear();
	new (&_storage.dep) Job_T::DepData();

	_storage._jobRemainCount.store(remainCount);
	_storage._task = func;

	_setInfo(info);

	setParent(parent);
}

void 
Job_T::init(const Task& func, const Info& info, JobDispatch_Base* dispatchJob, JobHandle parent)
{
	init(func, info, parent);
	setDispatchJob(dispatchJob);
}

void 
Job_T::init(const Task& func, const Info& info, JobDispatch_Base* dispatchJob, bool forceBeginEnd, JobHandle parent)
{
	init(func, info, dispatchJob, parent);
	_storage._isForceOnBeginEnd = forceBeginEnd;
}

void 
Job_T::addJobCount()				
{ 
	_storage._jobRemainCount++; 
}

Job_T::JobCountType		
Job_T::decrDependencyCount()
{ 
	return _storage.dep.decrDependencyCount(); 
}

void 
Job_T::invokeOnEnd()
{
	if (dispatchJob())
	{
		_dispatchJob()->onEnd();
	}
	NMSP_CORE_ASSERT(!_storage._hasExecutedOnEnd || !dispatchJob(), "should only invoke onEnd() once");
	_storage._hasExecutedOnEnd = true;
}

void 
Job_T::setIsForceOnBeginEnd(bool v)
{
	_storage._isForceOnBeginEnd = v;
}

bool 
Job_T::isForceOnBeginEnd() const
{
	return _storage._isForceOnBeginEnd;
}


const Job_T::Info& Job_T::info() const
{
	return _storage._info;
}

Job_T* Job_T::setName(const char* name) 
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT || NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	_name = name;
	#endif // NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER

	return this;
}

void Job_T::setEmpty()
{
	init(s_emptyTask, JobInfo{}, nullptr);
}

void 
Job_T::createParentJob()
{
	init(Job_T::s_emptyTask, JobInfo{}, nullptr, 0);
}

const char* Job_T::name() const
{
	#if NMSP_JOB_SYSTEM_DEVELOPMENT || NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	return _name.c_str();
	#else
	return "";
	#endif // NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
}

#endif


#if 0
#pragma mark --- Job_T::DepData-Impl ---
#endif // 0
#if 1

Job_T::DepData::DepData()
	: _runAfterThis(JobSystem_T::_defaultAllocator().jobDepAllocator())
{
	_dependencyCount.store(0);
}


#endif // 1


}