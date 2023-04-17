#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspVec4_Basic.h"
#include "simd/nmspVec4_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Vec4_T = Vec4_SIMD_T<T>;

#else

template<class T> using Vec4_T = Vec4_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Vec4f_T = Vec4_T<f32>;
using Vec4d_T = Vec4_T<f64>;
using Vec4i_T = Vec4_T<i32>;
using Vec4u_T = Vec4_T<u32>;


#if 0
#pragma mark --- Vec4_T_AddOns-Impl ---
#endif // 0
#if 1
template<class T>
void onFormat(fmt::format_context& ctx, const Vec4_T<T>& v)
{
	formatTo(ctx, "({}, {}, {}, {})", v.x, v.y, v.z, v.w);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Vec4_T<T> );






//namespace Math {
//
//template<class T, class EP = T> NMSP_INLINE 
//bool equals (const Vec4_T<T>& a, const Vec4_T<T>& b, const EP& ep = epsilon<T>()) 
//{ 
//	return a.equals(b, ep);
//}
//
//template<class T, class EP = T> NMSP_INLINE 
//bool equals0(const Vec4_T<T>& a,					 const EP& ep = epsilon<T>())
//{ 
//	return a.equals0(ep); 
//}
//
//}
#endif


}
