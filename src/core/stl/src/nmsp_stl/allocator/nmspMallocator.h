#pragma once

#include "nmspAllocator_Common.h"

namespace nmsp {

#if 0
#pragma mark --- Mallocator_T-Impl---
#endif // 0
#if 1

class Mallocator_T : public Allocator_Base<Mallocator_T>
{
public:
	using Base = Allocator_Base<Mallocator_T>;
	using SizeType = size_t;

	static constexpr SizeType s_kAlign = StlTraits::s_kDefaultAlign;

	Mallocator_T(const char* name = "Mallocator_T") : Base(name) {};
	~Mallocator_T() = default;

	void* alloc(SizeType n, SizeType align = s_kAlign, SizeType offset = 0)
	{
		void* p = NMSP_ALLOC_ALIGNED(n, align);
		return p;
	}

	void free(void* p, size_t n = 0)
	{
		NMSP_FREE_ALIGNED(p);
	}

	//void freeAll() { _offset = _storage; }
	bool is_owning(void* p, SizeType size) const { return true; }
};



#endif

}


