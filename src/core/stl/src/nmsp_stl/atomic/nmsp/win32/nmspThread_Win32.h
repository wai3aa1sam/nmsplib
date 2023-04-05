#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

#include "nmsp_stl/atomic/base/nmspThread_Base.h"

#if NMSP_OS_WINDOWS


#if 0
#pragma mark --- Thread_Win32-Decl ---
#endif // 0
#if 1
namespace nmsp {

class Thread_Win32 : public Thread_Base
{
public:
	using Base = Thread_Base;
	using This = Thread_Win32;

public:
	using Base::CreateDesc;
public:
	Thread_Win32()	= default;
	~Thread_Win32() = default;

	void create(const CreateDesc& cd);
	void destroy();

private:

};

}
#endif




#else
	#error "platform is not window"
#endif // NMSP_OS_WINDOWS


