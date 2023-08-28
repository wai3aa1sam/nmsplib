#pragma once

#include "nmsp_job_system/common/nmsp_job_system_common.h"
#include "nmspJob.h"

namespace nmsp 
{

// TODO: maybe change to this design
// useless now

#define JobExtensionType_ENUM_LIST(E) \
	E(None, = 0) \
	E(IJobBeginEnd,) \
	E(JobCluster,) \
	E(_kCount,) \
//---
NMSP_ENUM_CLASS(JobExtensionType, u8);


class IJobBeginEnd : public NonCopyable
{
	friend class Job_T;
	friend class ThreadPool_T;

public:
	#if NMSP_JOB_SYSTEM_DEVELOPMENT

	IJobBeginEnd() 
	{
		_hasExecutedOnBegin = false;
		_hasExecutedOnEnd	= false;
	};

	virtual void onBegin()	
	{ 
		NMSP_ASSERT(!_hasExecutedOnBegin, "onBegin() shd only execute once");	
		_hasExecutedOnBegin = true; 
	};

	virtual void onEnd()	
	{ 
		NMSP_ASSERT(!_hasExecutedOnEnd, "onEnd() shd only execute once");	
		_hasExecutedOnEnd = true; 

	};
	#else

	IJobBeginEnd() 
	{

	};

	virtual void onBegin()	{};
	virtual void onEnd()	{};

	#endif

	virtual ~IJobBeginEnd() = default;

private:
	#if NMSP_JOB_SYSTEM_DEVELOPMENT
	volatile bool _hasExecutedOnBegin;
	volatile bool _hasExecutedOnEnd;
	#endif
};


}