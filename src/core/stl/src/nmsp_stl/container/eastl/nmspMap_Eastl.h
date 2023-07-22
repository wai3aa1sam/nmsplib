#pragma once

#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

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

