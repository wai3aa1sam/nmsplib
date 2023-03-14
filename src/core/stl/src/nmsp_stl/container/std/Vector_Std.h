#pragma once

#include "../nmspContainer_Common.h"

namespace nmsp {

#if 0
#pragma mark --- Vector_Std-Decl
#endif // 0
#if 1

template<class T, class ALLOCATOR = DefaultAllocator>
class Vector_Std : public std::vector<T /*, ALLOCATOR*/>
{
public:
	Vector_Std()
	{
		_NMSP_LOG("Vector_Std() {}, {}", 1, "hellowrld");
	}
private:

};

#endif

}