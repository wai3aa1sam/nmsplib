#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

namespace nmsp {

template<class T> struct Tuple4_T;
using Tuple4f_T = Tuple4_T<f32>;
using Tuple4d_T = Tuple4_T<f64>;
using Tuple4i_T = Tuple4_T<i32>;
using Tuple4u_T = Tuple4_T<u32>;

#if 0
#pragma mark --- Tuple4-Decl ---
#endif // 0
#if 1

template<class T>
struct Tuple4_T
{
public:
	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	static constexpr size_t s_kElementCount = 4;

public:
	union
	{
		struct { T x, y, z, w; };
		T data[s_kElementCount];
	};
public:
	Tuple4_T();
	Tuple4_T(T x_, T y_, T z_, T w_);

	void set	(T x_, T y_, T z_, T w_);
	void setAll	(T val);

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);

public:
	template<class JSON_SE> void onJsonIo(JSON_SE& se);

private:

};

template<class T> 
template<class JSON_SE> inline
void 
Tuple4_T<T>::onJsonIo(JSON_SE& se)
{
	NMSP_NAMED_FIXED_IO(se, x);
	NMSP_NAMED_FIXED_IO(se, y);
	NMSP_NAMED_FIXED_IO(se, z);
	NMSP_NAMED_FIXED_IO(se, w);
}

template<class T>
void onFormat(fmt::format_context& ctx, const Tuple4_T<T>& v)
{
	formatTo(ctx, "Tuple4({}, {}, {}, {})", v.x, v.y, v.z, v.w);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Tuple4_T<NMSP_ARGS(T)> );

#endif



#if 0
#pragma mark --- Tuple4-Impl ---
#endif // 0
#if 1

template<class T> inline
Tuple4_T<T>::Tuple4_T()
	: x(T(0.0)), y(T(0.0)), z(T(0.0)), w(T(0.0))
{

}


template<class T> inline
Tuple4_T<T>::Tuple4_T(T x_, T y_, T z_, T w_)
	: x(x_), y(y_), z(z_), w(w_)
{

}

template<class T> inline
void Tuple4_T<T>::set(T x_, T y_, T z_, T w_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->w = w_;
}

template<class T> inline
void Tuple4_T<T>::setAll(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
	this->w = val;
}

template<class T> inline
T	Tuple4_T<T>::operator[](SizeType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple4_T<T>::operator[]");
	return data[i];
}

template<class T> inline
T&	Tuple4_T<T>::operator[](SizeType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple4_T<T>::operator[]");
	return data[i];
}

#endif


}