#pragma once

/*
references:
~ BBox3.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#include "nmspMathGeometry_Common.h"
#include "nmspMathRect2.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- nmspAABBox3-Decl ---
#endif // 0
#if 1

template<class T>
struct AABBox3_T 
{
public:
	using SizeType	= MathTraits::SizeType;
	using Vec3		= Vec3_T<T>;
	using Mat4		= Mat4_T<T>;
	using Rect2		= Rect2_T<T>;

public:
	static constexpr SizeType s_kVertexCount = 8;

public:
	Vec3	min;
	Vec3	max;

public:
	static AABBox3_T	s_invalid();
	static void			create(AABBox3_T& o, Vec3 pts[s_kVertexCount]);

public:
	AABBox3_T();
	AABBox3_T(const Vec3& min_, const Vec3& max_);

	void reset();
	void reset(const Vec3& min_, const Vec3& max_);

	void encapsulate(			const Vec3& pt);
	void encapsulate_CheckValid(const Vec3& pt);

	AABBox3_T makeExpanded(Vec3 outPoints[s_kVertexCount], const Mat4& matrix) const;
	AABBox3_T makeExpanded(const Mat4& matrix) const;

public:
	bool isValid() const;
	void getPoints(Vec3 outPoints[s_kVertexCount], const Mat4& matrix) const;
	void getPoints(Vec3 outPoints[s_kVertexCount]) const;

	bool isOverlapped(const AABBox3_T&	b) const;
	bool isInside(	  const Vec3&		pt) const;

public:
	Vec3	center()	const;
	Vec3	size()		const;
	Vec3	halfSize()	const;
	Rect2	toRect2()	const;
};

#endif

#if 0
#pragma mark --- nmspAABBox3-Impl ---
#endif // 0
#if 1

template<class T> inline 
AABBox3_T<T>	
AABBox3_T<T>::s_invalid() 
{ 
	T maxT		= NumLimit<T>::max();
	T lowestT	= NumLimit<T>::lowest();		// this one is -max ...
	return AABBox3_T<T>(Vec3{maxT, maxT, maxT}, Vec3(lowestT, lowestT, lowestT));
}

template<class T> inline 
void 
AABBox3_T<T>::create(AABBox3_T& o, Vec3 pts[s_kVertexCount])
{
	o.reset();
	for (size_t i = 0; i < s_kVertexCount; i++)
	{
		o.encapsulate(pts[i]);
	}
}

template<class T> inline
AABBox3_T<T>::AABBox3_T() 
{
	reset();
}

template<class T> inline
AABBox3_T<T>::AABBox3_T(const Vec3& min_, const Vec3& max_) 
	: min(min_), max(max_) 
{

}

template<class T> inline bool			AABBox3_T<T>::isValid() const	{ return min.x <= max.x && min.y <= max.y && min.z <= max.z; }

template<class T> inline 
void 
AABBox3_T<T>::reset()	
{
	auto invalid = s_invalid();
	min = invalid.min;
	max = invalid.max;
}

template<class T> inline 
void 
AABBox3_T<T>::reset(const Vec3& min_, const Vec3& max_)	
{
	min = min_;
	max = max_;
}

template<class T> inline
void 
AABBox3_T<T>::getPoints(Vec3 outPoints[s_kVertexCount], const Mat4& matrix) const 
{
	const auto& a = min;
	const auto& b = max;

	outPoints[0] = matrix.mulPoint4x3(Vec3(a.x, a.y, a.z));
	outPoints[1] = matrix.mulPoint4x3(Vec3(b.x, a.y, a.z));
	outPoints[2] = matrix.mulPoint4x3(Vec3(b.x, b.y, a.z));
	outPoints[3] = matrix.mulPoint4x3(Vec3(a.x, b.y, a.z));

	outPoints[4] = matrix.mulPoint4x3(Vec3(a.x, a.y, b.z));
	outPoints[5] = matrix.mulPoint4x3(Vec3(b.x, a.y, b.z));
	outPoints[6] = matrix.mulPoint4x3(Vec3(b.x, b.y, b.z));
	outPoints[7] = matrix.mulPoint4x3(Vec3(a.x, b.y, b.z));
}

template<class T> inline
void 
AABBox3_T<T>::getPoints(Vec3 outPoints[s_kVertexCount]) const 
{
	const auto& a = min;
	const auto& b = max;

	outPoints[0] = (Vec3(a.x, a.y, a.z));
	outPoints[1] = (Vec3(b.x, a.y, a.z));
	outPoints[2] = (Vec3(b.x, b.y, a.z));
	outPoints[3] = (Vec3(a.x, b.y, a.z));

	outPoints[4] = (Vec3(a.x, a.y, b.z));
	outPoints[5] = (Vec3(b.x, a.y, b.z));
	outPoints[6] = (Vec3(b.x, b.y, b.z));
	outPoints[7] = (Vec3(a.x, b.y, b.z));
}

template<class T> inline
void
AABBox3_T<T>::encapsulate(const Vec3& pt) 
{
	min = math::min(min, pt);
	max = math::max(max, pt);
}

template<class T> inline
void 
AABBox3_T<T>::encapsulate_CheckValid(const Vec3& pt)
{
	if (!isValid()) 
	{
		min = pt;
		max = pt;
	} else 
	{
		encapsulate(pt);
	}
}

template<class T> inline
AABBox3_T<T>
AABBox3_T<T>::makeExpanded(Vec3 outPoints[s_kVertexCount], const Mat4& matrix) const
{
	auto& pts = outPoints;
	getPoints(pts, matrix);

	auto o = AABBox3_T<T>{};
	for (size_t i = 0; i < 8; ++i)
	{
		const auto& pt = pts[i];
		o.encapsulate(pt);
	}
	o.getPoints(pts);		// get expanded points
	return o;
}

template<class T> inline
AABBox3_T<T>
AABBox3_T<T>::makeExpanded(const Mat4& matrix) const
{
	Vec3 pts[s_kVertexCount];
	return makeExpanded(pts, matrix);
}

template<class T> inline
bool
AABBox3_T<T>::isOverlapped(const AABBox3_T& b) const
{
	return (   (max.x >= b.min.x) && (min.x <= b.max.x)
			&& (max.y >= b.min.y) && (min.y <= b.max.y)
			&& (max.z >= b.min.z) && (min.z <= b.max.z));
}

template<class T> inline
bool
AABBox3_T<T>::isInside(const Vec3& pt) const
{
	return (   (pt.x >= min.x && pt.x <= max.x)
            && (pt.y >= min.y && pt.y <= max.y)
            && (pt.z >= min.z && pt.z <= max.z));
}

template<class T> inline 
typename AABBox3_T<T>::Vec3
AABBox3_T<T>::center() const
{ 
	return (Vec3{ max } + Vec3{ min }) / sCast<T>(2.0); 
}

template<class T> inline 
typename AABBox3_T<T>::Vec3
AABBox3_T<T>::size() const
{ 
	return (Vec3{ max } - Vec3{ min }); 
}

template<class T> inline
typename AABBox3_T<T>::Vec3
AABBox3_T<T>::halfSize() const
{ 
	return size() / sCast<T>(2.0); 
}

template<class T> inline 
typename AABBox3_T<T>::Rect2
AABBox3_T<T>::toRect2() const
{ 
	Rect2 o; 
	o.set(min.toVec2(), size().toVec2()); 
	return o; 
}

#endif

using AABBox3f_T = AABBox3_T<float>;
using AABBox3d_T = AABBox3_T<double>;

}
}
