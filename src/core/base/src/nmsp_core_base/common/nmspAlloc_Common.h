#pragma once

#include "nmsp_core_base/common/nmsp_core_base_traits.h"

#include "nmspTypeTraits_Common.h"

#include <new>

#if 0
#pragma mark --- nmspNmspAlloc-Impl ---
#endif // 0
#if 1

namespace nmsp {

void* nmsp_alloc(size_t size, size_t align = nmsp::CoreBaseTraits::s_kDefaultAlign, size_t offset = 0)		NMSP_NOEXCEPT;
void  nmsp_free	(void* p, size_t size = 0)																	NMSP_NOEXCEPT;

template<class T, class... ARGS> inline 
T* nmsp_new(ARGS&&... args)	NMSP_NOEXCEPT 
{ 
	auto* p = static_cast<T*>(nmsp_alloc(sizeof(T), NMSP_ALIGN_OF(T)));  
	new (p) T(nmsp::forward<ARGS>(args)...);
	return p; 
}
template<class T> inline void	nmsp_delete(T* p)	NMSP_NOEXCEPT 
{ 
	p->~T();
	nmsp_free(p); 
}

}

#if 0
#define NMSP_NEW_1(ptr, ...)			::nmsp::nmsp_new<::nmsp::RemovePtr<decltype(ptr)> >(); NMSP_ASSERT(ptr != nullptr)
//#define NMSP_NEW_2(ptr, count, ...)	::nmsp::sCast<decltype(ptr)>(::nmsp::nmsp_alloc(sizeof( ::nmsp::RemovePtr<decltype(ptr)> ) * count, __VA_ARGS__) )	; ; NMSP_ASSERT(ptr != nullptr)
//#define NMSP_NEW_3(ptr, count, ...)	::nmsp::sCast<decltype(ptr)>(::nmsp::nmsp_alloc(sizeof( ::nmsp::RemovePtr<decltype(ptr)> ) * count, __VA_ARGS__) )	; ; NMSP_ASSERT(ptr != nullptr)
//#define NMSP_NEW_4(ptr, count, ...)	::nmsp::sCast<decltype(ptr)>(::nmsp::nmsp_alloc(sizeof( ::nmsp::RemovePtr<decltype(ptr)> ) * count, __VA_ARGS__) )	; ; NMSP_ASSERT(ptr != nullptr)

#define NMSP_NEW_SELECT(COUNT) NMSP_NEW_##COUNT
//#define NMSP_NEW(...) NMSP_IDENTITY(NMSP_CALL(NMSP_NEW_SELECT, NMSP_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))

#endif // 0

#define NMSP_NEW(T, PTR, ...)	::nmsp::nmsp_new<T>(__VA_ARGS__)
#define NMSP_DELETE(PTR, ...)	::nmsp::nmsp_delete(PTR)

#define NMSP_ALLOC(PTR, SIZE, ...)		::nmsp::sCast<decltype(PTR)>(::nmsp::nmsp_alloc(SIZE, __VA_ARGS__)); NMSP_ASSERT(PTR != nullptr)											
#define NMSP_FREE(PTR, ...)				do{ ::nmsp::nmsp_free(PTR, __VA_ARGS__); } while(false)

#endif

#if NMSP_OVERRIDE_NEW_OP

NMSP_NODISCARD void*	operator new  (size_t size);
NMSP_NODISCARD void*	operator new[](size_t size);
NMSP_NODISCARD void*	operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
NMSP_NODISCARD void*	operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void	operator delete  (void* ptr)					NMSP_NOEXCEPT;
void	operator delete  (void* ptr, std::size_t size)	NMSP_NOEXCEPT;
void	operator delete[](void* ptr)					NMSP_NOEXCEPT;
void	operator delete[](void* ptr, std::size_t size)	NMSP_NOEXCEPT;


#endif // NMSP_OVERRIDE_NEW




namespace nmsp {

#if 0
#pragma mark --- nmspNmspAlloc-Impl ---
#endif // 0
#if 1

#if !NMSP_CUSTOM_ALLOC

inline 
void* nmsp_alloc(size_t size, size_t align /*= nmsp::CoreBaseTraits::s_kDefaultAlign*/, size_t offset /*= 0*/) NMSP_NOEXCEPT
{
	auto alignSize	= nmsp::_alignTo(size, align);
	auto* p			= std::malloc(alignSize);
	_NMSP_PROFILE_ALLOC(p, alignSize);
	return p; 
}

inline
void  nmsp_free(void* p, size_t size /*= 0*/) NMSP_NOEXCEPT
{ 
	_NMSP_PROFILE_FREE(p, size);
	std::free(p);
}

#endif

#endif
}