#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"

#include "nmspTypeThread.h"
#include <nmsp_os/atomic/extra/nmspAtomicQueue.h>


namespace nmsp {

class ThreadStorage_T;
class ThreadPool_T;
class JobSystem_T;

#if 0
#pragma mark --- WorkerThread_T-Decl ---
#endif // 0
#if 1

struct WorkerThread_CreateDesc : public TypeThread_T::CreateDesc
{

};

class WorkerThread_T : public TypeThread_T
{
public:
	using Base = TypeThread_T;

	using CreateDesc		= WorkerThread_CreateDesc;
	using CreateDesc_Base	= Base::CreateDesc_Base;

	using JobQueue		= JobQueue_T<>;
	using JobHandle		= JobHandle_T;
	using ThreadPool	= ThreadPool_T;
	using ThreadStorage = ThreadStorage_T;
	using JobSystem_T	= JobSystem_T;

public:
	static CreateDesc makeCDesc();

public:
	WorkerThread_T();
	virtual ~WorkerThread_T();

	void submit(JobHandle task);

public:
	ThreadStorage& threadStorage();
	JobQueue& queue();

protected:
	virtual void onCreate(const CreateDesc_Base& cDescBase) override;
	virtual void onDestroy() override;

	virtual void* onRoutine() override;

protected:
	bool _tryGetJob(JobHandle& job);

private:
	JobQueue	_jobs;
};

inline
WorkerThread_T::CreateDesc WorkerThread_T::makeCDesc()
{
	return CreateDesc{};
}

inline WorkerThread_T::JobQueue& WorkerThread_T::queue() { return _jobs; }

#endif

}