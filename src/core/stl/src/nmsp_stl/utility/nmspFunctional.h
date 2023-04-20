#pragma once

#include "../common/nmsp_stl_common.h"


#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_STD_CONTAINER

#elif NMSP_STL_BUILD_NMSP_CONTAINER

#elif NMSP_STL_BUILD_EASTL_CONTAINER
	
	#include "EASTL/functional.h"

	namespace nmsp {

	template<class T> struct Less		: public eastl::less<T>		{};
	template<class T> struct EqualTo	: public eastl::equal_to<T>	{};
	template<class T> struct StrLess	: public eastl::str_less<T>	{};

	template<class T> struct Hash		: public eastl::hash<T>		{};

	}

#else
	#error "nmspFunctional.h should have backend switch"
#endif // NMSP_STL_BUILD_EASTL_CONTAINER

#endif


