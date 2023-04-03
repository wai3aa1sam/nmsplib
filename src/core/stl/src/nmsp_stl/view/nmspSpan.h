#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#if NMSP_BUILD_STL_STD_CONTAINER

#include "nmsp/nmspSpan_Std.h"

namespace nmsp {


}

#elif NMSP_BUILD_STL_NMSP_CONTAINER

#include "nmsp/nmspSpan_Nmsp.h"

namespace nmsp {

}


#elif NMSP_BUILD_STL_EASTL_CONTAINER

#include "eastl/nmspSpan_Eastl.h"

namespace nmsp {

template<class T> using Span_Impl = Span_Eastl<T>;

}

#else
#error "unsupported stl build"
#endif // 0

namespace nmsp {

template<class T> using Span_T = Span_Impl<T>;
using ByteSpan_T = Span_T<const u8>;

template<class DST, class SRC> inline
Span_T<DST> spanCast(Span_T<SRC> src)
{
	size_t srcBytes = src.size_bytes();
	return Span<DST>(reinterpret_cast<DST>(src.data()), srcBytes / sizeof(DST));
}

}