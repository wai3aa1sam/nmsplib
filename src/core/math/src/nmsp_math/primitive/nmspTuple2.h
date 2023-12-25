#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

namespace nmsp {

template<class T> struct Tuple2_T;
using Tuple2f_T = Tuple2_T<f32>;
using Tuple2d_T = Tuple2_T<f64>;
using Tuple2i_T = Tuple2_T<i32>;
using Tuple2u_T = Tuple2_T<u32>;

#if 0
#pragma mark --- Tuple2-Decl ---
#endif // 0
#if 1

template<class T>
struct Tuple2_T
{
public:
	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	static constexpr size_t s_kElementCount = 2;

public:
	union
	{
		struct { T x, y; };
		T data[s_kElementCount];
	};
public:
	static constexpr Tuple2_T s_zero();

	template<class T2> static constexpr Tuple2_T s_cast(const Tuple2_T<T2>& rhs);

public:
	Tuple2_T();
	Tuple2_T(T x_, T y_);

	void set	(T x_, T y_);
	void setAll	(T val);

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);
private:

};

template<class T>
void onFormat(fmt::format_context& ctx, const Tuple2_T<T>& v)
{
	formatTo(ctx, "Tuple2({}, {})", v.x, v.y);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Tuple2_T<NMSP_ARGS(T)> );

#endif



#if 0
#pragma mark --- Tuple2-Impl ---
#endif // 0
#if 1


template<class T> inline constexpr Tuple2_T<T> Tuple2_T<T>::s_zero() { return { sCast<T>(0), sCast<T>(0) }; }

template<class T> 
template<class T2> inline constexpr
typename Tuple2_T<T> Tuple2_T<T>::s_cast(const Tuple2_T<T2>& rhs)
{
	return Tuple2_T{ T(rhs.x), T(rhs.y) };
}

template<class T> inline
Tuple2_T<T>::Tuple2_T()
	: x(T(0.0)), y(T(0.0))
{

}


template<class T> inline
Tuple2_T<T>::Tuple2_T(T x_, T y_)
	: x(x_), y(y_)
{

}

template<class T> inline
void Tuple2_T<T>::set(T x_, T y_)
{
	this->x = x_;
	this->y = y_;
}

template<class T> inline
void Tuple2_T<T>::setAll(T val)
{
	this->x = val;
	this->y = val;
}

template<class T> inline
T	Tuple2_T<T>::operator[](SizeType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple2_T<T>::operator[]");
	return data[i];
}

template<class T> inline
T&	Tuple2_T<T>::operator[](SizeType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple2_T<T>::operator[]");
	return data[i];
}

#endif


}