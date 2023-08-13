#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

	#include "std/nmspSpan_Std.h"

	namespace nmsp {


	}

#elif NMSP_STL_BUILD_CONTAINER_NMSP

	#include "nmsp/nmspSpan_Nmsp.h"

	namespace nmsp {

	}


#elif NMSP_STL_BUILD_CONTAINER_EASTL

	#include "eastl/nmspSpan_Eastl.h"

	namespace nmsp {

	template<class T> using Span_Impl = Span_Eastl<T>;

	}

#else
	#error "--- error: nmsp_stl unsupported build container"
#endif // 0

#endif

namespace nmsp {

template<class T> using Span_T = Span_Impl<T>;
using ByteSpan_T = Span_T<const u8>;

template<class DST, class SRC> inline
Span_T<DST> spanCast(Span_T<SRC> src)
{
	size_t srcBytes = src.size_bytes();
	return Span_T<DST>(reinCast<DST*>(src.data()), srcBytes / sizeof(DST));
}

template<class T> inline 
ByteSpan_T 
makeByteSpan(Span_T<T> sv)
{
	return spanCast<const u8>(sv);
}


}