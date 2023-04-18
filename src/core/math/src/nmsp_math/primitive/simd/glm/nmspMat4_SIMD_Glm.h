#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspMat4_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Mat4_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Mat4_SIMD_T = glm::mat<4, 4, T, glm::aligned_lowp>;

template<class T> 
struct Mat4_SIMD_Data_Glm : public Glm_Mat4_SIMD_T<T>
{
public:
	using Base		= Glm_Mat4_SIMD_T<T>;
	
	using Vec4 = Vec4_T<T>;

	using ElementType	= T;
	using SizeType		= NmspMathTraits::SizeType;
	using IndexType		= NmspMathTraits::IndexType;

public:
	Mat4_SIMD_Data_Glm()
		: Base(	  Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) } )
	{
	}

	Mat4_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Mat4_SIMD_Glm = Mat4_Basic_Glm<T, Mat4_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Mat4_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
