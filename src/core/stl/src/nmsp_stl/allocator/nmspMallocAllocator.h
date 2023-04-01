#pragma once

#include "nmspAllocator_Common.h"

namespace nmsp {

#if 0
#pragma mark --- MallocAllocator-Decl ---
#endif // 0
#if 1


template<size_t ALIGN = s_kDefaultAlign>
class MallocAllocator_T
{
public:
	using SizeType = size_t;

	static constexpr SizeType s_kAlign = ALIGN;

	void* alloc(SizeType n, SizeType align = s_kAlign, SizeType offset = 0)
	{
		intptr_t new_n = _alignTo(n, s_kAlign);
		return new u8[new_n];
	}

	void free(void* p, size_t n)
	{
		delete[] p;
	}

	//void freeAll() { _offset = _storage; }
	bool is_owning(void* p, SizeType size) const { return true; }
};

using MallocAllocator = MallocAllocator_T<s_kDefaultAlign>;

#endif

}

