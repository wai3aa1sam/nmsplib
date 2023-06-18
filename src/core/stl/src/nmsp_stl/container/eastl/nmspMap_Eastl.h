#pragma once

#include "../nmspContainer_Common.h"

NMSP_DISABLE_ALL_WARNINGS()
#include <EASTL/map.h>
NMSP_RESTORE_ALL_WARNINGS()

namespace nmsp {

#if 0
#pragma mark --- Map_Eastl-Decl ---
#endif // 0
#if 0

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator>
class Map_Eastl : public eastl::map<KEY, VALUE, PRED, ALLOC>
{
public:
	Map_Eastl() = default;
	~Map_Eastl() = default;

private:

};

#else

template<class KEY, class VALUE, class PRED = Less<KEY>, class ALLOC = DefaultAllocator> using Map_Eastl = eastl::map<KEY, VALUE, PRED, ALLOC>;

#endif

}

