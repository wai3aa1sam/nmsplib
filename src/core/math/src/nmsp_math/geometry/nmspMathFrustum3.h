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

private:
	void updatePlanesFromPoints();
	static bool _outsideOfPlane(const Plane3& p, const Vec3 points[8]);
};

#endif

#if 0
#pragma mark --- nmspFrustum3_T-Impl ---
#endif // 0
#if 1

template<class T>
void Frustum3_T<T>::updatePlanesFromPoints()
{
	nearPlane().setByTriangle(	points[0], points[2], points[1]);
	farPlane().setByTriangle(	points[4], points[5], points[6]);

	leftPlane().setByTriangle(	points[0], points[4], points[3]);
	rightPlane().setByTriangle(	points[1], points[2], points[5]);

	topPlane().setByTriangle(	points[2], points[3], points[6]);
	bottomPlane().setByTriangle(points[0], points[1], points[4]);
}


template<class T>
void
Frustum3_T<T>::setByBBox(const AABBox3& bbox, const Mat4& matrix) 
{
	bbox.getPoints(points, matrix);
	updatePlanesFromPoints();
}

template<class T>
void 
Frustum3_T<T>::setByInvViewProjMatrix(const Mat4& invMatrix) 
{
	points[0] = invMatrix.mulPoint(Vec4(-1,-1, 0, 1)).toVec3();
	points[1] = invMatrix.mulPoint(Vec4( 1,-1, 0, 1)).toVec3();
	points[2] = invMatrix.mulPoint(Vec4( 1, 1, 0, 1)).toVec3();
	points[3] = invMatrix.mulPoint(Vec4(-1, 1, 0, 1)).toVec3();

	points[4] = invMatrix.mulPoint(Vec4(-1,-1, 1, 1)).toVec3();
	points[5] = invMatrix.mulPoint(Vec4( 1,-1, 1, 1)).toVec3();
	points[6] = invMatrix.mulPoint(Vec4( 1, 1, 1, 1)).toVec3();
	points[7] = invMatrix.mulPoint(Vec4(-1, 1, 1, 1)).toVec3();

	updatePlanesFromPoints();
}

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

template<class T>
bool
Frustum3_T<T>::isOverlapped(const Frustum3_T& f) const 
{
	for (size_t i = 0; i < Frustum3_Side::_kCount; i++) 
	{
		if (_outsideOfPlane(planes[i], f.points))
			return false;
	}

	for (size_t i = 0; i < Frustum3_Side::_kCount; i++) 
	{
		if (_outsideOfPlane(f.planes[i], points))
			return false;
	}

	return true;
}

template<class T> inline
bool 
Frustum3_T<T>::isOverlapped(const AABBox3& v, const Mat4& matrix) const 
{
	/*Frustum3_T tmp;
	tmp.setByBBox(bbox, matrix);
	return isOverlapped(tmp);*/

	AABBox3 aabbox;
	aabbox = v.makeExpanded(matrix);
	return isOverlapped(aabbox);
}

template<class T> inline
bool 
Frustum3_T<T>::isOverlapped(const AABBox3& v) const
{
	const AABBox3& aabbox = v;

	// check box outside/inside of frustum
	for(int i = 0; i < 6; i++)
	{
		int out = 0;
		out += ((planes[i].dot(Vec3(aabbox.min.x, aabbox.min.y, aabbox.min.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.max.x, aabbox.min.y, aabbox.min.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.min.x, aabbox.max.y, aabbox.min.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.max.x, aabbox.max.y, aabbox.min.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.min.x, aabbox.min.y, aabbox.max.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.max.x, aabbox.min.y, aabbox.max.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.min.x, aabbox.max.y, aabbox.max.z) ) < 0.0 ) ? 1 : 0);
		out += ((planes[i].dot(Vec3(aabbox.max.x, aabbox.max.y, aabbox.max.z) ) < 0.0 ) ? 1 : 0);
		if( out==8 ) return false;
	}

	// check frustum outside/inside box
	int out;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].x > aabbox.max.x) ? 1 : 0); if(out == 8) return false;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].x < aabbox.min.x) ? 1 : 0); if(out == 8) return false;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].y > aabbox.max.y) ? 1 : 0); if(out == 8) return false;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].y < aabbox.min.y) ? 1 : 0); if(out == 8) return false;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].z > aabbox.max.z) ? 1 : 0); if(out == 8) return false;
	out = 0; for(int i = 0; i < 8; i++) out += ((points[i].z < aabbox.min.z) ? 1 : 0); if(out == 8) return false;

	return true;
}



#endif

using Frustum3f_T = Frustum3_T<float>;
using Frustum3d_T = Frustum3_T<double>;

}
}