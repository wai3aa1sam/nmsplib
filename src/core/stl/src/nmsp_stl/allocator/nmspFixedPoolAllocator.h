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

inline
FixedPoolAllocator_T::FixedPoolAllocator_T(const char* name)
	: Base(name)
{

}

inline void* 
FixedPoolAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	return Mallocator_T::alloc(n, align);
}

inline void  
FixedPoolAllocator_T::free(void* p, SizeType n)
{
	Mallocator_T::free(p);
}


#endif

}