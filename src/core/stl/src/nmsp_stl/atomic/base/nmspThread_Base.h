#pragma once

#include "nmsp_stl/atomic/nmspAtomic_Common.h"

namespace nmsp {

#if 0
#pragma mark --- Thread_Base_CreateDesc-Decl ---
#endif // 0
#if 1

struct Thread_Base_CreateDesc
{

};

#endif

#if 0
#pragma mark --- Thread_Base-Decl ---
#endif // 0
#if 1

class Thread_Base : public NonCopyable
{
public:
	using CreateDesc = Thread_Base_CreateDesc;
public:
	Thread_Base()	= default;
	~Thread_Base()	= default;

	/*void create(const CreateDesc& cd);
	void destroy();*/

private:

};

#endif

}
