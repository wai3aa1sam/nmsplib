#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple4.h"

#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspQuat4_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Quat4_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Quat4_SIMD_T = glm::qua<T, glm::aligned_lowp>;

template<class T> 
struct Quat4_SIMD_Data_Glm : public Glm_Quat4_SIMD_T<T>
{
public:
	using Base		= Glm_Quat4_SIMD_T<T>;
	
	using ElementType = T;
	using SizeType = NmspMathTraits::SizeType;
	using IndexType = NmspMathTraits::IndexType;

public:
	Quat4_SIMD_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0), T(0.0))
	{
	}

	Quat4_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Quat4_SIMD_Glm = Quat4_Basic_Glm<T, Quat4_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Quat4_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
