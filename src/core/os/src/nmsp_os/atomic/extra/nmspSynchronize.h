#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#include <future>

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

#if NMSP_OS_BUILD_SYNC_STD

namespace nmsp {

template<class T> using Future_T	= std::future<T>;
template<class T> using Promise_T	= std::promise<T>;

}

#elif NMSP_OS_BUILD_SYNC_NMSP



#else

#error "nmsp_os build sync"

#endif // NMSP_OS_BUILD_SYNC_STD


namespace nmsp
{ 

#if 0
#pragma mark --- CheckOnce_T-Decl/Impl ---
#endif // 0
#if 1

class CheckOnce_T
{
public:
	CheckOnce_T() 
	{ 
		_hasExecuted = false; 
	}

	~CheckOnce_T()
	{
		NMSP_ASSERT(_hasExecuted, "");
	}

	void check() 
	{
		NMSP_ASSERT(!_hasExecuted, "");
	}

private:
	volatile bool _hasExecuted = false;		// use Atm<bool> to ensure the hit rate is 100%
};

#endif


#if 0
#pragma mark --- CheckExclusive_T-Decl/Impl ---
#endif // 0
#if 1

class CheckExclusive_T
{
public:
	CheckExclusive_T() 
	{ 
		_hasLocked = false;
	}

	void acquire() 
	{
		NMSP_ASSERT(!_hasLocked, "");
		_hasLocked = true;
	}

	void release()
	{
		NMSP_ASSERT(_hasLocked, "");
		_hasLocked = false;
	}

private:
	volatile bool _hasLocked = false;		// use Atm<bool> to ensure the hit rate is 100%
};

class ScopedCheckExclusive_T
{
public:
	ScopedCheckExclusive_T(CheckExclusive_T* p)
		: _p(p)
	{
		_p->acquire();
	}

	~ScopedCheckExclusive_T()
	{
		_p->release();
	}

private:
	CheckExclusive_T* _p = nullptr;
};



#endif

}

