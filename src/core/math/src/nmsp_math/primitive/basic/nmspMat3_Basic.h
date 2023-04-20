#pragma once

#include "nmsp_math/common/nmsp_math_common.h"


#if 0
#pragma mark --- nmsp_math_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_MATH_BACKEND_NMSP
	
	#include "nmsp/nmspMat3_Basic_Nmsp.h"

	namespace nmsp {

	template<class T>				using Mat3_Basic_Data_Impl	= Mat3_Basic_Data_Nmsp<T>;
	template<class T, class DATA>	using Mat3_Basic_Impl		= Mat3_Basic_Nmsp<T, DATA>;

	}

#elif NMSP_MATH_BACKEND_GLM

	#include "glm/nmspMat3_Basic_Glm.h"

	namespace nmsp {

	template<class T>				using Mat3_Basic_Data_Impl	= Mat3_Basic_Data_Glm<T>;
	template<class T, class DATA>	using Mat3_Basic_Impl		= Mat3_Basic_Glm<T, DATA>;

	}

#else
	#error "--- error: nmsp_math_backend_switch"
#endif // NMSP_MATH_BACKEND_NMSP

namespace nmsp {

template<class T>										using Mat3_Basic_Data_T = Mat3_Basic_Data_Impl<T>;
template<class T, class DATA = Mat3_Basic_Data_T<T> >	using Mat3_Basic_T		= Mat3_Basic_Impl<T, DATA>;

}
#endif

