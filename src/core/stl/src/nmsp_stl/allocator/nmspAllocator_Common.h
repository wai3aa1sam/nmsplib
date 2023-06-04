#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include "nmspAllocator_Base.h"

namespace nmsp {


#if 0
#pragma mark --- DefaultAllocator-Decl ---
#endif // 0
#if 1

class DefaultAllocator : public Allocator_Base<DefaultAllocator>
{
public:
	using Base = Allocator_Base<DefaultAllocator>;

public:
	DefaultAllocator(const char* name = "nmspDefaultAllocator");
	~DefaultAllocator()	= default;

	void*	alloc(SizeType n, SizeType align = StlTraits::s_kDefaultAlign, SizeType offset = 0);
	void	free(void* p, SizeType n = 0);

	bool is_owning(void* p, SizeType n);

private:

};

#endif


#if 0
#pragma mark --- DefaultAllocator-Decl ---
#endif // 0
#if 1

inline
DefaultAllocator::DefaultAllocator(const char* name)
	: Base(name)
{

}

inline void*	
DefaultAllocator::alloc(SizeType n, SizeType align, SizeType offset)
{
	return NMSP_ALLOC_ALIGNED(n, align);
}

inline void		
DefaultAllocator::free(void* p, SizeType n)
{
	NMSP_FREE_ALIGNED(p, n);
}

inline bool 
DefaultAllocator::is_owning(void* p, SizeType n)
{
	_notYetSupported();
	return false;
}

#endif

}