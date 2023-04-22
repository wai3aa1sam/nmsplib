#pragma once

#include "nmsp_os/common/nmsp_os_common.h"


namespace nmsp {

#if 0
#pragma mark --- WindowRect2-Decl ---
#endif // 0
#if 1

template<class T>
struct WindowVec2_T
{
public:
	using Vec2 = WindowVec2_T;

	using ElementType	= T;
	using SizeType		= OsTraits::SizeType;
	using IndexType		= OsTraits::IndexType;

public:
	static const SizeType s_kElementCount = 2;

public:
	union
	{
		T x, y;
		T data[s_kElementCount];
	};

public:
	static Vec2 s_zero		();
	static Vec2 s_one		();
	
public:
	WindowVec2_T() = default;
	WindowVec2_T(T x_, T y_);

	void	set				(T x_, T y_);
	void	setAll			(T val);

	Vec2 operator+(T val) const;
	Vec2 operator-(T val) const;
	Vec2 operator*(T val) const;
	Vec2 operator/(T val) const;

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator/(const Vec2& rhs) const;
};

template<class T>
struct WindowRect2_T
{
public:
	using ElementType = T;
	using Vec2 = WindowVec2_T<T>;
public:
	static const size_t s_kElementCount = 4;

public:
	union
	{
		T x, y, w, h;
		Vec2 pos, size;
		T data[s_kElementCount];
	};

public:
	WindowRect2_T() = default;
	WindowRect2_T(T x_, T y_, T w_, T h_);
	WindowRect2_T(const Vec2& pos_, const Vec2& size_);

	void set(T x_, T y_, T w_, T h_);
	void set(const Vec2& pos_, const Vec2& size_);

	T xMin() const;
	T yMin() const;

	T xMax() const;
	T yMax() const;
};

#endif

#if 0
#pragma mark --- WindowVec2-Impl ---
#endif // 0
#if 1

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::s_zero()
{
	return Vec2(0.0, 0.0);
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::s_one()
{
	return Vec2(1.0, 1.0);
}

template<class T> inline
WindowVec2_T<T>::WindowVec2_T(T x_, T y_)
{
	set(x_, y_);
}

template<class T> inline 
void WindowVec2_T<T>::set(T x_, T y_)
{
	x = x_;
	y = y_;
}

template<class T> inline 
void WindowVec2_T<T>::setAll(T val)
{
	x = val;
	y = val;
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator+(T val) const
{
	return Vec2{ x + val, y + val };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator-(T val) const
{
	return Vec2{ x - val, y - val };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator*(T val) const
{
	return Vec2{ x * val, y * val };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator/(T val) const
{
	return Vec2{ x / val, y / val };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator+(const Vec2& rhs) const
{
	return Vec2{ x + rhs.x, y + rhs.y };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator-(const Vec2& rhs) const
{
	return Vec2{ x - rhs.x, y - rhs.y };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator*(const Vec2& rhs) const
{
	return Vec2{ x * rhs.x, y * rhs.y };
}

template<class T> inline 
typename WindowVec2_T<T>::Vec2 WindowVec2_T<T>::operator/(const Vec2& rhs) const
{
	return Vec2{ x / rhs.x, y / rhs.y };
}

#endif


#if 0
#pragma mark --- WindowRect2-Impl ---
#endif // 0
#if 1

template<class T> inline 
WindowRect2_T<T>::WindowRect2_T(T x_, T y_, T w_, T h_)
{
	set(x_, y_, w_, h_);
}

template<class T> inline 
WindowRect2_T<T>::WindowRect2_T(const Vec2& pos_, const Vec2& size_)
{
	set(pos_, size_);
}

template<class T> inline 
void WindowRect2_T<T>::set(T x_, T y_, T w_, T h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
}

template<class T> inline 
void WindowRect2_T<T>::set(const Vec2& pos_, const Vec2& size_)
{
	pos		= pos_;
	size	= size_;
}

template<class T> inline 
T WindowRect2_T<T>::xMin() const
{
	return x;
}

template<class T> inline 
T WindowRect2_T<T>::yMin() const
{
	return y;
}

template<class T> inline 
T WindowRect2_T<T>::xMax() const
{
	return x + w;
}

template<class T> inline 
T WindowRect2_T<T>::yMax() const
{
	return y + h;
}


#endif


}
