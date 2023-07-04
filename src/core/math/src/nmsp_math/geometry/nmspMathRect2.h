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
	using Vec2 = Vec2_T<T>;
    
public:
	static const size_t s_kElementCount = 4;

public:
	union
	{
		struct { T x, y, w, h; };
		struct { Vec2 pos, size; };
		T data[s_kElementCount];
	};

public:
	Rect2_T() = default;
	Rect2_T(T x_, T y_, T w_, T h_);
	Rect2_T(const Vec2& pos_, const Vec2& size_);

	void set(T x_, T y_, T w_, T h_);
	void set(const Vec2& pos_, const Vec2& size_);

	T xMin() const;
	T yMin() const;

	T xMax() const;
	T yMax() const;
};

#endif

#if 0
#pragma mark --- Rect2-Impl ---
#endif // 0
#if 1


template<class T> inline 
Rect2_T<T>::Rect2_T(T x_, T y_, T w_, T h_)
{
	set(x_, y_, w_, h_);
}

template<class T> inline 
Rect2_T<T>::Rect2_T(const Vec2& pos_, const Vec2& size_)
{
	set(pos_, size_);
}

template<class T> inline 
void Rect2_T<T>::set(T x_, T y_, T w_, T h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

template<class T> inline 
void Rect2_T<T>::set(const Vec2& pos_, const Vec2& size_)
{
	pos		= pos_;
	size	= size_;
}

template<class T> inline 
T Rect2_T<T>::xMin() const
{
	return x;
}

template<class T> inline 
T Rect2_T<T>::yMin() const
{
	return y;
}

template<class T> inline 
T Rect2_T<T>::xMax() const
{
	return x + w;
}

template<class T> inline 
T Rect2_T<T>::yMax() const
{
	return y + h;
}


#endif

}
}
