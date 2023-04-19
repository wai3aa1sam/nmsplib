#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspMat3_Basic.h"
#include "simd/nmspMat3_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Mat3_T = Mat3_SIMD_T<T>;

#else

template<class T> using Mat3_T = Mat3_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Mat3f_T = Mat3_T<f32>;
using Mat3d_T = Mat3_T<f64>;
using Mat3i_T = Mat3_T<i32>;
using Mat3u_T = Mat3_T<u32>;

template<class T>
void onFormat(fmt::format_context& ctx, const Mat3_T<T>& v)
{
	formatTo(ctx, "Mat3(\n	{},\n	{},\n	{})", v.row(0), v.row(1), v.row(2));
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Mat3_T<T> );

}
