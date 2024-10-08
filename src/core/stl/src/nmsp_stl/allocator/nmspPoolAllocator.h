#pragma once

#include "nmsp_stl/allocator/nmspAllocator_Common.h"

namespace nmsp {


#if 0
#pragma mark --- PoolAllocator_T-Decl ---
#endif // 0
#if 1

class PoolAllocator_T : public Allocator_Base<PoolAllocator_T>
{
public:
	using Base = Allocator_Base<PoolAllocator_T>;

public:
	PoolAllocator_T(const char* name = "PoolAllocator_T");
	~PoolAllocator_T() = default;

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign, SizeType offset = 0);
	void  free(void* p, SizeType n = 0);

private:

};

#endif



#if 0
#pragma mark --- PoolAllocator_T-Decl ---
#endif // 0
#if 1

inline
PoolAllocator_T::PoolAllocator_T(const char* name)
	: Base(name)
{

}

inline void* 
PoolAllocator_T::alloc(SizeType n, SizeType align, SizeType offset)
{
	return Mallocator_T::alloc(n, align, offset);
}

inline void  
PoolAllocator_T::free(void* p, SizeType n)
{
	Mallocator_T::free(p, n);
}


#endif

}