#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

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

