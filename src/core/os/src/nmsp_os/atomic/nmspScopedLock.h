#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"
#include "nmspMutex.h"

namespace nmsp {

template<class T> using ULock_T = std::unique_lock<T>;
template<class T> using SLock_T = std::shared_lock<T>;

#if 0
#pragma mark --- ScopedLock_Base-Decl ---
#endif // 0
#if 1

template<class T_Mutex, class T_LockGuard = ULock_T<T_Mutex> >
class ScopedLock_Base : public NonCopyable
{
public:
	using Mutex = T_Mutex;
	
public:
	~ScopedLock_Base()									{}
	explicit	ScopedLock_Base(Mutex& mutex)			: _lock(mutex) { }
				ScopedLock_Base(ScopedLock_Base&& r)	: _lock(nmsp::move(r._lock)) { }

public:
	void lock(Mutex& mutex)		{ _lock.lock(); }
	bool try_lock(Mutex& mutex) { return _lock.try_lock(); }
	void unlock()				{ _lock.unlock(); }

	Mutex* detach()	{ return _lock.release(); }

public:
	Mutex* mutex() { return _lock.mutex(); }

public:
	T_LockGuard _lock;
};
template<class T_Mutex> using ScopedReadLock_Base = ScopedLock_Base<T_Mutex, SLock_T<T_Mutex> >;

#endif

#if 0
#pragma mark --- ScopedLock_T-Decl ---
#endif // 0
#if 1

template<class T, class T_Mutex, class T_Base = ScopedLock_Base<T_Mutex> >
class ScopedLock_T : public T_Base
{
public:
	using Base	= T_Base;
	using Mutex = T_Mutex;

public:
	~ScopedLock_T();
	ScopedLock_T(T& data, Mutex& mutex);
	ScopedLock_T(ScopedLock_T&& r);

public:
	void unlock() 
	{
		Base::unlock();
		_data = nullptr;
	}

public:
			T*	data();
	const	T*	data() const;

			T* operator->();
	const	T* operator->() const;

private:
	T*		_data = nullptr;
};

#endif

#if 0
#pragma mark --- ScopedLock_Selector-Decl ---
#endif // 0
#if 1

// TODO: put "using ScopedLock" to Mutex and SharedMutex, then no need to use ScopedLock_Selector
template<class T, class T_Mutex> struct ScopedLock_Selector;

template<class T> 
struct ScopedLock_Selector<T, nmsp::Mutex_T> 
{ 
	using Mutex			= nmsp::Mutex_T;
	using ScopedLock	= ScopedLock_T<T, Mutex>;
};

template<class T> 
struct ScopedLock_Selector<T, nmsp::SMutex_T> 
{ 
	using Mutex				= nmsp::SMutex_T;
	using ScopedLock		= ScopedLock_T<T, Mutex>;
	using ScopedReadLock	= ScopedLock_T<const T, Mutex, ScopedReadLock_Base<Mutex> >;
};

#endif

#if 0
#pragma mark --- ScopedLock_T-Impl ---
#endif // 0
#if 1

template<class T, class T_Mutex, class T_Base> inline
ScopedLock_T<T, T_Mutex, T_Base>::~ScopedLock_T()
{

}

template<class T, class T_Mutex, class T_Base> inline
ScopedLock_T<T, T_Mutex, T_Base>::ScopedLock_T(T& data, Mutex& mutex)
	: Base(mutex), _data(&data)
{

}

template<class T, class T_Mutex, class T_Base> inline
ScopedLock_T<T, T_Mutex, T_Base>::ScopedLock_T(ScopedLock_T&& r)
	: Base(nmsp::move(r))
{
	_data	= r._data;
	r._data	= nullptr;
}

template<class T, class T_Mutex, class T_Base> inline T*		ScopedLock_T<T, T_Mutex, T_Base>::data()			{ return _data; }
template<class T, class T_Mutex, class T_Base> inline const T*	ScopedLock_T<T, T_Mutex, T_Base>::data() const		{ return _data; }

template<class T, class T_Mutex, class T_Base> inline T*		ScopedLock_T<T, T_Mutex, T_Base>::operator->()			{ return _data; }
template<class T, class T_Mutex, class T_Base> inline const T*	ScopedLock_T<T, T_Mutex, T_Base>::operator->() const	{ return _data; }

#endif

// for not std version, no std::lock_guard, std::unique_lock, std::shared_lock
#if 0

template<class T_Mutex>
class ScopedLock_Base : public NonCopyable
{
public:
	using Mutex = T_Mutex;

public:
	~ScopedLock_Base()									{ unlock(); }
	explicit	ScopedLock_Base(Mutex& mutex)			{ lock(*_mutex); }
	ScopedLock_Base(ScopedLock_Base&& r)	: _mutex(nmsp::move(&r._mutex))	{ r._mutex = nullptr;}

public:
	void lock(Mutex& mutex) { if (_mutex != &mutex) { unlock(); mutex.lock(); _mutex = &mutex; } }
	void unlock()			
	{ 
		if (_mutex) 
		{
			_mutex->unlock(); 
			_mutex = nullptr;
		} 
	}

	void detach	()	{ _mutex = nullptr; }

public:
	Mutex* mutex() { return _mutex; }

private:
	Mutex* _mutex = nullptr;
};

template<class T_Mutex> using ReadLock = ScopedReadLock_Base<T_Mutex>;

#endif // 0

}
