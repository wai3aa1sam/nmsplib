#pragma once

#include <nmsp_core_base/common/nmspNmspTraits.h>

#include <thread>

namespace nmsp {

#if 0
#pragma mark --- NmspStlTraits-Impl ---
#endif // 0
#if 1

inline thread_local i32		_internal_threadLocalId			= 0;
inline thread_local bool	_internal_isSettedThreadLocalId = false;

class ThreadDefaultStorage_T;
class AllThreadsDefaultStorage_T;

using ThreadStorage		= ThreadDefaultStorage_T;
using AllThreadsStorage = AllThreadsDefaultStorage_T;

struct NmspStlDefaultTraits_T : public NmspTraits
{
	// Multi-thread Params
	static constexpr size_t s_kMainThreadLocalId		= 0;
	static constexpr size_t	s_kEstLogicalThreadCount	= 32;

	static void		setThreadLocalId	(i32 id) { NMSP_ASSERT(!_internal_isSettedThreadLocalId,	"threadLocalId should set only once");			_internal_threadLocalId = id; _internal_isSettedThreadLocalId = true; }
	static i32		threadLocalId		()		 { /*NMSP_ASSERT(_internal_threadLocalId != -1,		"threadLocalId is -1, set it before use");*/	return _internal_threadLocalId; }
	static bool		isMainThread		()		 { return threadLocalId() == s_kMainThreadLocalId; }
	static size_t	logicalThreadCount	()		 { return std::thread::hardware_concurrency(); }


	//static AllThreadsStorage*	_internal_allThreadsStorage	();
	//static ThreadStorage*		_internal_threadStorage		();
};

#if !NMSP_CUSTOM_STL_TRAITS

using NmspStlTraits = NmspStlDefaultTraits_T;

#else

#endif // 

#endif

}