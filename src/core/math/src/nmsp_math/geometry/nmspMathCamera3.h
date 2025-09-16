#pragma once

#include "nmspMathGeometry_Common.h"
#include "nmspMathRay3.h"
#include "nmspMathFrustum3.h"
#include "nmspMathRect2.h"
/*
references:
~ MathCamera3.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {
namespace math {

template<class T> struct Camera3_T;
using Camera3f_T = Camera3_T<float>;
using Camera3d_T = Camera3_T<double>;

#if 0
#pragma mark --- Camera3_T-Decl ---
#endif // 0
#if 1

template<class T>
struct Camera3_T
{
public:
	using Vec2		= Vec2_T<T>;
	using Vec3		= Vec3_T<T>;
	using Vec4		= Vec4_T<T>;
	using Mat4		= Mat4_T<T>;
	using Quat4		= Quat4_T<T>;
	using Rect2		= Rect2_T<T>;
	using Ray3		= Ray3_T<T>;
	using Frustum3	= Frustum3_T<T>;

public:
	Camera3_T();
	~Camera3_T();

public:
	void pan	(T x, T y);
	void orbit	(T x, T y);
	void move	(T x, T y, T z);
	void move	(const Vec3& v) { move(v.x, v.y, v.z); }

	void dolly	(T z);

	void setPos(T x, T y, T z)	{ setPos(Vec3(x,y,z)); }
	void setAim(T x, T y, T z)	{ setAim(Vec3(x,y,z)); }
	void setUp (T x, T y, T z)	{ setUp (Vec3(x,y,z)); }

	void setNearClip(T v)	{ _nearClip = v; }
	void setFarClip( T v)	{ _farClip	= v; }

	void setPos(const Vec3& pos)	{ _pos = pos; }
	void setAim(const Vec3& aim)	{ _aim = aim; }
	void setUp (const Vec3& up)		{ _up  = up;  }
	void setFov(const T& fov)		{ _fov = fov; }
	void setViewport(const Rect2& v) { _viewport = v; }

	void setPerspective();
	void setOrthographic(const T& orthScale = T(1.0));

public:
	Mat4	viewMatrix() const;
	Mat4	projMatrix() const;
	Mat4	viewProjMatrix() const { return projMatrix() * viewMatrix(); }

	const Vec3& pos() const		 { return _pos; }
	const Vec3& aim() const		 { return _aim; }
	const Vec3& up () const		 { return _up;  }
	const T&	fov() const		 { return _fov; }

	const T&		nearClip()		const { return _nearClip; }
	const T&		farClip()		const { return _farClip; }
	const Rect2&	viewport()		const { return _viewport; }
	T				aspectRatio()	const { return _viewport.h != 0 ? _viewport.w / _viewport.h : T(0); }
	T				orthoScale()	const { return _orthoScale; }
	
	Ray3	getRay(const Vec2& screenPos) const;

	Frustum3 frustum() const { Frustum3 o; o.setByViewProjMatrix(viewProjMatrix()); return o; };

	static T	invalidOrthographicScale()			{ return NumLimit<T>::lowest(); }
	bool		isOrthgraphicMode()			const	{ return !math::equals(_orthoScale, invalidOrthographicScale()); }

private:	
	T		_fov		= T(50.0);
	T		_nearClip	= T(0.1);
	T		_farClip	= T(10000.0);
	T		_orthoScale	= invalidOrthographicScale();
	Rect2	_viewport;
	Vec3	_pos {150, 150, 200};
	Vec3	_aim {0,0,0};
	Vec3	_up  {0,1,0};
};


#endif

#if 0
#pragma mark --- Camera3_T-Impl ---
#endif // 0
#if 1



#endif

}
}
