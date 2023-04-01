#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/vector_map.h>

namespace nmsp {

#if 0
#pragma mark --- VectorMap_Eastl-Decl ---
#endif // 0
#if 0

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>
class VectorMap_Eastl : public ::eastl::vector_map<KEY, VALUE, PRED, ALLOC>
{
public:
	VectorMap_Eastl() = default;
	~VectorMap_Eastl() = default;

private:

};

#else

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using VectorMap_Eastl = ::eastl::vector_map<KEY, VALUE, PRED, ALLOC>;

#endif

}

