#pragma once

#include "nmspAllocator_Common.h"

namespace nmsp {

#if 0
#pragma mark --- MallocAllocator-Impl---
#endif // 0
#if 1

template<size_t ALIGN = NmspTraits::s_kDefaultAlign>
class MallocAllocator_T : public Allocator_Base<MallocAllocator_T<ALIGN> >
{
public:
	using SizeType = size_t;

	static constexpr SizeType s_kAlign = ALIGN;

	MallocAllocator_T(const char* name = "MallocAllocator_T") {};
	~MallocAllocator_T() = default;

	void* alloc(SizeType n, SizeType align = s_kAlign, SizeType offset = 0)
	{
		intptr_t new_n = _alignTo(n, s_kAlign);
		void* p = NMSP_ALLOC(p, new_n, align, offset);
		return p;
	}

	void free(void* p, size_t n = 0)
	{
		NMSP_FREE(p, n);
	}

	//void freeAll() { _offset = _storage; }
	bool is_owning(void* p, SizeType size) const { return true; }
};



#endif

}


