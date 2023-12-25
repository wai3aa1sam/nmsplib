#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include "nmspInclude_Common.h"
#include "nmspTypeTraits_Common.h"

namespace nmsp 
{

#if 0
#pragma mark --- nmspCast-Impl ---
#endif // 0
#if 1

template<class DST, class SRC> constexpr 	   DST sCast(	   SRC* v)	{ return static_cast<	   DST>(v); }
template<class DST, class SRC> constexpr 	   DST sCast(	   SRC& v)	{ return static_cast<	   DST>(v); }
template<class DST, class SRC> constexpr const DST sCast(const SRC* v)	{ return static_cast<const DST>(v); }
template<class DST, class SRC> constexpr const DST sCast(const SRC& v)	{ return static_cast<const DST>(v); }

template<class DST, class SRC> constexpr 	   DST reinCast(	  SRC* v)	{ return reinterpret_cast<		DST>(v); }
template<class DST, class SRC> constexpr 	   DST reinCast(	  SRC& v)	{ return reinterpret_cast<		DST>(v); }
template<class DST, class SRC> constexpr const DST reinCast(const SRC* v)	{ return reinterpret_cast<const DST>(v); }
template<class DST, class SRC> constexpr const DST reinCast(const SRC& v)	{ return reinterpret_cast<const DST>(v); }

template<class DST, class SRC> constexpr DST constCast(const SRC* v) { return const_cast<DST>(v); }
template<class DST, class SRC> constexpr DST constCast(const SRC& v) { return const_cast<DST>(v); }

template<class SRC> constexpr RemoveConst<SRC>* constCast(const SRC* v) { return const_cast<RemoveConst<SRC>*>(v); }
template<class SRC> constexpr RemoveConst<SRC>& constCast(const SRC& v) { return const_cast<RemoveConst<SRC>&>(v); }

#endif

template<class T> inline void swap(T& a,	 T& b) { T  tmp = move(a); a = move(b); b = move(tmp); }
template<class T> inline void swap(T*& a,	T*& b) { T* tmp = move(a); a = move(b); b = move(tmp); }

template<class T>
static constexpr T _alignTo(T n, T a)
{
	static_assert(IsUInt<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
}

template<class OBJ, class MEMBER> inline 
constexpr ptrdiff_t 
memberOffset(MEMBER OBJ::* member)
{
	OBJ*	o = nullptr;
	MEMBER* m = &(o->*member);
	return reinCast<intptr_t>(m);
}


template<class T, size_t N>
size_t 
arraySize(T (&arr)[N])
{
	return N;
}

template<class CAST_TO, class T, size_t N>
CAST_TO 
arraySizeT(T (&arr)[N])
{
	return sCast<CAST_TO>(N);
}

#if 0
#pragma mark --- nmsp_os_alloc-Impl ---
#endif // 0
#if 1

inline void*
os_aligned_alloc(size_t size, size_t alignment)
{
	#if NMSP_OS_WINDOWS
	return _aligned_malloc(size, alignment);
	#else
	return std::aligned_alloc(alignment, size);
	#endif
}

inline void
os_aligned_free(void* p)
{
	#if NMSP_OS_WINDOWS
	return _aligned_free(p);
	#else
	return std::free(p);
	#endif
}

#endif // 0


}