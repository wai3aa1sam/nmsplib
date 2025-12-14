#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"
#include "nmspScopedLock.h"
#include "nmspCondVar.h"
#include "nmspMutexProtected.h"

namespace nmsp
{

#if 0
#pragma mark --- nmspCondMutex_T-Impl ---
#endif // 0
#if 1

template<bool IsBroadcast>
class CondMutex_T : public NonCopyable
{
public:
	using This		= CondMutex_T;
	using Mutex		= Mutex_T;
	using CondVar	= CondVar_T;

	using Int		= i64;

public:
	class ScopedLock //: public ScopedLock_Base<Mutex>
	{
	public:
		//using Base				= ScopedLock_Base<Mutex>;
		using ScopedMutexLock	= ScopedLock_Base<Mutex>;

	public:
		~ScopedLock();
		ScopedLock(CondMutex_T& condMutex);
		ScopedLock(ScopedLock && r);

	public:
		void lock(		CondMutex_T& condMutex);
		bool try_lock(	CondMutex_T& condMutex);
		void unlock	();
		void detach	();

		void signal	()	{ _condMutex->signal(); }
		void wait	()	{ _condMutex->wait(*this);   }
		bool timed_wait(Int milliseconds) { return _condMutex->timed_wait(*this, milliseconds); }

		CondMutex_T*		condMutex() { return _condMutex; }
		ScopedMutexLock&	mutexLock() { return _mutexLock; } // _mutexLock; }

	private:
		ScopedMutexLock		_mutexLock;
		CondMutex_T*		_condMutex = nullptr;
	};

	void lock		()	{ _mutex.lock(); }
	bool tryLock	()	{ return _mutex.try_lock(); }

	void unlock		() { 
		_mutex.unlock();
		if constexpr (IsBroadcast) {
			_cond.broadcast();
		} else {
			_cond.signal();
		}
	}

	void wait		(ScopedLock& locked)		{ _cond.wait(locked.mutexLock()); }
	bool timed_wait	(ScopedLock& locked, Int milliseconds) { 
		return _cond.timed_wait(locked.mutexLock(), milliseconds);
	}

	void signal		()							{ _cond.signal(); }
	void broadcast	()							{ _cond.broadcast(); } // static_assert(false, "set IsBroadcast = true, to use broadcast()");

public:
	Mutex&		mutex	() { return _mutex; }
	CondVar&	cond	() { return _cond;  }

private:
	Mutex	_mutex;
	CondVar	_cond;
};

template<class T, bool IsBroadcast> 
struct ScopedLock_Selector<T, CondMutex_T<IsBroadcast> > 
{ 
	using Mutex			= CondMutex_T<IsBroadcast>;
	using ScopedLock	= ScopedLock_T<T, Mutex, typename Mutex::ScopedLock>;
};

#endif


#if 0
#pragma mark --- nmspCondMutexProtected_T-Impl ---
#endif // 0
#if 1

template<class T_Data, bool IsBroadcast>
class CondMutexProtected_T : public MutexProtected_T<T_Data, CondMutex_T<IsBroadcast> > 
{
	using Base = MutexProtected_T<T_Data, CondMutex_T<IsBroadcast> >;
public:
	template<class... T_Args>
	CondMutexProtected_T(T_Args&&... args) : Base(nmsp::forward(args)...) {}

	void signal		() { Base::mutex().signal(); }
	void broadcast	() { Base::mutex().broadcast(); }
};

#endif

#if 0
#pragma mark --- nmspCondMutex_T-Impl ---
#endif // 0
#if 1

template<bool IsBroadcast> inline
CondMutex_T<IsBroadcast>::ScopedLock::ScopedLock(ScopedLock && r)
	: _mutexLock(nmsp::move(r._mutexLock)) //_mutexLock(nmsp::move(r._mutexLock))
	, _condMutex(r._condMutex)
{
	r._condMutex = nullptr;
}

template<bool IsBroadcast> inline
CondMutex_T<IsBroadcast>::ScopedLock::ScopedLock(CondMutex_T& condMutex)
	: _mutexLock(condMutex.mutex())
{
	_condMutex = &condMutex;
}

template<bool IsBroadcast> inline
CondMutex_T<IsBroadcast>::ScopedLock::~ScopedLock() {
	_mutexLock.detach();
	unlock();
}

template<bool IsBroadcast> inline
void 
CondMutex_T<IsBroadcast>::ScopedLock::lock(CondMutex_T& condMutex) {
	unlock();
	mutexLock().lock(condMutex.mutex());
	_condMutex = &condMutex;
}

template<bool IsBroadcast> inline
bool 
CondMutex_T<IsBroadcast>::ScopedLock::try_lock(CondMutex_T& condMutex) {
	unlock();
	if (mutexLock().try_lock(condMutex.mutex())) {
		_condMutex = &condMutex;
		return true;
	}
	return false;
}

template<bool IsBroadcast> inline
void
CondMutex_T<IsBroadcast>::ScopedLock::unlock() {
	if (_condMutex) {
		_condMutex->unlock();
		_condMutex = nullptr;
	}
}

template<bool IsBroadcast> inline
void
CondMutex_T<IsBroadcast>::ScopedLock::detach() {
	mutexLock().detach();
	_condMutex = nullptr;
}

#endif // 1

}