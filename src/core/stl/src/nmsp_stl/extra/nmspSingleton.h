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
	static T* instance();

public:
	/*static void create();
	static void destroy();*/

	static void init();
	static void terminate();

protected:
	Singleton_T();
	~Singleton_T();

	static T* s_instance;
};

#endif

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

protected:
	static T* s_instance;
};

#endif

	
#if 0
#pragma mark --- Singleton_T-Impl ---
#endif // 0
#if 1

template<class T> inline
T* 
Singleton_T<T>::instance()
{
	NMSP_ASSERT(s_instance);
	return s_instance;
}

template<class T> inline
Singleton_T<T>::Singleton_T()
{
	NMSP_ASSERT(!s_instance);
	s_instance = sCast<T*>(this);
}

template<class T> inline
Singleton_T<T>::~Singleton_T()
{
	NMSP_ASSERT(s_instance == this);
	s_instance = nullptr;
}

template<class T> inline
void
Singleton_T<T>::init()
{
	NMSP_NEW(T)();
}

template<class T> inline
void
Singleton_T<T>::terminate()
{
	NMSP_DELETE(instance());
}

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
	NMSP_ASSERT(s_instance == this);
	s_instance = nullptr;
}


#endif

}