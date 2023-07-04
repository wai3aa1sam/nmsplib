#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"
#include "nmspTypeTraits_Common.h"

#include "fmt/format.h"

#define _NMSP_LOG(...) do{ ::nmsp::_log(__VA_ARGS__); } while(false)

#define _NMSP_DUMP_VAR_1(v0)				do{ _NMSP_LOG("DUMP_VAR: {}=[{}]",								#v0, (v0)); } while(false)
#define _NMSP_DUMP_VAR_2(v0, v1)			do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}]",						#v0, (v0), #v1, (v1)); } while(false)
#define _NMSP_DUMP_VAR_3(v0, v1, v2)		do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}]",			#v0, (v0), #v1, (v1), #v2, (v2)); } while(false)
#define _NMSP_DUMP_VAR_4(v0, v1, v2, v3)	do{ _NMSP_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}]",	#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3)); } while(false)

#define _NMSP_DUMP_VAR_SELECT(COUNT) _NMSP_DUMP_VAR_##COUNT
#define _NMSP_DUMP_VAR(...) NMSP_IDENTITY(NMSP_CALL(_NMSP_DUMP_VAR_SELECT, NMSP_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))

namespace nmsp {

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

template<class DST, class SRC> constexpr DST* constCast(const SRC* v) { return const_cast<DST>(v); }
template<class DST, class SRC> constexpr DST& constCast(const SRC& v) { return const_cast<DST>(v); }

#endif

template<class T> inline void swap(T& a, T& b) { T tmp = move(a); a = move(b); b = move(tmp); }

template<class T>
static constexpr T _alignTo(T n, T a)
{
	static_assert(IsUInt<T>, "");
	T r = n % a;
	return r ? (n + a - r) : n;
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


#if 0
#pragma mark --- nmspInternalLog-Impl ---
#endif // 0
#if 1

inline void _log()
{

}

template<class... ARGS> inline
void _log(const char* format, ARGS&&... args)
{
	std::cout << fmtAs_T<std::string>(format, nmsp::forward<ARGS>(args)...) << "\n";
}

#endif

inline void _notYetSupported()
{
	NMSP_ASSERT(false, "not yet supported");
}

}