#pragma once

#include <nmsp_core_base.h>
//#include <nmsp_log.h>

#include "nmsp_math-config.h"
#include "nmsp_math_traits.h"

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif


#if NMSP_MATH_BACKEND_GLM

	#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
	#define GLM_FORCE_SIMD_AVX2
	#define GLM_FORCE_ALIGNED
	#define GLM_FORCE_SSE2

	#pragma warning( push )
	#pragma warning( disable : 4324)

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>

	#include <glm/gtx/quaternion.hpp>
	#include <glm/gtx\euler_angles.hpp>
	#include <glm/gtx\rotate_vector.hpp>
	#include <glm/gtx/matrix_decompose.hpp>

	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>

	#pragma warning( pop )

#endif // 1
