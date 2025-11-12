#pragma once

#include "nmspMathGeometry_Common.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- Rect2-Decl ---
#endif // 0
#if 1

template<class T> struct Rect2_T;
using Rect2f_T = Rect2_T<f32>;
using Rect2d_T = Rect2_T<f64>;
using Rect2i_T = Rect2_T<i32>;
using Rect2u_T = Rect2_T<u32>;

template<class T>
struct Rect2_T
{
public:
	using ElementType = T;
	using Vec2		= Vec2_T<T>;
	using Tuple2	= Tuple2_T<T>;

public:
	static const size_t s_kElementCount = 4;

public:
	union
	{
		struct { T x, y, w, h; };
		struct { Tuple2 pos, size; };
		T data[s_kElementCount];
	};
public:
	static constexpr Rect2_T s_zero();
	static constexpr Rect2_T s_one();
	static constexpr Rect2_T s_posZero_sizeOne();

public:
	Rect2_T() : pos(), size() {};
	Rect2_T(T x_, T y_, T w_, T h_);
	Rect2_T(const Tuple2& pos_, const Tuple2& size_);
	Rect2_T(const Vec2&   pos_, const Vec2&   size_);

	void set(T x_, T y_, T w_, T h_);
	void set(const Tuple2& pos_, const Tuple2& size_);
	void set(const Vec2&   pos_, const Vec2&   size_);

	T xMin() const;
	T yMin() const;

	T xMax() const;
	T yMax() const;

	Vec2 center()	const;
	Vec2 halfSize() const;
};

template<class T> inline
math::Rect2_T<T> toRect2_wh(const Vec2_T<T>& vec2)
{
	math::Rect2_T<T> o;
	o.w = vec2.x;
	o.h = vec2.y;
	return o;
}

template<class T> inline
math::Rect2_T<T> toRect2_wh(const Tuple2_T<T>& tuple2)
{
	math::Rect2_T<T> o;
	o.w = tuple2.x;
	o.h = tuple2.y;
	return o;
}

template<class T> inline
math::Rect2_T<T> toRect2_xy(const Vec2_T<T>& vec2)
{
	math::Rect2_T<T> o;
	o.x = vec2.x;
	o.y = vec2.y;
	return o;
}

template<class T> inline
math::Rect2_T<T> toRect2_xy(const Tuple2_T<T>& tuple2)
{
	math::Rect2_T<T> o;
	o.x = tuple2.x;
	o.y = tuple2.y;
	return o;
}

#endif

#if 0
#pragma mark --- Rect2-Impl ---
#endif // 0
#if 1

template<class T> inline constexpr Rect2_T<T> Rect2_T<T>::s_zero()					{ return Rect2_T<T>{ sCast<T>(0), sCast<T>(0), sCast<T>(0), sCast<T>(0) }; }
template<class T> inline constexpr Rect2_T<T> Rect2_T<T>::s_one()					{ return Rect2_T<T>{ sCast<T>(1), sCast<T>(1), sCast<T>(1), sCast<T>(1) }; }
template<class T> inline constexpr Rect2_T<T> Rect2_T<T>::s_posZero_sizeOne()		{ return Rect2_T<T>{ sCast<T>(0), sCast<T>(0), sCast<T>(1), sCast<T>(1) }; }		

template<class T> inline 
Rect2_T<T>::Rect2_T(T x_, T y_, T w_, T h_)
{
	set(x_, y_, w_, h_);
}

template<class T> inline 
Rect2_T<T>::Rect2_T(const Tuple2& pos_, const Tuple2& size_)
{
	set(pos_, size_);
}

template<class T> inline 
Rect2_T<T>::Rect2_T(const Vec2& pos_, const Vec2& size_)
{
	set(pos_, size_);
}

template<class T> inline 
void 
Rect2_T<T>::set(T x_, T y_, T w_, T h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

template<class T> inline 
void 
Rect2_T<T>::set(const Tuple2& pos_, const Tuple2& size_)
{
	pos		= pos_;
	size	= size_;
}

template<class T> inline 
void 
Rect2_T<T>::set(const Vec2& pos_, const Vec2& size_)
{
	pos		=  pos_.toTuple2();
	size	= size_.toTuple2();
}

template<class T> inline 
T 
Rect2_T<T>::xMin() const
{
	return x;
}

template<class T> inline 
T 
Rect2_T<T>::yMin() const
{
	return y;
}

template<class T> inline 
T 
Rect2_T<T>::xMax() const
{
	return x + w;
}

template<class T> inline 
T 
Rect2_T<T>::yMax() const
{
	return y + h;
}

template<class T> inline 
typename Rect2_T<T>::Vec2	
Rect2_T<T>::center() const
{ 
	return Vec2{ pos } + halfSize(); 
}

template<class T> inline 
typename Rect2_T<T>::Vec2	
Rect2_T<T>::halfSize() const
{ 
	return Vec2{ size } / sCast<T>(2.0); 
}


#endif

}
}
