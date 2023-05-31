#pragma once

#include "nmsp_stl/allocator/nmspAllocator_Common.h"

namespace nmsp {


#if 0
#pragma mark --- MemoryArena_T-Decl ---
#endif // 0
#if 1

template<class ALLOC, class BOUND_POLICY>
class MemoryArena_T : public ALLOC
{
public:
	using Base = ALLOC;
	using SizeType = StlTraits::SizeType;
	//using Base::SizeType;

public:
	MemoryArena_T(const char* name = "MemoryArena_T");

	~MemoryArena_T() = default;

	void* alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign, SizeType offset = 0);
	void  free(void* p, SizeType n = 0);

private:

};

#endif

#if 0
#pragma mark --- MemoryArena_T-Decl ---
#endif // 0
#if 1

template<class ALLOC, class BOUND_POLICY> inline
MemoryArena_T<ALLOC, BOUND_POLICY>::MemoryArena_T(const char* name)
	: Base(name)
{

}

template<class ALLOC, class BOUND_POLICY> inline
void* 
MemoryArena_T<ALLOC, BOUND_POLICY>::alloc(SizeType n, SizeType align, SizeType offset)
{
	return NMSP_ALLOC_ALIGNED(n, align);
}

template<class ALLOC, class BOUND_POLICY> inline
void  
MemoryArena_T<ALLOC, BOUND_POLICY>::free(void* p, SizeType n)
{
	NMSP_FREE_ALIGNED(p);
}


#endif

}