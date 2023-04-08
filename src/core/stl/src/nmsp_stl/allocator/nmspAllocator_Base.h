#pragma once

#include "eastl/nmspAllocatorBase_Eastl.h"

namespace nmsp {


#if 0
#pragma mark --- AllocatorBase_Nmsp-Decl ---
#endif // 0
#if 1

template<class ALLOC>
class AllocatorBase_Nmsp
{
public:
	using This = AllocatorBase_Nmsp<ALLOC>;
public:
	using SizeType = size_t;

public:
	AllocatorBase_Nmsp(const char* name = "AllocatorBase_Nmsp");
	~AllocatorBase_Nmsp()	= default;

	void* alloc(SizeType n, SizeType align = NmspTraits::s_kDefaultAlign, SizeType offset = 0);
	void* alloc_all(SizeType n);

	void free(void* p, SizeType n = 0);
	void free_all();

	bool is_owning(void* p, SizeType n);

	bool operator==(const AllocatorBase_Nmsp& rhs);
	bool operator!=(const AllocatorBase_Nmsp& rhs);
private:
};

#endif

#if 0
#pragma mark --- AllocatorBase_Nmsp-Impl ---
#endif // 0
#if 1

template<class ALLOC> inline
AllocatorBase_Nmsp<ALLOC>::AllocatorBase_Nmsp(const char* name)
{

}

template<class ALLOC> inline
void*	AllocatorBase_Nmsp<ALLOC>::alloc(SizeType n, SizeType align, SizeType offset)
{
	return static_cast<ALLOC&>(*this).alloc(n, align, offset);
}

template<class ALLOC> inline
void*	AllocatorBase_Nmsp<ALLOC>::alloc_all(SizeType n)
{
	return static_cast<ALLOC&>(*this).alloc_all(n);
}

template<class ALLOC> inline
void	AllocatorBase_Nmsp<ALLOC>::free(void* p, SizeType n)
{
	static_cast<ALLOC&>(*this).free(p, n);
}

template<class ALLOC> inline
void	AllocatorBase_Nmsp<ALLOC>::free_all()
{
	static_cast<ALLOC&>(*this).free_all();
}

template<class ALLOC> inline
bool	AllocatorBase_Nmsp<ALLOC>::is_owning(void* p, SizeType n)
{
	static_cast<ALLOC&>(*this).is_owning(p, n);
}

template<class ALLOC> inline
bool	AllocatorBase_Nmsp<ALLOC>::operator==(const AllocatorBase_Nmsp& rhs)
{
	return static_cast<ALLOC&>(*this) == static_cast<ALLOC&>(rhs)
}

template<class ALLOC> inline
bool	AllocatorBase_Nmsp<ALLOC>::operator!=(const AllocatorBase_Nmsp& rhs)
{
	return !static_cast<ALLOC&>(*this).operator==(rhs);
}

#endif

#if NMSP_BUILD_STL_EASTL_CONTAINER
	template<class ALLOC> using AllocatorBase_Impl	= AllocatorBase_Eastl< AllocatorBase_Nmsp<ALLOC> >;
#elif NMSP_BUILD_STL_NMSP_CONTAINER
	template<class ALLOC> using AllocatorBase_Impl	= AllocatorBase_Nmsp<ALLOC>;
#else
	#error "unspported stl build marco"
#endif // NMSP_BUILD_STL_EASTL_CONTAINER

template<class ALLOC> using Allocator_Base	= AllocatorBase_Impl<ALLOC>;

template<size_t ALIGN> class MallocAllocator_T;
using DefaultAllocator						= MallocAllocator_T<8>;

}