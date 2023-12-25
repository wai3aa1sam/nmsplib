#pragma once

#include "nmspMathGeometry_Common.h"

/*
references:
~ Line3.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {
namespace math {

template<class T> struct Line3_T;
using Line3f_T = Line3_T<float>;
using Line3d_T = Line3_T<double>;

#if 0
#pragma mark --- Line3-Decl ---
#endif // 0
#if 1

template<class T>
struct Line3_T 
{
	using Vec3 = nmsp::Vec3_T<T>;
public:
	Line3_T() = default;
	Line3_T(const Vec3& start_, const Vec3& end_)
		: start(start_)
		, end(end_)
	{}

	bool getClosestPoint(Vec3& outPoint, const Vec3& inPoint) const;

	T	distanceToPoint(const Vec3& pt) const;

	Vec3	start;
	Vec3	end;
};


#endif

#if 0
#pragma mark --- Line3-Impl ---
#endif // 0
#if 1



#endif

}
}
