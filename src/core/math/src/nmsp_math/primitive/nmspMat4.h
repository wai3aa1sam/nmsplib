#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspVec3_Basic.h"
#include "simd/nmspVec3_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Vec3_T = Vec3_SIMD_T<T>;

#else

template<class T> using Vec3_T = Vec3_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Vec3f_T = Vec3_T<f32>;
using Vec3d_T = Vec3_T<f64>;
using Vec3i_T = Vec3_T<i32>;
using Vec3u_T = Vec3_T<u32>;

template<class T>
void onFormat(fmt::format_context& ctx, const Vec3_T<T>& v)
{
	formatTo(ctx, "({}, {}, {})", v.x, v.y, v.z);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Vec3_T<T> );

}
