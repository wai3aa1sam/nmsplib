#include "nmsp_core_base-pch.h"
#include "nmspAllocation.h"

NmspAllocationCallback* _nmspAllocationCallback = nullptr;

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