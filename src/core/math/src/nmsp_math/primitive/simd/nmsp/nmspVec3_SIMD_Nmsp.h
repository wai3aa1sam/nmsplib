#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

#include <xmmintrin.h>

#if NMSP_MATH_BACKEND_NMSP

namespace nmsp {
#if 0
#pragma mark --- Vec3_Basic_Nmsp-Decl ---
#endif // 0
#if 1

template<class T, class M> 
struct Vec3_SIMD_Data_Nmsp
{
public:
	using SizeType = size_t;

public:
	static constexpr size_t s_kElementCount = 3;

public:
	union
	{
		struct { T x, y, z; T _padding; };
		T data[s_kElementCount];
		M _m;
	};
};


template<class T> 
struct Vec3_SIMD_Data_Nmsp_Selector;
struct Vec3_SIMD_Data_Nmsp_Selector<f32> { using Data = Vec3_SIMD_Data_Nmsp<f32, __m128>; };
struct Vec3_SIMD_Data_Nmsp_Selector<f64> { using Data = Vec3_SIMD_Data_Nmsp<f64, __m256>; };

template<class T> using Vec3_SIMD_Nmsp = Vec3_Basic_Nmsp<T, typename Vec3_SIMD_Data_Nmsp_Selector<T>::Data> >;

using Vec3f_SIMD_Nmsp = Vec3_SIMD_Nmsp<f32>;
using Vec3d_SIMD_Nmsp = Vec3_SIMD_Nmsp<f64>;

#endif // NMSP_MATH_BACKEND_NMSP


#if 0
#pragma mark --- Vec3_Basic_Nmsp-Impl ---
#endif // 0
#if 1


#endif


}
#endif // NMSP_MATH_BACKEND_NMSP
