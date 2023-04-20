#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

#if NMSP_MATH_BACKEND_GLM

#include "nmsp_math/primitive/basic/glm/nmspMat3_Basic_Glm.h"

namespace nmsp {
#if 0
#pragma mark --- Mat3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Mat3_SIMD_T = glm::mat<3, 3, T, glm::aligned_lowp>;

template<class T> 
struct Mat3_SIMD_Data_Glm : public Glm_Mat3_SIMD_T<T>
{
public:
	using Base		= Glm_Mat3_SIMD_T<T>;
	
	using Vec3 = Vec3_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Mat3_SIMD_Data_Glm()
		: Base(	  Vec3{ T(0.0), T(0.0), T(0.0) }
				, Vec3{ T(0.0), T(0.0), T(0.0) }
				, Vec3{ T(0.0), T(0.0), T(0.0) }
				, Vec3{ T(0.0), T(0.0), T(0.0) } )
	{
	}

	Mat3_SIMD_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T> using Mat3_SIMD_Glm = Mat3_Basic_Glm<T, Mat3_SIMD_Data_Glm<T> >;


#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Mat3_Basic_Glm-Impl ---
#endif // 0
#if 1



#endif
}

#endif // NMSP_MATH_BACKEND_GLM
