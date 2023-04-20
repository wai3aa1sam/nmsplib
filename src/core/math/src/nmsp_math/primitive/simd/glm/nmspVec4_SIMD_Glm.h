#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple4.h"

#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspVec4_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Vec4_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec4_SIMD_T = glm::vec<4, T, glm::aligned_lowp>;

template<class T> 
struct Vec4_SIMD_Data_Glm : public Glm_Vec4_SIMD_T<T>
{
public:
	using Base		= Glm_Vec4_SIMD_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Vec4_SIMD_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0), T(0.0))
	{
	}

	Vec4_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Vec4_SIMD_Glm = Vec4_Basic_Glm<T, Vec4_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec4_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
