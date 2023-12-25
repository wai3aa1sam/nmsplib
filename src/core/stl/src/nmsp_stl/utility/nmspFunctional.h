#pragma once

#include "../common/nmsp_stl_common.h"


#if 0
#pragma mark --- stl_container_backend_switch-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD

#elif NMSP_STL_BUILD_CONTAINER_NMSP

#elif NMSP_STL_BUILD_CONTAINER_EASTL
	
	#include "nmsp_stl/backend/eastl/common/nmspStl_Common_Eastl.h"

	namespace nmsp {

	template<class T> struct Less				: public eastl::less<T>		{};
	template<class T> struct EqualTo			: public eastl::equal_to<T>	{};
	template<class T> struct StrLess			: public eastl::str_less<T>	{};

	template<class T = void> struct Plus		: public eastl::plus<T>		{};

	template<class T> struct Hash				: public eastl::hash<T>		{};

	template<class FUNC, class... ARGS> constexpr decltype(auto) invoke(ARGS&&... args);

	}

#else
	#error "nmspFunctional.h should have backend switch"
#endif // NMSP_STL_BUILD_CONTAINER_EASTL

#endif

namespace nmsp {


template<class T, size_t N> inline
constexpr T accumulator(const T (&arr)[N])
{
	T sum(T(0));
	for (int i = 0; i < N; ++i)
	{
		sum = Plus()(sum, arr[i]);
	}
	return sum;
}


template<size_t I, class T, size_t N> inline
constexpr T accumulateTo(const T (&arr)[N])
{
	T sum(T(0));
	for (int i = 0; i < I; ++i)
	{
		sum = Plus()(sum, arr[i]);
	}
	return sum;
}

template<class FUNC, class... ARGS> inline constexpr
decltype(auto) invoke(FUNC&& func, ARGS&&... args)
{
	return eastl::invoke(nmsp::forward<FUNC>(func), nmsp::forward<ARGS>(args)...);
}


}


