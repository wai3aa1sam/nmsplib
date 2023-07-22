#pragma once

#include "../nmspContainer_Common.h"

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

#if 0
#pragma mark --- List_Eastl-Decl ---
#endif // 0
#if 0

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>
class List_Eastl : public eastl::set<KEY, PRED, ALLOC>
{
public:
	List_Eastl() = default;
	~List_Eastl() = default;

private:

};

#else

template<class T, size_t N = 0, class FALLBACK_ALLOC = DefaultAllocator>	using List_Eastl	= eastl::list<T, FALLBACK_ALLOC>;

#endif

}