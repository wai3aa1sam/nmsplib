#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspVec2_Basic.h"
#include "simd/nmspVec2_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Vec2_T = Vec2_SIMD_T<T>;

#else

template<class T> using Vec2_T = Vec2_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Vec2f_T = Vec2_T<f32>;
using Vec2d_T = Vec2_T<f64>;
using Vec2i_T = Vec2_T<i32>;
using Vec2u_T = Vec2_T<u32>;


#if 0
#pragma mark --- Vec2_T_AddOns-Impl ---
#endif // 0
#if 1
template<class T>
void onFormat(fmt::format_context& ctx, const Vec2_T<T>& v)
{
	formatTo(ctx, "Vec2({}, {})", v.x, v.y);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Vec2_T<NMSP_ARGS(T)> );

template<class T> inline void swap(Vec2_T<T>& lhs, Vec2_T<T>& rhs) noexcept { nmsp::swap<Vec2_T<T> >(lhs, rhs); }

namespace math {

//template<class T, class EP = T> NMSP_INLINE
//bool equals(const Vec2_T<T>& a, const Vec2_T<T>& b, const EP& ep = epsilon<T>())
//{
//	return a.equals(b, ep);
//}
//
//template<class T, class EP = T> NMSP_INLINE
//bool equals0(const Vec2_T<T>& a,					const EP& ep = epsilon<T>())
//{
//	return a.equals0(ep);
//}

}
#endif


}
