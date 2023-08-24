#pragma once

#include "nmspAlloc_Common.h"

#if 0
#pragma mark --- nmspNmspAllocMarco-Impl ---
#endif // 0
#if 1

#define NMSP_ALLOC_ALIGNED(N, ALIGN)	::nmsp::nmsp_alloc(N, ALIGN)
#define NMSP_FREE_ALIGNED(PTR, ...)		::nmsp::nmsp_free(PTR, __VA_ARGS__)

#define NMSP_ALLOC(N)			NMSP_ALLOC_ALIGNED(N, ::nmsp::CoreBaseTraits::s_kDefaultAlign)
#define NMSP_FREE(PTR, ...)		NMSP_FREE_ALIGNED(PTR, __VA_ARGS__)

#define NMSP_NEW(T)				new(NMSP_ALLOC_ALIGNED(sizeof(T), NMSP_ALIGN_OF(T))) T
#define NMSP_DELETE(PTR)		::nmsp::nmsp_delete(PTR)


using nmspAllocCallback = void* (*)(size_t n, size_t align, size_t offset);
using nmspFreeCallback	= void  (*)(void* p, size_t n);
struct NmspAllocationCallback
{
	nmspAllocCallback	allocCallback;
	nmspFreeCallback	freeCallback;
};
extern NmspAllocationCallback _nmspAllocationCallback;

#endif

#if 0
#pragma mark --- nmspNmspAlloc-Impl ---
#endif // 0
#if 1

namespace nmsp 
{

void* nmsp_alloc(size_t size, size_t align = nmsp::CoreBaseTraits::s_kDefaultAlign, size_t offset = 0)		NMSP_NOEXCEPT;
void  nmsp_free	(void* p, size_t size = 0)																	NMSP_NOEXCEPT;

#if !NMSP_CUSTOM_ALLOC

inline void* 
nmsp_alloc(size_t size, size_t align /*= nmsp::CoreBaseTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
{
	auto* p = nmsp::os_aligned_alloc(size, align);
	_NMSP_PROFILE_ALLOC(p, nmsp::_alignTo(size, align));
	return p;
}

inline void  
nmsp_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
{
	_NMSP_PROFILE_FREE(p, size);
	nmsp::os_aligned_free(p);
}

#endif

template<class T> inline 
void
nmsp_delete(T* p)	NMSP_NOEXCEPT 
{ 
	p->~T();
	nmsp_free(p); 
}

}
#endif

#if 0

namespace nmsp {

//
//template<class ALLOC> void* nmsp_alloc	(ALLOC& alloc, size_t size, size_t align = nmsp::CoreBaseTraits::s_kDefaultAlign, size_t offset = 0)		NMSP_NOEXCEPT;
//template<class ALLOC> void  nmsp_free	(ALLOC& alloc, void* p, size_t size = 0)																	NMSP_NOEXCEPT;
//
//template<class ALLOC> void* nmsp_os_alloc (ALLOC& alloc, size_t size, size_t align = nmsp::CoreBaseTraits::s_kDefaultAlign, size_t offset = 0)		NMSP_NOEXCEPT;
//template<class ALLOC> void  nmsp_os_free  (ALLOC& alloc, void* p, size_t size = 0)																	NMSP_NOEXCEPT;
//
//template<class ALLOC> void* nmsp_alloc	(ALLOC& alloc, size_t size, size_t align, size_t offset, const AllocStats_Base& stats)		NMSP_NOEXCEPT;
//template<class ALLOC> void  nmsp_free	(ALLOC& alloc, void* p, size_t size, const AllocStats_Base& stats)							NMSP_NOEXCEPT;
//
//template<class ALLOC> void* nmsp_os_alloc (ALLOC& alloc, size_t size, size_t align, size_t offset, const AllocStats_Base& stats)	NMSP_NOEXCEPT;
//template<class ALLOC> void  nmsp_os_free  (ALLOC& alloc, void* p, size_t size, const AllocStats_Base& stats)						NMSP_NOEXCEPT;


//template<class T, class... ARGS> inline 
//T*
//nmsp_new(AllocStats_Base stats, ARGS&&... args)	NMSP_NOEXCEPT 
//{
//	T* p = nullptr;
//	{
//		_Internal_ScopedTimer t;
//		p = nmsp_new(nmsp::forward<ARGS>(args)...));
//		stats.setTime(t.get<double>());
//	}
//	return p;
//}
//
//template<class T> inline 
//void
//nmsp_delete(AllocStats_Base stats, T* p, size_t n = 0)	NMSP_NOEXCEPT 
//{ 
//	p->~T();
//	{
//		_Internal_ScopedTimer t;
//		os_aligned_free(p); 
//		stats.setTime(t.get<double>());
//	}
//}

}

//
//#if NMSP_OVERRIDE_NEW_OP
//
//NMSP_NODISCARD void*	operator new  (size_t size);
//NMSP_NODISCARD void*	operator new[](size_t size);
//NMSP_NODISCARD void*	operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
//NMSP_NODISCARD void*	operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
//
//void	operator delete  (void* ptr)					NMSP_NOEXCEPT;
//void	operator delete  (void* ptr, std::size_t size)	NMSP_NOEXCEPT;
//void	operator delete[](void* ptr)					NMSP_NOEXCEPT;
//void	operator delete[](void* ptr, std::size_t size)	NMSP_NOEXCEPT;
//
//#endif // NMSP_OVERRIDE_NEW

namespace nmsp {

#if 0
#pragma mark --- nmspNmspAlloc-Impl ---
#endif // 0
#if 1

//#if !NMSP_CUSTOM_ALLOC
//
//inline void* 
//nmsp_alloc(size_t size, size_t align /*= nmsp::CoreBaseTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
//{
//	auto* p = nmsp::os_aligned_alloc(align, size);
//	_NMSP_PROFILE_ALLOC(p, nmsp::_alignTo(size, align));
//	return p;
//}
//
//inline void  
//nmsp_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
//{
//	_NMSP_PROFILE_FREE(p, size);
//	nmsp::os_aligned_free(p, size);
//}
//
//inline void* 
//nmsp_os_alloc(size_t size, size_t align /*= nmsp::CoreBaseTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
//{
//	auto* p = nmsp::os_aligned_alloc(align, size);
//	_NMSP_PROFILE_ALLOC(p, nmsp::_alignTo(size, align));
//	return p;
//}
//
//inline void  
//nmsp_os_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
//{
//	_NMSP_PROFILE_FREE(p, size);
//	nmsp::os_aligned_free(p, size);
//}
//
//
//#endif

#endif
}


//#if NMSP_ENABLE_ALLOC_STATS
//
//#define NMSP_NEW(T, ...)				::nmsp::nmsp_new<T>(AllocStats_Base{NMSP_SRCLOC}, __VA_ARGS__)
//#define NMSP_DELETE(PTR, ...)			::nmsp::nmsp_delete(AllocStats_Base{NMSP_SRCLOC}, PTR, 0)
//
//#else
//
//
//#endif // 1


//#if !NMSP_CUSTOM_ALLOC
//
//#define NMSP_NEW(T, ...)				new () T
//#define NMSP_DELETE(PTR, ...)			::nmsp::nmsp_delete(PTR)
//
//#define NMSP_NEW_T(T, ALLOC, ...)		::nmsp::nmsp_new<T>(__VA_ARGS__)
//#define NMSP_DELETE_T(PTR, ALLOC, ...)	::nmsp::nmsp_delete(PTR)
//
//#define NMSP_ALLOC(PTR, SIZE, ...)		::nmsp::sCast<decltype(PTR)>(::nmsp::nmsp_alloc(SIZE, __VA_ARGS__)); NMSP_ASSERT(PTR != nullptr)											
//#define NMSP_FREE(PTR, ...)				do{ ::nmsp::nmsp_free(PTR, __VA_ARGS__); } while(false)
//
//#endif // 0
//

#endif // 0
