#pragma once

#include "../nmspContainer_Common.h"

NMSP_DISABLE_ALL_WARNINGS()
#include <EASTL/unordered_map.h>
NMSP_RESTORE_ALL_WARNINGS()

namespace nmsp {

#if 0
#pragma mark --- UnorderedMap_Eastl-Decl ---
#endif // 0
#if 0

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator>
class UnorderedMap_Eastl : public eastl::unordered_map<KEY, VALUE, HASH, PRED, ALLOC>
{
public:
	UnorderedMap_Eastl() = default;
	~UnorderedMap_Eastl() = default;

private:

};

#else

template<class KEY, class VALUE, class HASH = Hash<KEY>, class PRED = EqualTo<KEY>, class ALLOC = DefaultAllocator> 
using UnorderedMap_Eastl = eastl::unordered_map<KEY, VALUE, HASH, PRED, ALLOC>;

#endif

}

