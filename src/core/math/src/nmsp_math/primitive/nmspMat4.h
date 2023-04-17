#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspMat4_Basic.h"
#include "simd/nmspMat4_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Mat4_T = Mat4_SIMD_T<T>;

#else

template<class T> using Mat4_T = Mat4_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Mat4f_T = Mat4_T<f32>;
using Mat4d_T = Mat4_T<f64>;
using Mat4i_T = Mat4_T<i32>;
using Mat4u_T = Mat4_T<u32>;


#if 0
#pragma mark --- Mat4_T_AddOns-Impl ---
#endif // 0
#if 1
template<class T>
void onFormat(fmt::format_context& ctx, const Mat4_T<T>& v)
{
	formatTo(ctx, "({}, {}, {}, {})", v[0], v[1], v[2], v[3]);
}
NMSP_FORMATTER_T(NMSP_ARGS(class T), Mat4_T<T>);






namespace Math {

template<class T, class EP = T> NMSP_INLINE
bool equals(const Mat4_T<T>& a, const Mat4_T<T>& b, const EP& ep = epsilon<T>())
{
	return a.equals(b, ep);
}

template<class T, class EP = T> NMSP_INLINE
bool equals0(const Mat4_T<T>& a, const EP& ep = epsilon<T>())
{
	return a.equals0(ep);
}

}
#endif


}
