#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

namespace nmsp {

#if 0
#pragma mark --- Set_Eastl-Decl ---
#endif // 0
#if 0

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>
class Set_Eastl : public eastl::set<KEY, PRED, ALLOC>
{
public:
	Set_Eastl() = default;
	~Set_Eastl() = default;

private:

};

#else

template<class KEY, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>								using Set_Eastl				= eastl::set<KEY, PRED, ALLOC>;
template<class KEY, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator>	using UnorderedSet_Eastl	= eastl::unordered_set<KEY, HASH, PRED, ALLOC>;


#endif

}