#pragma once

#include "../common/nmsp_stl_common.h"


namespace nmsp {

#if 0
#pragma mark --- StackSingleton_T-Decl ---
#endif // 0
#if 1

template<class T>
class StackSingleton_T : public NonCopyable
{
public:
	static T* instance();

public:
	StackSingleton_T();
	~StackSingleton_T();

private:
	static T* s_instance;
};


#endif

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


#if 0
#pragma mark --- StackSingleton_T-Impl ---
#endif // 0
#if 1

template<class T> inline
	T* StackSingleton_T<T>::instance()
{
	return s_instance;
}

template<class T> inline
	StackSingleton_T<T>::StackSingleton_T()
{
	NMSP_ASSERT(!s_instance);
	s_instance = sCast<T*>(this);
}

template<class T> inline
	StackSingleton_T<T>::~StackSingleton_T()
{
	NMSP_ASSERT(s_instance);
	s_instance = nullptr;
}
#endif

}