#pragma once

/*
references:
~ Plane3.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#include "nmspMathGeometry_Common.h"
#include "nmspMathTriangle3.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- nmspPlane3_T-Decl ---
#endif // 0
#if 1

template<class T>
struct Plane3_T
{
public:
	using Vec3		= Vec3_T<T>;
	using Triangle3 = Triangle3_T<T>;

public:
	Vec3	normal;
	T		distance; // distance from origin

public:
	Plane3_T() = default;
	Plane3_T(const Vec3& normal_, T distance_)
		: normal(normal_)
		, distance(distance_) 
	{}

	Plane3_T(const Vec3& normal_, const Vec3& point_)
		: normal(normal_)
		, distance(normal_.dot(point_))
	{}

	Plane3_T(const Triangle3&  tri) { setByTriangle(tri); }

public:
	void set(const Vec3& normal_, T distance_) 
	{
		normal = normal_;
		distance = distance_;
	}

	void setByTriangle(const Triangle3&  tri) 
	{
		setByTriangle(tri.v0, tri.v1, tri.v2);
	}

	void setByTriangle(const Vec3& v0, const Vec3& v1, Vec3& v2) 
	{
		normal = (v1 - v0).cross(v2 - v0).normalize();
		distance = normal.dot(v0);
	}

	T dot(const Vec3& point) const { return normal.dot(point) - distance; }

public:
	void onFormat(fmt::format_context& f) const;
};


#endif

#if 0
#pragma mark --- Plane3-Impl ---
#endif // 0
#if 1



#endif

using Plane3f_T  = Plane3_T<float>;
using Plane3d_T  = Plane3_T<double>;

}
}
