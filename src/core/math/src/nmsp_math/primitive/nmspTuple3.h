#pragma once

#include "../common/nmsp_math_common.h"

namespace nmsp {

template<class T> struct Tuple3_T;
using Tuple3f_T = Tuple3_T<f32>;
using Tuple3d_T = Tuple3_T<f64>;
using Tuple3i_T = Tuple3_T<i32>;
using Tuple3u_T = Tuple3_T<u32>;

#if 0
#pragma mark --- Tuple3-Decl ---
#endif // 0
#if 1

template<class T>
struct Tuple3_T
{
public:
	using ElementType	= T;
	using SizeType		= NmspMathTraits::SizeType;
	using IndexType		= NmspMathTraits::IndexType;

public:
	static constexpr size_t s_kElementCount = 3;

public:
	union
	{
		struct { T x, y, z; };
		T data[s_kElementCount];
	};
public:
	Tuple3_T();
	Tuple3_T(T x, T y, T z);

	void set	(T x, T y, T z);
	void setAll	(T val);

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);

private:

};

template<class T>
void onFormat(fmt::format_context& ctx, const Tuple3_T<T>& v)
{
	formatTo(ctx, "Tuple3({}, {}, {})", v.x, v.y, v.z);
}
NMSP_FORMATTER_T( NMSP_ARGS(class T), Tuple3_T<T> );

#endif



#if 0
#pragma mark --- Tuple3-Impl ---
#endif // 0
#if 1

template<class T> inline
Tuple3_T<T>::Tuple3_T()
	: x(T(0.0)), y(T(0.0)), z(T(0.0))
{

}


template<class T> inline
Tuple3_T<T>::Tuple3_T(T x, T y, T z)
	: x(x), y(y), z(z)
{

}

template<class T> inline
void Tuple3_T<T>::set(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T> inline
void Tuple3_T<T>::setAll(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T> inline
T	Tuple3_T<T>::operator[](SizeType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple3_T<T>::operator[]");
	return data[i];
}

template<class T> inline
T&	Tuple3_T<T>::operator[](SizeType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Tuple3_T<T>::operator[]");
	return data[i];
}


#endif


}