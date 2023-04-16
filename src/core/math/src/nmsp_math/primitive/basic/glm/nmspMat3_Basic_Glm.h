#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/nmspMath.h"
#include "nmsp_math/primitive/nmspTuple3.h"

#include "nmsp_math/primitive/nmspVec2.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Mat3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Mat3_T = glm::vec<3, T, glm::lowp>;

template<class T> 
struct Mat3_Basic_Data_Glm : public Glm_Mat3_T<T>
{
public:
	using Base		= Glm_Mat3_T<T>;
	using SizeType	= size_t;
	using IndexType	= i32;

public:
	Mat3_Basic_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0))
	{
	}

	Mat3_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Mat3_Basic_Data_Glm<T> >
struct Mat3_Basic_Glm : public DATA
{
public:
	using Base		= DATA;
	using Mat3		= Mat3_Basic_Glm;
	using Tuple3	= Tuple3_T<T>;
	using Vec2		= Vec2_T<T>;

	template<class T2, class DATA2> using Mat3_T = Mat3_Basic_Glm<T2, DATA2>;

	using SizeType	= typename Base::SizeType;
	using IndexType = typename Base::IndexType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::data;

public:
	static constexpr SizeType s_kElementCount = 3;

public:
	static Mat3 s_zero		();
	static Mat3 s_one		();
	static Mat3 s_forward	();
	static Mat3 s_up		();
	static Mat3 s_right		();
	static Mat3 s_back		();
	static Mat3 s_down		();
	static Mat3 s_left		();
	static Mat3 s_inf		();
	static Mat3 s_negInf	();

	template<class T2, class DATA2> static Mat3 s_cast(const Mat3_T<T2, DATA2>& rhs);

public:
	Mat3() = default;
	Mat3(T x_, T y_, T z_);
	Mat3(const Tuple3& r);
	Mat3(const Vec2& r, T z_);
	template<class T2, class DATA2> Mat3(const Mat3_T<T2, DATA2>& rhs);

	void	set				(T x_, T y_, T z_);
	void	set				(const Tuple3& rhs);
	void	set				(const Vec2& rhs, T z_);
	void	setAll			(T val);

	bool	equals	(const Mat3& rhs, const T& epsilon = Math::epsilon<T>()) const;
	bool	equals0	(const Mat3& rhs, const T& epsilon = Math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot				(const Mat3& rhs)									const;
	NMSP_NODISCARD Mat3		cross			(const Mat3& rhs)									const;
	NMSP_NODISCARD Mat3		reflect			(const Mat3& normal)								const;
	NMSP_NODISCARD Mat3		orthogonal		()													const;

	NMSP_NODISCARD T		distance		(const Mat3& rhs)									const;
	NMSP_NODISCARD T		sqrDistance		(const Mat3& rhs)									const;
	NMSP_NODISCARD T		magnitude		()													const;
	NMSP_NODISCARD T		sqrMagnitude	()													const;
	NMSP_NODISCARD T		normalize		()													const;

	NMSP_NODISCARD Mat3		lerp			(const Mat3& b, T t)								const;
	NMSP_NODISCARD Mat3		slerp			(const Mat3& b, T t)								const;
	NMSP_NODISCARD Mat3		rotateTo		(const Mat3& target, T maxRadDelta, T maxMagDelta)	const;

	NMSP_NODISCARD Tuple3	toTuple3()	const;
	NMSP_NODISCARD Vec2		toVec2()	const;

	T	operator[](IndexType i) const;
	T&	operator[](IndexType i);

	Mat3 operator-() const;

	Mat3 operator+(T val) const;
	Mat3 operator-(T val) const;
	Mat3 operator*(T val) const;
	Mat3 operator/(T val) const;

	Mat3 operator+=(T val);
	Mat3 operator-=(T val);
	Mat3 operator*=(T val);
	Mat3 operator/=(T val);

	Mat3 operator+(const Mat3& rhs) const;
	Mat3 operator-(const Mat3& rhs) const;
	Mat3 operator*(const Mat3& rhs) const;
	Mat3 operator/(const Mat3& rhs) const;

	Mat3 operator+=(const Mat3& rhs);
	Mat3 operator-=(const Mat3& rhs);
	Mat3 operator*=(const Mat3& rhs);
	Mat3 operator/=(const Mat3& rhs);

	bool operator==(const Mat3& rhs) const;
	bool operator!=(const Mat3& rhs) const;

private:
	using Glm_Mat3 = typename DATA::Base;
	Mat3(const Glm_Mat3& rhs); // for glm only

	/*operator Glm_Mat3<T>() const	{ return Glm_Mat3<T>{x, y, z}; }
	operator Glm_Mat3<T>()			{ return Glm_Mat3<T>{x, y, z}; }*/
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Mat3_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_zero		()
{
	return Mat3{ T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_one		()
{
	return Mat3{ T(1), T(1), T(1)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_forward	()
{
	return Mat3{ T(0), T(0), T(1)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_up		()
{
	return Mat3{ T(0), T(1), T(0)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_right	()
{
	return Mat3{ T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_back		()
{
	return Mat3{ T(0), T(0), -T(1)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_down		()
{
	return Mat3{ T(0), -T(1), T(0)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_left		()
{
	return Mat3{ -T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_inf		()
{
	auto f = Math::inf<T>();
	return Mat3{ f, f, f};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_negInf	()
{
	return -s_inf();
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_cast(const Mat3_T<T2, DATA2>& rhs)
{
	return Mat3{ T(rhs.x), T(rhs.y), T(rhs.z) };
}

template<class T, class DATA> inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(T x_, T y_, T z_)
{
	set(x_, y_, z_);
}

template<class T, class DATA> inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(const Tuple3& rhs)
{
	set(rhs);
}

template<class T, class DATA> inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(const Vec2& rhs, T z_)
{
	set(rhs, z_);
}

template<class T, class DATA> 
template<class T2, class DATA2>  inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(const Mat3_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z));
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::set				(T x_, T y_, T z_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::set				(const Tuple3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::set				(const Vec2& rhs, T z_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = z_;
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::setAll			(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::equals	(const Mat3& rhs, const T& epsilon) const
{
	return Math::equals(x, rhs.x, epsilon)
		&& Math::equals(y, rhs.y, epsilon)
		&& Math::equals(z, rhs.z, epsilon);
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::equals0	(const Mat3& rhs, const T& epsilon) const
{
	return Math::equals0(x, rhs.x, epsilon)
		&& Math::equals0(y, rhs.y, epsilon)
		&& Math::equals0(z, rhs.z, epsilon);
}

template<class T, class DATA> inline
T										Mat3_Basic_Glm<T, DATA>::dot		(const Mat3& rhs)		const
{
	return glm::dot(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(rhs));
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::cross		(const Mat3& rhs)		const
{
	return glm::cross(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(rhs));
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::reflect	(const Mat3& normal)	const
{
	return glm::reflect(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(normal));
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::orthogonal	()						const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
}

template<class T, class DATA> inline
T										Mat3_Basic_Glm<T, DATA>::distance	(const Mat3& rhs)		const
{
	return glm::distance(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(rhs));
}

template<class T, class DATA> inline
T										Mat3_Basic_Glm<T, DATA>::sqrDistance(const Mat3& rhs)		const
{
	return glm::distance2(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(rhs));
}

template<class T, class DATA> inline
T Mat3_Basic_Glm<T, DATA>::magnitude	()	const
{
	return glm::length(sCast<Glm_Mat3>(*this));
}

template<class T, class DATA> inline
T Mat3_Basic_Glm<T, DATA>::sqrMagnitude	()	const
{
	return glm::length2(sCast<Glm_Mat3>(*this));
}

template<class T, class DATA> inline
T Mat3_Basic_Glm<T, DATA>::normalize		()	const
{
	return glm::normalize(sCast<Glm_Mat3>(*this));
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::lerp			(const Mat3& b, T t)									const
{
	return glm::lerp(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(b), t);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::slerp			(const Mat3& b, T t)									const
{
	return glm::slerp(sCast<Glm_Mat3>(*this), sCast<Glm_Mat3>(b), t);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::rotateTo		(const Mat3& target, T maxRadDelta, T maxMagDelta)	const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Tuple3	Mat3_Basic_Glm<T, DATA>::toTuple3()	const
{
	return Tuple3{ x, y, z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec2		Mat3_Basic_Glm<T, DATA>::toVec2()	const
{
	return Vec2{ x, y };
}

template<class T, class DATA> inline
T	Mat3_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Mat3_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
T&	Mat3_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Mat3_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-()		const
{
	return Mat3{ -x, -y, -z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+(T val)	const
{
	return Mat3{ x + val, y + val, z + val };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-(T val)	const
{
	return Mat3{ x - val, y - val, z - val };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*(T val)	const
{
	return Mat3{ x * val, y * val, z * val };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/(T val)	const
{
	return Mat3{ x / val, y / val, z / val };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/=(T val)
{
	x /= val; y /= val; z /= val;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+(const Mat3& rhs)	const
{
	return Mat3{ x + rhs.x, y + rhs.y, z + rhs.z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-(const Mat3& rhs)	const
{
	return Mat3{ x - rhs.x, y - rhs.y, z - rhs.z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*(const Mat3& rhs)	const
{
	return Mat3{ x * rhs.x, y * rhs.y, z * rhs.z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/(const Mat3& rhs)	const
{
	return Mat3{ x / rhs.x, y / rhs.y, z / rhs.z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+=(const Mat3& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-=(const Mat3& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*=(const Mat3& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/=(const Mat3& rhs)
{
	x /= rhs.x; y /= rhs.y; z /= rhs.z;
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::operator==(const Mat3& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::operator!=(const Mat3& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(const Glm_Mat3& rhs) // for glm only
	: Base(rhs)
{
	
}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
