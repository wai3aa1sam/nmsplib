#pragma once

/*
references:
~ Frustum3.h		- https://github.com/SimpleTalkCpp/SimpleGameEngine
~ isOverlapped()	- https://iquilezles.org/articles/frustumcorrect/
*/

#include "nmspMathGeometry_Common.h"
#include "nmspMathPlane3.h"
#include "nmspMathAABBox3.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- nmspFrustum3_T-Decl ---
#endif // 0
#if 1

enum Frustum3_Side
{
	Near,
	Far,
	Left,
	Right,
	Top,
	Bottom,
	_kCount,
};

/*
 planes
 _______________
 |		|		|
 |		v		|
 |--->		<---|
 |		^		|
 |______|_______|
 */
template<class T>
struct Frustum3_T 
{
	using Vec3			= Vec3_T<T>;
	using Vec4			= Vec4_T<T>;
	using Mat4			= Mat4_T<T>;
	using Plane3		= Plane3_T<T>;
	using AABBox3		= AABBox3_T<T>;

public:
	using SizeType	= MathTraits::SizeType;
	using Side		= Frustum3_Side;

public:
	static constexpr SizeType s_kVertexCount = 8;

public:
	Vec3	points[s_kVertexCount];
	Plane3	planes[Side::_kCount];

public:
	void setByViewProjMatrix(const Mat4& matrix) { setByInvViewProjMatrix(matrix.inverse()); }
	void setByInvViewProjMatrix(const Mat4& invMatrix);

	void setByBBox(const AABBox3& bbox, const Mat4& matrix);

public:
	bool isOverlapped(const AABBox3& v, const Mat4& matrix) const;
	bool isOverlapped(const AABBox3& v) const;
	bool isOverlapped(const Frustum3_T& f) const;

public:
			Plane3&	nearPlane()				{ return planes[Side::Near  ]; }
			Plane3&	farPlane()				{ return planes[Side::Far   ]; }
			Plane3&	leftPlane()				{ return planes[Side::Left  ]; }
			Plane3&	rightPlane()			{ return planes[Side::Right ]; }
			Plane3&	topPlane()				{ return planes[Side::Top   ]; }
			Plane3&	bottomPlane()			{ return planes[Side::Bottom]; }

	const	Plane3&	nearPlane()		const	{ return planes[Side::Near  ]; }
	const	Plane3&	farPlane()		const	{ return planes[Side::Far   ]; }
	const	Plane3&	leftPlane()		const	{ return planes[Side::Left  ]; }
	const	Plane3&	rightPlane()	const	{ return planes[Side::Right ]; }
	const	Plane3&	topPlane()		const	{ return planes[Side::Top   ]; }
	const	Plane3&	bottomPlane()	const	{ return planes[Side::Bottom]; }

	Vec3	center()							const;
	AABBox3 computeAABBox()						const;
	AABBox3 computeAABBox(const Mat4& matrix)	const;


private:
	void updatePlanesFromPoints();
	static bool _outsideOfPlane(const Plane3& p, const Vec3 points[8]);
};

#endif

#if 0
#pragma mark --- nmspFrustum3_T-Impl ---
#endif // 0
#if 1

template<class T> inline
bool 
Frustum3_T<T>::_outsideOfPlane(const Plane3& p, const Vec3 points[8]) 
{
	for (size_t i = 0; i < 8; i++) 
	{
		if (p.dot(points[i]) < 0)
			return false;
	}
	return true;
}

template<class T> inline
typename Frustum3_T<T>::Vec3
Frustum3_T<T>::center() const
{
	Vec3 center = Vec3::s_zero();
	for (const auto& e : points)
	{
		center += e;
	}
	center /= s_kVertexCount;
	return center;
}

template<class T> inline
typename Frustum3_T<T>::AABBox3
Frustum3_T<T>::computeAABBox() const
{
	AABBox3 aabbox;
	for (const auto& e : points)
	{
		aabbox.encapsulate(e);
	}
	return aabbox;
}

template<class T> inline
typename Frustum3_T<T>::AABBox3
Frustum3_T<T>::computeAABBox(const Mat4& matrix) const
{
	AABBox3 aabbox;
	for (const auto& e : points)
	{
		Vec3 pt = matrix.mulPoint4x3(e);
		aabbox.encapsulate(pt);
	}
	return aabbox;
}

#endif

using Frustum3f_T = Frustum3_T<float>;
using Frustum3d_T = Frustum3_T<double>;

}
}