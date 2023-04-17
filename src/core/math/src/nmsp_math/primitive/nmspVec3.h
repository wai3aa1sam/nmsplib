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

#if 0
#pragma mark --- Vec3_T_AddOns-Impl ---
#endif // 0
#if 1
template<class T>
void onFormat(fmt::format_context& ctx, const Vec3_T<T>& v)
{
	formatTo(ctx, "({}, {}, {})", v.x, v.y, v.z);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Vec3_T<T> );






namespace Math {

template<class T, class EP = T> NMSP_INLINE
bool equals(const Vec3_T<T>& a, const Vec3_T<T>& b, const EP& ep = epsilon<T>())
{
	return a.equals(b, ep);
}

template<class T, class EP = T> NMSP_INLINE 
bool equals0(const Vec3_T<T>& a,					const EP& ep = epsilon<T>())
{
	return a.equals0(ep);
}

}
#endif


}
