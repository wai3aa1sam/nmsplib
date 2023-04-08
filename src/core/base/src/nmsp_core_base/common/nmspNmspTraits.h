#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

#include "nmsp_core_base/marco/nmsp_core_base_internal_marco.h"

#include <new>

namespace nmsp {


template<class T>
static constexpr T _alignTo(T n, T a) 
{
	static_assert(IsUInt<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
}

#if 0
#pragma mark --- nmspNmspTrait-Impl ---
#endif // 0
#if 1


struct NmspDefaultTraits_T
{
	static constexpr size_t s_kCahchLineSize	= std::hardware_destructive_interference_size;
	static constexpr size_t s_kDefaultAlign		= NMSP_ALIGN_OF(std::max_align_t);


};

#if !NMSP_CUSTOM_TRAITS

using NmspTraits = NmspDefaultTraits_T;

#else


#endif // 

#if !NMSP_CUSTOM_ALLOC

inline void* nmsp_alloc(size_t size, size_t align = NmspTraits::s_kDefaultAlign, size_t offset = 0)			noexcept 
{
	auto alignSize	= _alignTo(size, align);
	auto* p			= std::malloc(alignSize);
	_NMSP_PROFILE_ALLOC(p, alignSize);
	return p; 
}

inline void	 nmsp_free(void* p, size_t size = 0)	noexcept 
{ 
	_NMSP_PROFILE_FREE(p, size)	
	delete[] p;
}

#else


#endif // !1

#define NMSP_ALLOC(ptr, size, ...)	::nmsp::nmsp_alloc(size, __VA_ARGS__)
#define NMSP_FREE(ptr, ...)			::nmsp::nmsp_free(ptr, __VA_ARGS__)

template<class T> inline T*		nmsp_new()			noexcept { return static_cast<T*>(nmsp_alloc(sizeof(T), NMSP_ALIGN_OF(T))); }
template<class T> inline void	nmsp_delete(T* p)	noexcept { nmsp_free(p); }

#endif

}

#if NMSP_OVERRIDE_NEW_OP

void*	operator new  (size_t size);
void*	operator new[](size_t size);
void*	operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void*	operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void	operator delete  (void* ptr)					noexcept;
void	operator delete  (void* ptr, std::size_t size)	noexcept;
void	operator delete[](void* ptr)					noexcept;
void	operator delete[](void* ptr, std::size_t size)	noexcept;


#endif // NMSP_OVERRIDE_NEW


