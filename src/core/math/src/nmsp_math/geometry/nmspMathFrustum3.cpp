#include "nmsp_math-pch.h"
#include "nmspMathFrustum3.h"

namespace nmsp {
namespace math {

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

template<class T>
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

template<class T>
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

template<class T>
void 
Frustum3_T<T>::setByInvViewProjMatrix(const Mat4& invMatrix) 
{
	points[0] = invMatrix.mulPoint(Vec4(-1,	-1,  0, 1)).toVec3();
	points[1] = invMatrix.mulPoint(Vec4( 1,	-1,  0, 1)).toVec3();
	points[2] = invMatrix.mulPoint(Vec4( 1,	 1,  0, 1)).toVec3();
	points[3] = invMatrix.mulPoint(Vec4(-1,	 1,  0, 1)).toVec3();

	points[4] = invMatrix.mulPoint(Vec4(-1,	-1,  1, 1)).toVec3();
	points[5] = invMatrix.mulPoint(Vec4( 1,	-1,  1, 1)).toVec3();
	points[6] = invMatrix.mulPoint(Vec4( 1,	 1,  1, 1)).toVec3();
	points[7] = invMatrix.mulPoint(Vec4(-1,	 1,  1, 1)).toVec3();

	updatePlanesFromPoints();
}

template struct Frustum3_T<float>;
template struct Frustum3_T<double>;


#endif

}

}