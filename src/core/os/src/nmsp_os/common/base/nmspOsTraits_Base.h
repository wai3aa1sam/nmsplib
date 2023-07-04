#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_os-config.h"

#include <thread>

namespace nmsp {

//template<class T> struct WindowVec2_T;
//template<class T> struct WindowRect2_T;

//template<class T> struct Vec2_T;
namespace math { template<class T> struct Rect2_T; }

enum class OsPlatform
{
	Windows = 0,
	Linux,
	_kCount,
};

#if 0
#pragma mark --- OsTraits-Impl ---
#endif // 0
#if 1

inline thread_local int		_internal_threadLocalId			= -1;
inline thread_local bool	_internal_isSettedThreadLocalId = false;

class ThreadDefaultStorage_T;
class AllThreadsDefaultStorage_T;

using ThreadStorage		= ThreadDefaultStorage_T;
using AllThreadsStorage = AllThreadsDefaultStorage_T;

struct OsDefaultTraits_Base : public CoreBaseTraits
{
public:
	static constexpr const char* s_mainThreadName = "Main Thread";

public:
	static constexpr OsPlatform				platform();
	static constexpr EnumInt<OsPlatform>	platformInt();
	
	template<class T>	using Rect2  = math::Rect2_T<T>;
						using Rect2f = Rect2<f32>;
						using Rect2d = Rect2<f64>;
						using Rect2i = Rect2<i32>;

	template<class T>	using Vec2  = Vec2_T<T>;
						using Vec2f = Vec2<f32>;
						using Vec2d = Vec2<f64>;
						using Vec2i = Vec2<i32>;

	using SizeType	= size_t;
	using IndexType	= i32;
	using FileSize  = size_t;


	// Multi-thread Params
	static constexpr int		s_kMainThreadLocalId		= 0;
	static constexpr SizeType	s_kEstLogicalThreadCount	= 32;

	static void		setThreadLocalId	(int id) { NMSP_ASSERT(!_internal_isSettedThreadLocalId && ((id >= 0 && id <= logicalThreadCount()) || id == s_kMainThreadLocalId), "threadLocalId should set only once"); _internal_threadLocalId = id; _internal_isSettedThreadLocalId = true; }
	static void		resetThreadLocalId	()		 { _internal_threadLocalId = -1; _internal_isSettedThreadLocalId = false; }
	static int		threadLocalId		()		 { NMSP_ASSERT( _internal_isSettedThreadLocalId, "threadLocalId is not set, set it before use");	return _internal_threadLocalId; }
	static bool		isMainThread		()		 { return threadLocalId() == s_kMainThreadLocalId; }
	static SizeType	logicalThreadCount	()		 { return std::thread::hardware_concurrency(); }

	//static AllThreadsStorage*	_internal_allThreadsStorage	();
	//static ThreadStorage*		_internal_threadStorage		();
};

#endif

}
