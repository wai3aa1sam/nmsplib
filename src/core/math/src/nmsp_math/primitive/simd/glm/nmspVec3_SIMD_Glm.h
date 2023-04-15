#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

//#include "nmsp_math/primitive/nmspVec2.h"


#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspVec3_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Vec3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec3_SIMD_T = glm::vec<3, T, glm::aligned_lowp>;

template<class T> 
struct Vec3_SIMD_Data_Glm : public Glm_Vec3_SIMD_T<T>
{
public:
	using Base		= Glm_Vec3_SIMD_T<T>;
	using SizeType	= size_t;

public:
	Vec3_SIMD_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0))
	{
	}

	Vec3_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Vec3_SIMD_Glm = Vec3_Basic_Glm<T, Vec3_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec3_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
