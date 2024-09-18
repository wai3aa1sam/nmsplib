#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

namespace nmsp {

#if NMSP_OS_WINDOWS
using ThreadHnd = HANDLE;
#else
#error "unknow thread handle"
#endif

using ThreadProcedure = void* (*)(void*);

#if 0
#pragma mark --- NativeThread_Base_CreateDesc-Decl ---
#endif // 0
#if 1

struct BasicThread_CreateDesc
{
	StrViewA_T		name;
	int				affinityIdx = -1;
	int				localId		= -1;
	ThreadProcedure	procdure = nullptr;
	void* args = nullptr;
};

struct NativeThread_CreateDesc : public BasicThread_CreateDesc
{
	using Base = BasicThread_CreateDesc;
	using Base::name;
	using Base::affinityIdx;
	using Base::localId;
};

#endif

#if 0
#pragma mark --- NativeThread_Base-Decl ---
#endif // 0
#if 1

class Thread_Base : public NonCopyable
{
public:
	using CreateDesc_Base	= BasicThread_CreateDesc;
	using CreateDesc		= BasicThread_CreateDesc;

public:
	Thread_Base();
	~Thread_Base();

	void create(const CreateDesc& bcd);

	void		join();
	void		setAffinity(int k_th_bit);
	size_t		threadId();
	ThreadHnd	nativeHnd();

	int				localId()	const;
	int				affinity()	const;
	const StringT&	name()	const;

protected:
	int		_localId	= -1;
	int		_affinity	= -1;
	StringT _name;

	#if NMSP_DEBUG
	bool _isJoined : 1;
	#endif // NMSP_DEBUG
};

class NativeThread_Base : public Thread_Base
{
public:
	using Base = Thread_Base;

	using CreateDesc_Base	= Base::CreateDesc_Base;
	using CreateDesc		= NativeThread_CreateDesc;

public:
	NMSP_NODISCARD static CreateDesc makeCDesc();

public:
	NativeThread_Base();
	virtual ~NativeThread_Base() = default;

public:
	void	create(const CreateDesc_Base& cDescBase);
	void*	proceed();

protected:
	virtual void* onProceed() = 0;
};

#endif

#if 0
#pragma mark --- nmspThread_Base-Impl ---
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
void
Thread_Base::create(const CreateDesc_Base& bcd)
{
	_localId	= bcd.localId;
	_affinity	= bcd.affinityIdx;
	_name		= bcd.name;
}

inline
int
Thread_Base::localId() const
{
	return _localId;
}

inline
const StringT&
Thread_Base::name() const
{
	return _name;
}

#endif

#if 0
#pragma mark --- nmspNativeThread_Base-Impl ---
#endif // 0
#if 1

inline
NativeThread_Base::CreateDesc NativeThread_Base::makeCDesc()
{
	return NativeThread_Base::CreateDesc{};
}

inline
NativeThread_Base::NativeThread_Base()
	: Base()
{

}

inline
void 
NativeThread_Base::create(const CreateDesc_Base& cDescBase)
{
	auto cDesc = sCast<const CreateDesc&>(cDescBase);
	Base::create(cDesc);
}

inline
void* 
NativeThread_Base::proceed()
{
	void* ret = nullptr;
	ret = onProceed();
	return ret;
}

#endif

}
