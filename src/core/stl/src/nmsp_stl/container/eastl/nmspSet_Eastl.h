#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/set.h>

namespace nmsp {

#if 0
#pragma mark --- Set_Eastl-Decl ---
#endif // 0
#if 0

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>
class Set_Eastl : public ::eastl::set<KEY, PRED, ALLOC>
{
public:
	Set_Eastl() = default;
	~Set_Eastl() = default;

private:

};

#else

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Set_Eastl = ::eastl::set<KEY, PRED, ALLOC>;


#endif

}