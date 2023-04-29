#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

namespace nmsp {

#if 0
#pragma mark --- ThreadLS_Std-Impl ---
#endif // 0
#if 1

template<class T>
class ThreadLS_Std : public NonCopyable
{
public:

	using ValueType = T;

public:
	ThreadLS_Std() { _notYetSupported(); };
	~ThreadLS_Std() = default;

			T& data();
	const	T& data() const;


private:
	thread_local static T _data;
};

#endif


#if 0
#pragma mark --- ThreadLS_Std-Impl ---
#endif // 0
#if 1


template<class T> inline
		T& ThreadLS_Std<T>::data()
{
	return _data;
}

template<class T> inline
const	T& ThreadLS_Std<T>::data() const
{
	return _data;
}

#endif

}