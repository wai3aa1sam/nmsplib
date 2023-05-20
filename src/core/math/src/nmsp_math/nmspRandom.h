#pragma once

#include "common/nmsp_math_common.h"

namespace nmsp {

#if 0
#pragma mark --- Random_T-Decl ---
#endif // 0
#if 1

class Random_T : public NonCopyable
{
public:
	template<class T> T range(T min, T max);

public:

public:
	static Random_T& _internal_s_get();

private:
	std::default_random_engine _rng { std::random_device{}() };
};


#endif


#if 0
#pragma mark --- Random_T-Impl ---
#endif // 0
#if 1

template<class T> inline 
T Random_T::range(T min, T max)
{
	if constexpr(IsIntegral<T>)
	{
		std::uniform_int_distribution<T> uni(min, max);
		return uni(_rng);
	}
	else if constexpr(IsFloat<T>)
	{
		std::uniform_real_distribution<T> uni(min, max);
		return uni(_rng);
	}
	else
	{
		NMSP_ASSERT(false, "");
		return 0;
	}
}

#endif

}