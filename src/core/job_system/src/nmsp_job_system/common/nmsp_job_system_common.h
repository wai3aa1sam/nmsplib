#pragma once

#include <nmsp_core_base.h>
#include <nmsp_profiler.h>
#include <nmsp_os.h>

#include "nmsp_job_system-config.h"
#include "nmsp_job_system_traits.h"

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

namespace nmsp {

#define JobPriority_ENUM_LIST(E) \
	E(Cirtical, = 0)	\
	E(High,)			\
	E(Normal,)			\
	E(Low,)				\
	E(_kCount,)			\
//----------
NMSP_ENUM_CLASS(JobPriority, u8)

#define NMSP_JOB_SYSTEM_JOB_TYPE_FRIEND_CLASS_DECLARE() \
	friend class Job_Base;										\
	friend class JobFor_Base;									\
	friend class JobParFor_Base;								\
	friend struct JobDispatcher									\
//---


class Job_T;
using JobHandle_T = Job_T*;

template<size_t N = 256, class ALLOC = DefaultAllocator> using BasicJobQueue_T	= AtmQueue_T<JobHandle_T, N, ALLOC>;
template<class ALLOC = DefaultAllocator>				 using JobStealQueue_T	= AtmStealQueue_T<JobHandle_T, BasicJobQueue_T<256, ALLOC> >;
template<class ALLOC = DefaultAllocator>				 using JobQueue_T		= AtmPriorityQueue_T<JobHandle_T, enumInt(JobPriority::_kCount), JobPriority, JobStealQueue_T<ALLOC> >;


}