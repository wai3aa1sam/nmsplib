#include "nmsp_stl-pch.h"

#include "nmsp_stl/common/nmsp_stl_traits.h"

#include "nmsp_stl/atomic/nmspThreadStorage.h"
#include "nmsp_stl/atomic/nmspAtomicUtil.h"

namespace nmsp {

#if 0
#pragma mark --- StlTraits-Impl ---
#endif // 0
#if 1

//AllThreadsStorage*	NmspStlDefaultTraits_T::_internal_allThreadsStorage()
//{
//	#if NMSP_ENABLE_THREAD_LOCAL
//	return nullptr;
//
//	#else
//	static AllThreadsStorage* _internal_allThreadsStorage = nullptr;
//	static CallOnce co{
//		[&]()
//		{
//			_internal_allThreadsStorage = NMSP_NEW(_internal_allThreadsStorage);
//		}
//	};
//	return _internal_allThreadsStorage;
//	#endif // NMSP_ENABLE_THREAD_LOCAL
//}
//
//ThreadStorage*		NmspStlDefaultTraits_T::_internal_threadStorage			()
//{
//	#if NMSP_ENABLE_THREAD_LOCAL
//	return nullptr;
//
//	#else
//	NMSP_ASSERT(_internal_allThreadsStorage(), "threadStorage should not be use if NMSP_ENABLE_THREAD_LOCAL is 1");
//	return (*_internal_allThreadsStorage())[threadLocalId()];
//
//	#endif
//}

#endif

}