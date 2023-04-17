#pragma once

#include "nmsp_math/common/nmsp_math_common.h"
#include "basic/nmspQuat4_Basic.h"
#include "simd/nmspQuat4_SIMD.h"

namespace nmsp {

#if NMSP_MATH_USE_SIMD

template<class T> using Quat4_T = Quat4_SIMD_T<T>;

#else

template<class T> using Quat4_T = Quat4_Basic_T<T>;

#endif // NMSP_MATH_USE_SIMD

using Quat4f_T = Quat4_T<f32>;
using Quat4d_T = Quat4_T<f64>;
using Quat4i_T = Quat4_T<i32>;
using Quat4u_T = Quat4_T<u32>;


#if 0
#pragma mark --- Quat4_T_AddOns-Impl ---
#endif // 0
#if 1
template<class T>
void onFormat(fmt::format_context& ctx, const Quat4_T<T>& v)
{
	formatTo(ctx, "({}, {}, {}, {})", v.w, v.x, v.y, v.z);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Quat4_T<T> );






namespace Math {

template<class T, class EP = T> NMSP_INLINE 
bool equals (const Quat4_T<T>& a, const Quat4_T<T>& b, const EP& ep = epsilon<T>()) 
{ 
	return a.equals(b, ep);
}

template<class T, class EP = T> NMSP_INLINE 
bool equals0(const Quat4_T<T>& a,					   const EP& ep = epsilon<T>())
{ 
	return a.equals0(ep); 
}

}
#endif


}
