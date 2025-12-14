#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"
#include "nmsp_os/atomic/nmspScopedLock.h"

namespace nmsp {

#if 0
#pragma mark --- MutexProtected_T_-Decl ---
#endif // 0
#if 1

template<class T, class T_Mutex = Mutex_T>
class MutexProtected_T : public NonCopyable
{
public:
	using ScopedLock_Selector = ScopedLock_Selector<T, T_Mutex>;
	using Mutex			= T_Mutex;
	using ScopedLock	= typename ScopedLock_Selector::ScopedLock;

public:
	NMSP_NODISCARD ScopedLock scopedLock();

	Mutex&	mutex();

private:
	Mutex	_mutex;
	T		_data;
};

#endif

#if 0
#pragma mark --- MutexProtected_T_-Decl ---
#endif // 0
#if 1

template<class T, class T_Mutex = SMutex_T>
class SharedMutexProtected_T : public NonCopyable
{
public:
	using ScopedLock_Selector = ScopedLock_Selector<T, T_Mutex>;
	using Mutex				= T_Mutex;
	using ScopedLock		= typename ScopedLock_Selector::ScopedLock;
	using ScopedReadLock	= typename ScopedLock_Selector::ScopedReadLock;

public:
	NMSP_NODISCARD ScopedLock		scopedLock();
	NMSP_NODISCARD ScopedReadLock	scopedReadLock();

	Mutex&	mutex();

private:
	Mutex	_mutex;
	T		_data;
};

#endif

#if 0
#pragma mark --- MutexProtected_T-Impl ---
#endif // 0
#if 1

template<class T, class T_Mutex> inline auto MutexProtected_T<T, T_Mutex>::scopedLock()		-> ScopedLock	{ return ScopedLock{_data, _mutex}; }
template<class T, class T_Mutex> inline auto MutexProtected_T<T, T_Mutex>::mutex()			-> Mutex&		{ return _mutex; }

#endif

#if 0
#pragma mark --- SharedMutexProtected_T-Impl ---
#endif // 0
#if 1

template<class T, class T_Mutex> inline auto SharedMutexProtected_T<T, T_Mutex>::scopedLock()			-> ScopedLock		{ return ScopedLock{_data, _mutex}; }
template<class T, class T_Mutex> inline auto SharedMutexProtected_T<T, T_Mutex>::scopedReadLock()		-> ScopedReadLock	{ return ScopedReadLock{_data, _mutex}; }
template<class T, class T_Mutex> inline auto SharedMutexProtected_T<T, T_Mutex>::mutex()				-> Mutex&			{ return _mutex; }

#endif

}
