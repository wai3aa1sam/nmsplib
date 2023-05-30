#pragma once

#include "nmsp_stl/allocator/nmspAllocator_Common.h"

namespace nmsp {


#if 0
#pragma mark --- FixedPoolAllocator_T-Decl ---
#endif // 0
#if 1

class FixedPoolAllocator_T : public Allocator_Base<FixedPoolAllocator_T>
{
public:
	using Base = Allocator_Base<FixedPoolAllocator_T>;

public:
	FixedPoolAllocator_T(const char* name = "FixedPoolAllocator_T");

	~FixedPoolAllocator_T() = default;

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign, SizeType offset = 0);
	void  free(void* p, SizeType n = 0);

private:

};

#endif

#if 0
#pragma mark --- FixedPoolAllocator_T-Decl ---
#endif // 0
#if 1

FixedPoolAllocator_T::FixedPoolAllocator_T(const char* name)
	: Base(name)
{

}

void* 
FixedPoolAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	return NMSP_ALLOC_ALIGNED(n, align);
}

void  
FixedPoolAllocator_T::free(void* p, SizeType n)
{
	NMSP_FREE_ALIGNED(p);
}


#endif

}