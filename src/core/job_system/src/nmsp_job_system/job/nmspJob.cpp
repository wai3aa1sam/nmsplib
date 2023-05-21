#include "nmsp_job_system-pch.h"
#include "nmspJob.h"

#include "nmsp_job_system/nmspJobSystem.h"

namespace nmsp {

#if 0
#pragma mark --- Job_T-Impl ---
#endif // 0
#if 1

Job_T::Task Job_T::s_emptyTask = [](const JobArgs& args) {};

void Job_T::clear()
{
	_storage.dep._dependencyCount.store(0);
	_storage.dep._runAfterThis.clear();

	_storage._task = nullptr;
	_storage._info.clear();

	_storage._jobRemainCount.store(1);
	_storage._parent = nullptr;

	_storage.setPriority(Job_T::Priority::Cirtical);

	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
	_storage._resetDebugCheck();
	#endif // _DEBUG
}

void Job_T::setParent(Job_T* parent)		
{ 
	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
	NMSP_ASSERT(!_storage._isSubmitted);
	NMSP_ASSERT(!_storage._isExecuted);
	#endif // 0

	// maybe shd set recursively
	if (!parent)
		return;
	parent->addJobCount(); 
	_storage._parent = parent; 
}

bool Job_T::isCompleted() const		{ return _storage._jobRemainCount.load() == 0 || _storage._task == nullptr; }
int  Job_T::jobRemainCount() const	{ return _storage._jobRemainCount.load(); }

void Job_T::_runAfter(Job_T* job)
{
	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
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
	#if NMSP_JOB_SYSTEM_DEBUG_CHECK
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
	return nullptr /*this->_storage._localBuf.allocate(n)*/;
}

void Job_T::_setInfo(const Info& info)
{
	_storage._info = info;
}

int		Job_T::dependencyCount() const		{ return _storage.dep._dependencyCount.load(); }
size_t	Job_T::runAfterCount() const		{ return _storage.dep._runAfterThis.size(); }

void Job_T::print() const
{
	//atomicLog("job -> jobRemainCount: {}", _storage._jobRemainCount);
	//atomicLog("job -> dependencyCount: {}", dependencyCount());
}

void Job_T::init(const Task& func, const Info& info, Job_T* parent)
{
	clear();
	new (&_storage.dep) Job_T::DepData();

	_storage._jobRemainCount.store(1);
	_storage._task = func;

	_setInfo(info);

	setParent(parent);
}

void Job_T::addJobCount()				{ _storage._jobRemainCount++; }
int	 Job_T::decrDependencyCount()		{ return _storage.dep.decrDependencyCount(); }

const Job_T::Info& Job_T::info() const
{
	return _storage._info;
}

Job_T* Job_T::setName(const char* name) 
{
	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	_name = name;
	#endif // NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER

	return this;
}

void Job_T::setEmpty()
{
	init(s_emptyTask, JobInfo(), nullptr);
}

const char* Job_T::name() const
{
	#if NMSP_JOB_SYSTEM_ENABLE_DEPENDENCY_MANAGER
	return _name.c_str();
	#else
	return nullptr;
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