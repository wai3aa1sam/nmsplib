#pragma once

#include "nmsp_math/common/nmsp_math_common.h"


#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspVec2_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Vec2_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec2_SIMD_T = glm::vec<2, T, glm::aligned_lowp>;

template<class T> 
struct Vec2_SIMD_Data_Glm : public Glm_Vec2_SIMD_T<T>
{
public:
	using Base		= Glm_Vec2_SIMD_T<T>;
	
	using ElementType	= T;
	using SizeType		= NmspMathTraits::SizeType;
	using IndexType		= NmspMathTraits::IndexType;

public:
	Vec2_SIMD_Data_Glm()
		: Base(T(0.0), T(0.0))
	{
	}

	Vec2_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Vec2_SIMD_Glm = Vec2_Basic_Glm<T, Vec2_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec2_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
