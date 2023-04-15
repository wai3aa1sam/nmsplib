#pragma once

#ifndef NMSP_MATH_USE_SIMD
	#define NMSP_MATH_USE_SIMD 1
#endif // 0

#ifndef NMSP_MATH_BACKEND_GLM
	#define NMSP_MATH_BACKEND_GLM	1
#endif // 

#ifndef NMSP_MATH_BACKEND_NMSP
	#define NMSP_MATH_BACKEND_NMSP	0
#endif //

#if NMSP_MATH_BACKEND_GLM + NMSP_MATH_BACKEND_NMSP != 1
	#error "error NMSP_MATH_BACKEND"
#endif
