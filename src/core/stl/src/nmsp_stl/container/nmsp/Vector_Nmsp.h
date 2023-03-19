#pragma once

#include "../nmspContainer_Common.h"

namespace nmsp {

#if 0
#pragma mark --- VectorBase_Nmsp-Decl
#endif // 0
#if 1

template<class T, size_t N, class ALLOCATOR = DefaultAllocator>
class VectorBase_Nmsp
{
public:
	VectorBase_Nmsp()
	{
	}
private:

};


template<class T, size_t N, class ALLOCATOR = DefaultAllocator> using Vector_Nmsp = VectorBase_Nmsp<T, N, ALLOCATOR>;

#endif


}