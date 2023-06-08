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

	void create();
	void destroy();

protected:
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

public:
	Singleton_T();
	~Singleton_T();

	void create(T* p);
	void destroy();

protected:
	static T* s_instance;

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
#pragma mark --- Singleton_T-Impl ---
#endif // 0
#if 1

template<class T> inline
T* 
Singleton_T<T>::instance()
{
	return s_instance;
}

template<class T> inline
Singleton_T<T>::Singleton_T()
{
}

template<class T> inline
Singleton_T<T>::~Singleton_T()
{
}



template<class T> inline
void
Singleton_T<T>::create(T* p)
{
	NMSP_ASSERT(!s_instance);
	s_instance = p;
}

template<class T> inline
void
Singleton_T<T>::destroy()
{
	NMSP_ASSERT(s_instance);
	s_instance = nullptr;
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
	create();
}

template<class T> inline
StackSingleton_T<T>::~StackSingleton_T()
{
	NMSP_ASSERT(!s_instance);
	//destroy();
}

template<class T> inline
void 
StackSingleton_T<T>::create()
{
	NMSP_ASSERT(!s_instance);
	s_instance = sCast<T*>(this);
}

template<class T> inline
void 
StackSingleton_T<T>::destroy()
{
	//NMSP_ASSERT(s_instance);
	s_instance = nullptr;
}


#endif

}