#include "nmsp_core_base-pch.h"

#include "nmspAlloc_Common.h"

namespace nmsp {

#if 0
#pragma mark --- nmspNmspAlloc-Impl ---
#endif // 0
#if 1

#if !NMSP_CUSTOM_ALLOC

	void* nmsp_alloc(size_t size, size_t align /*= nmsp::NmspTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
	{
		auto alignSize	= nmsp::_alignTo(size, align);
		auto* p			= std::malloc(alignSize);
		_NMSP_PROFILE_ALLOC(p, alignSize);
		return p; 
	}

	void  nmsp_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
	{ 
		_NMSP_PROFILE_FREE(p, size);
		std::free(p);
	}

#endif

#endif
}

#if NMSP_OVERRIDE_NEW_OP

void*	operator new  (size_t size)
{
	void* p = NMSP_ALLOC(p, size);
	return p;
}

void*	operator new[](size_t size)
{
	void* p = NMSP_ALLOC(p, size);
	return p;
}

void*	operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	void* p = NMSP_ALLOC(p, size);
	return p;
}

void*	operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	void* p = NMSP_ALLOC(p, size, alignment, alignmentOffset);
	return p;
}

void	operator delete  (void* ptr)					NMSP_NOEXCEPT
{
	NMSP_FREE(ptr);
}

void	operator delete  (void* ptr, std::size_t size)	NMSP_NOEXCEPT
{
	NMSP_FREE(ptr, size);
}

void	operator delete[](void* ptr)					NMSP_NOEXCEPT
{
	NMSP_FREE(ptr);
}

void	operator delete[](void* ptr, std::size_t size)	NMSP_NOEXCEPT
{
	NMSP_FREE(ptr, size);
}

#endif