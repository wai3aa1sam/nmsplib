#include "nmsp_core_base-pch.h"

#include "nmspAllocation.h"

#if NMSP_CUSTOM_ALLOC
NmspAllocationCallback  _nmspAllocationCallback;
namespace nmsp
{
void*	
nmsp_alloc(size_t size, size_t align /*= nmsp::CoreBaseTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
{
	return _nmspAllocationCallback.allocCallback(size, align, offset);
}

void	
nmsp_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
{
	_nmspAllocationCallback.freeCallback(p, size);
}
}
#endif // NMSP_CUSTOM_ALLOC

#if NMSP_OVERRIDE_NEW_OP

//void*	operator new  (size_t size)
//{
//	void* p = NMSP_ALLOC(p, size);
//	return p;
//}
//
//void*	operator new[](size_t size)
//{
//	void* p = NMSP_ALLOC(p, size);
//	return p;
//}
//
//void*	operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
//{
//	void* p = NMSP_ALLOC(p, size);
//	return p;
//}
//
//void*	operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
//{
//	void* p = NMSP_ALLOC(p, size, alignment, alignmentOffset);
//	return p;
//}
//
//void	operator delete  (void* ptr)					NMSP_NOEXCEPT
//{
//	NMSP_FREE(ptr);
//}
//
//void	operator delete  (void* ptr, std::size_t size)	NMSP_NOEXCEPT
//{
//	NMSP_FREE(ptr, size);
//}
//
//void	operator delete[](void* ptr)					NMSP_NOEXCEPT
//{
//	NMSP_FREE(ptr);
//}
//
//void	operator delete[](void* ptr, std::size_t size)	NMSP_NOEXCEPT
//{
//	NMSP_FREE(ptr, size);
//}

#endif