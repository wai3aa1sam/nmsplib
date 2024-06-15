#pragma once

/*
references:
~ MathGeometry.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#include "nmspMathGeometry_Common.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- nmspTriangle3_T-Decl ---
#endif // 0
#if 1

template<class T>
struct Triangle3_T 
{
public:
	using Vec3 = Vec3_T<T>;

public:
	Vec3 v0, v1, v2;

public:
	Triangle3_T() = default;
	Triangle3_T(const Vec3& v0_, const Vec3& v1_, const Vec3& v2_) : v0(v0_), v1(v1_), v2(v2_) {}
};

#endif

#if 0
#pragma mark --- Triangle3-Impl ---
#endif // 0
#if 1



#endif

}
}
