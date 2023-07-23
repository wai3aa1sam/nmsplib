#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

#include "nmsp_os/atomic/nmspMutex.h"
#include "nmsp_os/atomic/nmspCondVar.h"

namespace nmsp {

template<class DATA> using EnableIfSMutex = EnableIf< IsSame<typename DATA::Mutex, SMutex_T> >;

#if 0
#pragma mark --- Locked_T-Decl ---
#endif // 0
#if 1

template<class T, class MUTEX, class LOCK>
class Locked_T
{
	using Mutex = MUTEX;
	using Lock	= LOCK;
public:
	Locked_T(T& data, Mutex& mutex);
	Locked_T(Locked_T&& r);

	T* operator->();
	T& operator* ();

	const T* operator->() const;
	const T& operator* () const;

private:
	Lock	_lock;			// should lock first
	T*		_data = nullptr;
};

#endif

#if 0
#pragma mark --- MutexProtected_T_-Decl ---
#endif // 0
#if 1

template<class T, class MUTEX, class ENABLE = void>
class MutexProtected_Data_T
{
public:
	using Mutex = MUTEX;
	using ULock = ULock_T<Mutex>;
	using SLock = SLock_T<Mutex>;

protected:
	Mutex	_mutex;
	T		_data;
};

template<class T, class DATA, class ENABLE = void>
class MutexProtected_T_ : private DATA
{
public:
	using Mutex = typename DATA::Mutex; 
	using ULock = typename DATA::ULock;
	using SLock = typename DATA::SLock;

	NMSP_NODISCARD Locked_T<T, Mutex, ULock>		scopedULock();
	NMSP_NODISCARD Locked_T<const T, Mutex, ULock>	scopedULock() const;

protected:
	using DATA::_mutex;
	using DATA::_data;
};

template<class T, class DATA>
class MutexProtected_T_<T, DATA, EnableIfSMutex<DATA> > : private DATA
{
public:
	using Mutex = typename DATA::Mutex;
	using ULock = typename DATA::ULock;
	using SLock = typename DATA::SLock;

	NMSP_NODISCARD Locked_T<T, Mutex, ULock> scopedULock();
	NMSP_NODISCARD Locked_T<T, Mutex, SLock> scopedSLock();

protected:
	using DATA::_mutex;
	using DATA::_data;
};

template<class T> using MutexProtected_T	= MutexProtected_T_<T, MutexProtected_Data_T<T, Mutex_T>  >;
template<class T> using SMutexProtected_T	= MutexProtected_T_<T, MutexProtected_Data_T<T, SMutex_T> >;

#endif

#if 0
#pragma mark --- LockedCV_T-Decl ---
#endif // 0
#if 1

template<class T, class MUTEX, class CONDVAR, class LOCK>
class LockedCV_T
{
	using Mutex		= MUTEX;
	using CondVar	= CONDVAR;
	using Lock		= LOCK;
public:
	LockedCV_T(T& data, Mutex& mutex, CondVar& condvar);
	LockedCV_T(LockedCV_T&& r);

	T* operator->();
	T& operator* ();

	void wait();

private:
	//Locked_T _locked; // should lock first
	Lock		_lock;
	CondVar*	_condvar	= nullptr;
	T*			_data		= nullptr;
};

#endif

#if 0
#pragma mark --- CondVarProtected_T_-Decl ---
#endif // 0
#if 1

template<class T, class MUTEX, class CONDVAR, class ENABLE = void>
class CondVarProtected_Data_T
{
public:
	using Mutex		= MUTEX;
	using CondVar	= CONDVAR;
	using ULock		= ULock_T<Mutex>;
	using SLock		= SLock_T<Mutex>;

public:
	void notifyAll();

protected:
	Mutex	_mutex;
	CondVar	_condvar;
	T		_data;
};

template<class T, class DATA, class ENABLE = void>
class CondVarProtected_T_ : public DATA
{
public:
	using Mutex		= typename DATA::Mutex;
	using CondVar	= typename DATA::CondVar;
	using ULock		= typename DATA::ULock;
	using SLock		= typename DATA::SLock;

public:
	NMSP_NODISCARD LockedCV_T<T, Mutex, CondVar, ULock> scopedULock();

protected:
	using DATA::_mutex;
	using DATA::_condvar;
	using DATA::_data;
};

template<class T, class DATA>
class CondVarProtected_T_<T, DATA, EnableIfSMutex<DATA> > : public DATA
{
public:
	using Mutex		= typename DATA::Mutex;
	using CondVar	= typename DATA::CondVar;
	using ULock		= typename DATA::ULock;
	using SLock		= typename DATA::SLock;

public:
	NMSP_NODISCARD LockedCV_T<T, Mutex, CondVar, ULock> scopedULock();
	NMSP_NODISCARD LockedCV_T<T, Mutex, CondVar, SLock> scopedSLock();

protected:
	using DATA::_mutex;
	using DATA::_condvar;
	using DATA::_data;
};

template<class T> using CondVarProtected_T		= CondVarProtected_T_<T, CondVarProtected_Data_T<T, Mutex_T,  CondVar_T>  >;
template<class T> using SMtxCondVarProtected_T	= CondVarProtected_T_<T, CondVarProtected_Data_T<T, SMutex_T, CondVarA_T> >;

#endif


#if 0
#pragma mark --- Locked_T-Impl ---
#endif // 0
#if 1

template<class T, class MUTEX, class LOCK> inline
Locked_T<T, MUTEX, LOCK>::Locked_T(T& data, Mutex& mutex)
	: _lock(mutex), _data(&data)
{

}

template<class T, class MUTEX, class LOCK> inline
Locked_T<T, MUTEX, LOCK>::Locked_T(Locked_T&& r)
	: _lock(std::move(r._lock))
{
	_data	= r._data;
	r._data = nullptr;
}

template<class T, class MUTEX, class LOCK> inline
T* Locked_T<T, MUTEX, LOCK>::operator->() 
{ 
	return  _data; 
}

template<class T, class MUTEX, class LOCK> inline
T& Locked_T<T, MUTEX, LOCK>::operator*()	
{ 
	return *_data; 
}

template<class T, class MUTEX, class LOCK> inline const T* Locked_T<T, MUTEX, LOCK>::operator->() const { return _data; }
template<class T, class MUTEX, class LOCK> inline const T& Locked_T<T, MUTEX, LOCK>::operator* () const { return *_data; }

#endif

#if 0
#pragma mark --- MutexProtected_T_-Impl ---
#endif // 0
#if 1

template<class T, class DATA, class ENABLE> inline
Locked_T<T, typename MutexProtected_T_<T, DATA, ENABLE>::Mutex, typename DATA::ULock> 
MutexProtected_T_<T, DATA, ENABLE>::scopedULock() 
{ 
	return { _data, _mutex }; 
}

template<class T, class DATA> inline
Locked_T<T, typename MutexProtected_T_<T, DATA, EnableIfSMutex<DATA> >::Mutex, typename DATA::ULock> 
MutexProtected_T_<T, DATA, EnableIfSMutex<DATA> >::scopedULock() 
{ 
	return { _data, _mutex }; 
}

template<class T, class DATA> inline 
Locked_T<T, typename MutexProtected_T_<T, DATA, EnableIfSMutex<DATA> >::Mutex, typename DATA::SLock> 
MutexProtected_T_<T, DATA, EnableIfSMutex<DATA> >::scopedSLock() 
{ 
	return { _data, _mutex }; 
}

#endif

#if 0
#pragma mark --- LockedCV_T-Impl ---
#endif // 0
#if 1

template<class T, class MUTEX, class CONDVAR, class LOCK> inline
LockedCV_T<T, MUTEX, CONDVAR, LOCK>::LockedCV_T(T& data, Mutex& mutex, CondVar& condvar)
	: _lock(mutex), _condvar(&condvar), _data(&data)
{
}

template<class T, class MUTEX, class CONDVAR, class LOCK> inline
LockedCV_T<T, MUTEX, CONDVAR, LOCK>::LockedCV_T(LockedCV_T&& r)
	: _lock(std::move(r._lock))
{
	_condvar	= r._condvar;
	_data		= r._data;
	r._condvar	= nullptr;
	r._data		= nullptr;
}

template<class T, class MUTEX, class CONDVAR, class LOCK> inline
T*		LockedCV_T<T, MUTEX, CONDVAR, LOCK>::operator->() 
{ 
	return  _data; 
}

template<class T, class MUTEX, class CONDVAR, class LOCK> inline
T&		LockedCV_T<T, MUTEX, CONDVAR, LOCK>::operator*()  
{ 
	return *_data; 
}

template<class T, class MUTEX, class CONDVAR, class LOCK> inline
void	LockedCV_T<T, MUTEX, CONDVAR, LOCK>::wait()
{
	if (_condvar)
	{
		_condvar->wait(_lock); 
	}
}

#endif

#if 0
#pragma mark --- CondVarProtected_T_-Decl ---
#endif // 0
#if 1

template<class T, class MUTEX, class CONDVAR, class ENABLE> inline
void CondVarProtected_Data_T<T, MUTEX, CONDVAR, ENABLE>::notifyAll()			
{ 
	_condvar.notify_all(); 
}

template<class T, class DATA, class ENABLE> inline NMSP_NODISCARD
LockedCV_T<T, typename DATA::Mutex, typename DATA::CondVar, typename DATA::ULock> 
CondVarProtected_T_<T, DATA, ENABLE>::scopedULock() 
{ 
	return { _data, _mutex, _condvar }; 
}

template<class T, class DATA> inline NMSP_NODISCARD 
LockedCV_T<T, typename DATA::Mutex, typename DATA::CondVar, typename DATA::ULock> 
CondVarProtected_T_<T, DATA, EnableIfSMutex<DATA> >::scopedULock() 
{ 
	return { _data, _mutex, _condvar}; 
}

template<class T, class DATA> inline NMSP_NODISCARD 
LockedCV_T<T, typename DATA::Mutex, typename DATA::CondVar, typename DATA::SLock> 
CondVarProtected_T_<T, DATA, EnableIfSMutex<DATA> >::scopedSLock() 
{ 
	return { _data, _mutex, _condvar}; 
}


#endif

}
