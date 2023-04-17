#pragma once

#include "nmsp_math/common/nmsp_math_common.h"


#if 0
#pragma mark --- stl_math_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_MATH_BACKEND_NMSP
	
	#include "nmsp/nmspQuat4_SIMD_Nmsp.h"

	namespace nmsp {

	template<class T> using Quat4_SIMD_Data_Impl	= Quat4_SIMD_Data_Nmsp<T>;
	template<class T> using Quat4_SIMD_Impl			= Quat4_SIMD_Nmsp<T>;

	}

#elif NMSP_MATH_BACKEND_GLM

	#include "glm/nmspQuat4_SIMD_Glm.h"

	namespace nmsp {

	template<class T> using Quat4_SIMD_Data_Impl	= Quat4_SIMD_Data_Glm<T>;
	template<class T> using Quat4_SIMD_Impl			= Quat4_SIMD_Glm<T>;

	}

#else
	#error "--- error: stl_math_backend_switch"
#endif // NMSP_MATH_BACKEND_NMSP

namespace nmsp {

template<class T>	using Quat4_SIMD_Data_T	= Quat4_SIMD_Data_Impl<T>;
template<class T>	using Quat4_SIMD_T		= Quat4_SIMD_Impl<T>;

}
#endif

