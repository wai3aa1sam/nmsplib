#pragma once

#include "../common/nmsp_stl_common.h"


namespace nmsp {

#if 0
#pragma mark --- Singleton_T-Decl ---
#endif // 0
#if 1

template<class T>
class Singleton_T : public NonCopyable
{
public:
	static T*	instance();

private:

};

#if NMSP_ENABLE_MULTI_THREAD
	template<class T>
	class TLSSingleton_T : public Singleton_T<T>
	{
	public:

	private:

	};

#else
	template<class T> using TLSSingleton_T = Singleton_T<T>;
#endif // !NMSP_ENABLE_MULTI_THREAD

#endif

}