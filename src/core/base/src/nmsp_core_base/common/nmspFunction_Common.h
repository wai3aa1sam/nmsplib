#pragma once

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

#if 0
#pragma mark --- nmspFormatter-Impl ---
#endif // 0
#if 1

template<class STR, class... ARGS> inline
void fmtTo(STR& outStr, ARGS&&... args)
{
	fmt::format_to(std::back_inserter(outStr), std::forward<ARGS>(args)...);
}

template<class STR, class... ARGS> inline
STR fmtAs(ARGS&&... args)
{
	STR out;
	fmtTo(out, std::forward<ARGS>(args)...);
	return out;
}

#endif



}