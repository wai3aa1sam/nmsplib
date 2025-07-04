#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

#include "nmsp_math/primitive/nmspTuple4.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Vec4_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec4_T = glm::vec<4, T, RDS_MATH_GLM_QUALIFIER>;

template<class T>
struct Vec4_Basic_Data_Glm : public Glm_Vec4_T<T>
{
public:
	using Base = Glm_Vec4_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Vec4_Basic_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0), T(0.0))
	{
	}

	Vec4_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Vec4_Basic_Data_Glm<T> >
struct Vec4_Basic_Glm : public DATA
{
public:
	using Base = DATA;
	using Data = DATA;

	using Vec4		= Vec4_Basic_Glm;
	using Tuple4	= Tuple4_T<T>;

	using Tuple2	= Tuple2_T<T>;
	using Vec2		= Vec2_T<T>;

	using Tuple3	= Tuple3_T<T>;
	using Vec3		= Vec3_T<T>;

	template<class T2, class DATA2> using Vec4_T = Vec4_Basic_Glm<T2, DATA2>;

	using ElementType	= typename Base::ElementType;
	using SizeType		= typename Base::SizeType;
	using IndexType		= typename Base::IndexType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::w;
	using Base::data;

public:
	static constexpr size_t s_kElementCount = 4;

public:
	static Vec4 s_zero();
	static Vec4 s_one();
	static Vec4 s_forward();
	static Vec4 s_up();
	static Vec4 s_right();
	static Vec4 s_back();
	static Vec4 s_down();
	static Vec4 s_left();
	static Vec4 s_inf();
	static Vec4 s_negInf();

	template<class T2, class DATA2> static Vec4 s_cast(const Vec4_T<T2, DATA2>& rhs);

public:
	Vec4() = default;
	Vec4(T x_, T y_, T z_, T w_);
	Vec4(const Tuple4& r);
	Vec4(const Vec3& r, T w_);
	Vec4(const Vec2& r, T z_, T w_);
	Vec4(const Tuple2& a, const Tuple2& b);
	template<class T2, class DATA2> explicit Vec4(const Vec4_T<T2, DATA2>& rhs);

	operator Tuple4() const;

	void	set(T x_, T y_, T z_, T w_);
	void	set(const Tuple4& rhs);
	void	set(const Vec3& rhs, T w_);
	void	set(const Vec2& rhs, T z_, T w_);
	void	set(const Tuple2& a_, const Tuple2& b_);
	void	setAll(T val);

	bool	equals(const Vec4& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0(const T& epsilon = math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot			(const Vec4& rhs)		const;
	NMSP_NODISCARD Vec4		cross		(const Vec4& rhs)		const;
	NMSP_NODISCARD Vec4		reflect		(const Vec4& normal)	const;
	NMSP_NODISCARD Vec4		orthogonal	()						const;

	NMSP_NODISCARD T		distance	(const Vec4& rhs)	const;
	NMSP_NODISCARD T		sqrDistance	(const Vec4& rhs)	const;
	NMSP_NODISCARD T		magnitude	()					const;
	NMSP_NODISCARD T		sqrMagnitude()					const;
	NMSP_NODISCARD Vec4		normalize()						const;

	NMSP_NODISCARD Vec4		lerp	(const Vec4& b, T t)								const;
	NMSP_NODISCARD Vec4		slerp	(const Vec4& b, T t)								const;
	NMSP_NODISCARD Vec4		rotateTo(const Vec4& target, T maxRadDelta, T maxMagDelta)	const;

	NMSP_NODISCARD Vec2		xy()		const;
	NMSP_NODISCARD Vec2		xz()		const;
	NMSP_NODISCARD Vec2		yz()		const;

	NMSP_NODISCARD Vec3		xyz()		const;
	NMSP_NODISCARD Vec3		xy0()		const;
	NMSP_NODISCARD Vec3		x0z()		const;

	NMSP_NODISCARD Tuple4	toTuple4()	const;
	NMSP_NODISCARD Vec2		toVec2()	const;
	NMSP_NODISCARD Vec3		toVec3()	const;

	T	operator[](IndexType i) const;
	T&	operator[](IndexType i);

	Vec4 operator-() const;

	Vec4 operator+(T val) const;
	Vec4 operator-(T val) const;
	Vec4 operator*(T val) const;
	Vec4 operator/(T val) const;

	void operator+=(T val);
	void operator-=(T val);
	void operator*=(T val);
	void operator/=(T val);

	Vec4 operator+(const Vec4& rhs) const;
	Vec4 operator-(const Vec4& rhs) const;
	Vec4 operator*(const Vec4& rhs) const;
	Vec4 operator/(const Vec4& rhs) const;

	void operator+=(const Vec4& rhs);
	void operator-=(const Vec4& rhs);
	void operator*=(const Vec4& rhs);
	void operator/=(const Vec4& rhs);

	bool operator==(const Vec4& rhs) const;
	bool operator!=(const Vec4& rhs) const;


public:
	using Glm_Vec4 = typename DATA::Base;
	Vec4(const Glm_Vec4& rhs); // for glm only
	const Data& toData() const;
private:
	const Glm_Vec4& toGlm() const;
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec4_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_zero()
{
	return Vec4{ T(0), T(0), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_one()
{
	return Vec4{ T(1), T(1), T(1), T(1) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_forward()
{
	return Vec4{ T(0), T(0), T(1), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_up()
{
	return Vec4{ T(0), T(1), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_right()
{
	return Vec4{ T(1), T(0), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_back()
{
	return Vec4{ T(0), T(0), -T(1), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_down()
{
	return Vec4{ T(0), -T(1), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_left()
{
	return Vec4{ -T(1), T(0), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_inf()
{
	auto f = math::inf<T>();
	return Vec4{ f, f, f, f };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_negInf()
{
	return -s_inf();
}

template<class T, class DATA>
template<class T2, class DATA2> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::s_cast(const Vec4_T<T2, DATA2>& rhs)
{
	return Vec4{ T(rhs.x), T(rhs.y), T(rhs.z), T(rhs.w) };
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(T x_, T y_, T z_, T w_)
{
	set(x_, y_, z_, w_);
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Tuple4& rhs)
{
	set(rhs);
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Vec3& rhs, T w_)
{
	set(rhs, w_);
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Vec2& rhs, T z_, T w_)
{
	set(rhs, w_, z_);
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Tuple2& a, const Tuple2& b)
{
	set(a, b);
}

template<class T, class DATA>
template<class T2, class DATA2>  inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Vec4_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z), sCast<T>(rhs.w));
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::operator Tuple4() const 
{
	return toTuple4(); 
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::set(T x_, T y_, T z_, T w_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->w = w_;
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::set(const Tuple4& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::set(const Vec3& rhs, T w_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = w_;
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::set(const Vec2& rhs, T z_, T w_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = z_;
	this->w = w_;
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::set(const Tuple2& a_, const Tuple2& b_)
{
	this->x = a_.x;
	this->y = a_.y;
	this->z = b_.x;
	this->w = b_.y;
}

template<class T, class DATA> inline
void Vec4_Basic_Glm<T, DATA>::setAll(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T, class DATA> inline
bool Vec4_Basic_Glm<T, DATA>::equals(const Vec4& rhs, const T& epsilon) const
{
	return math::equals(x, rhs.x, epsilon)
		&& math::equals(y, rhs.y, epsilon)
		&& math::equals(z, rhs.z, epsilon)
		&& math::equals(w, rhs.w, epsilon);
}

template<class T, class DATA> inline
bool Vec4_Basic_Glm<T, DATA>::equals0(const T& epsilon) const
{
	return math::equals0(x, epsilon)
		&& math::equals0(y, epsilon)
		&& math::equals0(z, epsilon)
		&& math::equals0(w, epsilon);
}

template<class T, class DATA> inline
T										Vec4_Basic_Glm<T, DATA>::dot(const Vec4& rhs)		const
{
	return glm::dot(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::cross(const Vec4& rhs)		const
{
	return glm::cross(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::reflect(const Vec4& normal)	const
{
	return glm::reflect(toGlm(), normal.toGlm());
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::orthogonal()						const
{
	_notYetSupported()
		return {};
}

template<class T, class DATA> inline
T										Vec4_Basic_Glm<T, DATA>::distance(const Vec4& rhs)		const
{
	return glm::distance(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T										Vec4_Basic_Glm<T, DATA>::sqrDistance(const Vec4& rhs)		const
{
	return glm::distance2(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T Vec4_Basic_Glm<T, DATA>::magnitude()	const
{
	return glm::length(toGlm());
}

template<class T, class DATA> inline
T Vec4_Basic_Glm<T, DATA>::sqrMagnitude()	const
{
	return glm::length2(toGlm());
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4
Vec4_Basic_Glm<T, DATA>::normalize() const
{
	return glm::normalize(toGlm());
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::lerp(const Vec4& b, T t)									const
{
	return glm::lerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::slerp(const Vec4& b, T t)									const
{
	return glm::slerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::rotateTo(const Vec4& target, T maxRadDelta, T maxMagDelta)	const
{
	_notYetSupported()
		return {};
}

template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec2 Vec4_Basic_Glm<T, DATA>::xy() const		{ return Vec2(x,y); }
template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec2 Vec4_Basic_Glm<T, DATA>::xz() const		{ return Vec2(x,z); }
template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec2 Vec4_Basic_Glm<T, DATA>::yz() const		{ return Vec2(y,z); }

template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec3 Vec4_Basic_Glm<T, DATA>::xyz() const	{ return Vec3(x,y,z); }
template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec3 Vec4_Basic_Glm<T, DATA>::xy0() const	{ return Vec3(x,y,0); }
template<class T, class DATA> inline typename Vec4_Basic_Glm<T, DATA>::Vec3 Vec4_Basic_Glm<T, DATA>::x0z() const	{ return Vec3(x,0,z); }

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Tuple4	Vec4_Basic_Glm<T, DATA>::toTuple4()	const
{
	return Tuple4{ x, y, z, w };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec2		Vec4_Basic_Glm<T, DATA>::toVec2()	const
{
	return Vec2{ x, y };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec3		Vec4_Basic_Glm<T, DATA>::toVec3()	const
{
	return Vec3{ x, y, z } / w;
}

template<class T, class DATA> inline
T	Vec4_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec4_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
T& Vec4_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec4_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator-()		const
{
	return Vec4{ -x, -y, -z, -w };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator+(T val)	const
{
	return Vec4{ x + val, y + val, z + val, w + val };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator-(T val)	const
{
	return Vec4{ x - val, y - val, z - val, w - val };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator*(T val)	const
{
	return Vec4{ x * val, y * val, z * val, w * val };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator/(T val)	const
{
	return Vec4{ x / val, y / val, z / val, w / val };
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val; w += val;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val; w -= val;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val; w *= val;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator/=(T val)
{
	x /= val; y /= val; z /= val; w /= val;
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator+(const Vec4& rhs)	const
{
	return Vec4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator-(const Vec4& rhs)	const
{
	return Vec4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator*(const Vec4& rhs)	const
{
	return Vec4{ x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
}

template<class T, class DATA> inline
typename Vec4_Basic_Glm<T, DATA>::Vec4	Vec4_Basic_Glm<T, DATA>::operator/(const Vec4& rhs)	const
{
	return Vec4{ x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w };
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator+=(const Vec4& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator-=(const Vec4& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator*=(const Vec4& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w;
}

template<class T, class DATA> inline
void	Vec4_Basic_Glm<T, DATA>::operator/=(const Vec4& rhs)
{
	x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w;
}

template<class T, class DATA> inline
bool Vec4_Basic_Glm<T, DATA>::operator==(const Vec4& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Vec4_Basic_Glm<T, DATA>::operator!=(const Vec4& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Vec4_Basic_Glm<T, DATA>::Vec4_Basic_Glm(const Glm_Vec4& rhs) // for glm only
	: Base(rhs)
{

}

template<class T, class DATA> inline
const typename Vec4_Basic_Glm<T, DATA>::Data& Vec4_Basic_Glm<T, DATA>::toData() const
{
	return sCast<const Data&>(*this);
}

template<class T, class DATA> inline
const typename Vec4_Basic_Glm<T, DATA>::Glm_Vec4& Vec4_Basic_Glm<T, DATA>::toGlm() const
{
	return sCast<const Glm_Vec4&>(*this);
}

#endif
}
#endif // NMSP_MATH_BACKEND_GLM
