#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmsp_stl/atomic/base/nmspNativeThread_Base.h"

#if NMSP_OS_WINDOWS

namespace nmsp {

#if 0
#pragma mark --- NativeThread_Win32-Decl ---
#endif // 0
#if 1

class NativeThread_Win32 : public NativeThread_Base
{
public:
	using Base = NativeThread_Base;
	using This = NativeThread_Win32;

public:
	using Base::CreateDesc;
public:
	//NativeThread_Win32()	= default;
	virtual ~NativeThread_Win32();

	void create(const CreateDesc& cd);

	//void destroy();

	void		join			();
	void		setAffinity		(int k_th_bit);
	size_t		threadId		();
	ThreadHnd	nativeHnd		();


protected:
	static DWORD WINAPI _routine(void* args);
	static DWORD WINAPI _basicRoutine(void* basicCreateDesc);


protected:
	ThreadHnd	_hnd	  = nullptr;
	size_t		_threadId = ~size_t(0);
};

#endif

#if 0
#pragma mark --- NativeThread_Win32-Impl ---
#endif // 0
#if 1


#endif


}
#else
	#error "platform is not window"
#endif // NMSP_OS_WINDOWS


