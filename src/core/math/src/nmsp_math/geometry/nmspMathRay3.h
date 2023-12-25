#pragma once

#include "nmspMathGeometry_Common.h"
#include "nmsp_math/primitive/nmspMat4.h"
#include "nmspMathLine3.h"
#include "nmspMathRect2.h"

#include "nmsp_math/primitive/nmspVec3.h"

/*
references:
~ Ray3.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {
namespace math {

template<class T> struct Ray3_T;
using Ray3f_T = Ray3_T<float>;
using Ray3d_T = Ray3_T<double>;

#if 0
#pragma mark --- Ray3_T-Decl ---
#endif // 0
#if 1

template<class T>
struct Ray3_T 
{
private:
	using Vec2		= nmsp::Vec2_T<T>;
	using Vec3		= nmsp::Vec3_T<T>;
	using Vec4		= nmsp::Vec4_T<T>;
	using Mat4		= nmsp::Mat4_T<T>;
	using Rect2		= nmsp::math::Rect2_T<T>;
	using Line3		= nmsp::math::Line3_T<T>;
public:

	Vec3 origin, dir;

	Ray3_T() = default;
	Ray3_T(const Vec3& origin_, const Vec3& dir_) : origin(origin_), dir(dir_) {}

	constexpr static Ray3_T s_zero() { return Ray3_T(Vec3::s_zero(), Vec3::s_zero()); }

	static Ray3_T s_unprojectFromInvMatrix(const Vec2& screenPos, const Mat4& invMat, const Rect2& viewport);

	struct HitTestResult {
		T		distance = Math::inf<T>();
		Vec3	point;
		Vec3	normal;

		bool	hasResult() const { return distance != math::inf<T>(); }
	};

	bool getClosestPoint(Vec3& outPoint, const Vec3& inPoint) const;
	bool getClosestPoint(Vec3& outPoint, const Line3& line, T minOnLine = 0, T maxOnLine = 1) const;
};

#endif

#if 0
#pragma mark --- Ray3_T-Impl ---
#endif // 0
#if 1



#endif

}
}
