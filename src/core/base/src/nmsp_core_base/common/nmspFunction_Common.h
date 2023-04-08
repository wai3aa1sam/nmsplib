#pragma once

#include "nmspTypeTrait_Common.h"

#include "fmt/format.h"

namespace nmsp {

#if 0
#pragma mark --- nmspCast-Impl ---
#endif // 0
#if 1

template<class DST, class SRC>		 DST sCast(		 SRC* v)	{ return static_cast<	   DST>(v); }
template<class DST, class SRC>		 DST sCast(		 SRC& v)	{ return static_cast<	   DST>(v); }
template<class DST, class SRC> const DST sCast(const SRC* v)	{ return static_cast<const DST>(v); }
template<class DST, class SRC> const DST sCast(const SRC& v)	{ return static_cast<const DST>(v); }

template<class DST, class SRC>		 DST reinCast(		SRC* v)	{ return reinterpret_cast<		DST>(v); }
template<class DST, class SRC>		 DST reinCast(		SRC& v)	{ return reinterpret_cast<		DST>(v); }
template<class DST, class SRC> const DST reinCast(const SRC* v)	{ return reinterpret_cast<const DST>(v); }
template<class DST, class SRC> const DST reinCast(const SRC& v)	{ return reinterpret_cast<const DST>(v); }

template<class T> T* constCast(const T* v) { return const_cast<T*>(v); }
template<class T> T& constCast(const T& v) { return const_cast<T&>(v); }

#endif

template<class T> inline void swap(T& a, T& b) { T tmp = move(a); a = move(b); b = move(tmp); }


}