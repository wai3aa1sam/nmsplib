#pragma once

#include "../nmspContainer_Common.h"

#include <EASTL/string_map.h>

namespace nmsp {

#if 0
#pragma mark --- StringMap_Eastl-Decl ---
#endif // 0
#if 1

template<class VALUE, class PRED = StrLess<const char*>, class ALLOC = DefaultAllocator>
class StringMap_Eastl : public ::eastl::string_map<VALUE, PRED, ALLOC>
{
public:
	StringMap_Eastl() = default;
	~StringMap_Eastl() = default;

	template <class... Args>
	void emplace(Args&&... args) { static_assert(false, "shd not be called"); } // 

private:

};

#else

template<class VALUE, class PRED = StrLess<const char*>, class ALLOC = DefaultAllocator> using StringMap_Eastl = ::eastl::string_map<VALUE, PRED, ALLOC>;

#endif

}

