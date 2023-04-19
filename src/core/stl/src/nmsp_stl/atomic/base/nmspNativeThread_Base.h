#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmsp_stl/container/nmspString.h"

namespace nmsp {

#if NMSP_OS_WINDOWS
using ThreadHnd = HANDLE;
#else
#error "unknow thread handle"
#endif

using ThreadRountine = void* (*)(void*);

#if 0
#pragma mark --- NativeThread_Base_CreateDesc-Decl ---
#endif // 0
#if 1

struct BasicThread_CreateDesc
{
	StrViewA_T		name;
	int				affinityIdx = -1;
	ThreadRountine	routine = nullptr;
	void* args = nullptr;
};

struct NativeThread_CreateDesc : private BasicThread_CreateDesc
{
	using Base = BasicThread_CreateDesc;
	using Base::name;
	using Base::affinityIdx;
};

#endif

#if 0
#pragma mark --- NativeThread_Base-Decl ---
#endif // 0
#if 1

class Thread_Base : public NonCopyable
{
public:
	using BasicCreateDesc = BasicThread_CreateDesc;
	using CreateDesc = NativeThread_CreateDesc;
public:
	Thread_Base();
	~Thread_Base();

	void create(const BasicCreateDesc& bcd);

	void		join();
	void		setAffinity(int k_th_bit);
	size_t		threadId();
	ThreadHnd	nativeHnd();

	int			localId()	const;
	StrViewA_T	name()	const;


protected:
	int		_localId = -1;
	StringT _name;

	#if NMSP_DEBUG
	bool _isJoined : 1;
	#endif // NMSP_DEBUG
};

class NativeThread_Base : public Thread_Base
{
	using Base = Thread_Base;
public:
	using BasicCreateDesc = BasicThread_CreateDesc;
	using CreateDesc = NativeThread_CreateDesc;
public:
	NativeThread_Base();
	virtual ~NativeThread_Base() = default;

	NMSP_NODISCARD static CreateDesc makeCD();

	void create(const CreateDesc& bcd);

	virtual void* onRoutine() = 0;

};

#endif

#if 0
#pragma mark --- NativeThread_Base-Impl ---
#endif // 0
#if 1

inline
Thread_Base::Thread_Base()
{
	#if NMSP_DEBUG
	_isJoined = true;
	#endif // NMSP_DEBUG
}

inline
Thread_Base::~Thread_Base()
{
	#if NMSP_DEBUG
	NMSP_ASSERT(_isJoined, "must call join() on derived class, also should be awaked");
	#endif // NMSP_DEBUG
}

inline
void			Thread_Base::create(const BasicCreateDesc& bcd)
{
	_localId = bcd.affinityIdx;
	_name = bcd.name;
}

inline
int			Thread_Base::localId() const
{
	return _localId;
}

inline
StrViewA_T	Thread_Base::name() const
{
	return _name;
}

inline
NativeThread_Base::NativeThread_Base()
	: Base()
{

}

inline
void NativeThread_Base::create(const CreateDesc& cd)
{
	Base::create((const BasicCreateDesc&)cd);
}

inline
NativeThread_Base::CreateDesc NativeThread_Base::makeCD()
{
	return NativeThread_Base::CreateDesc{};
}


#endif

}