#pragma once

#include "../common/nmsp_math_common.h"

namespace nmsp {

template<class T> struct Tuple2_T;
using Tuple2i_T = Tuple2_T<i32>;
using Tuple2f_T = Tuple2_T<f32>;
using Tuple2d_T = Tuple2_T<f64>;

#if 0
#pragma mark --- Tuple2-Decl ---
#endif // 0
#if 1

template<class T>
struct Tuple2_T
{
public:
	using SizeType = i32;

public:
	static constexpr size_t s_kElementCount = 2;

public:
	union
	{
		struct { T x, y; };
		T data[s_kElementCount];
	};
public:
	Tuple2_T();
	Tuple2_T(T x, T y);

	void set	(T x, T y);
	void setAll	(T val);

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);
private:

};

template<class T>
void onFormat(fmt::format_context& ctx, const Tuple2_T<T>& v)
{
	formatTo(ctx, "({}, {})", v.x, v.y);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Tuple2_T<T> );

#endif



#if 0
#pragma mark --- Tuple2-Impl ---
#endif // 0
#if 1

template<class T> inline
Tuple2_T<T>::Tuple2_T()
	: x(T(0.0)), y(T(0.0))
{

}


template<class T> inline
Tuple2_T<T>::Tuple2_T(T x, T y)
	: x(x), y(y)
{

}

template<class T> inline
void Tuple2_T<T>::set(T x, T y)
{
	this->x = x;
	this->y = y;
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