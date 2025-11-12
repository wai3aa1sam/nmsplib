#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

#include "nmsp_math/primitive/nmspVec2.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Vec3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec3_T = glm::vec<3, T, RDS_MATH_GLM_QUALIFIER>;

template<class T> 
struct Vec3_Basic_Data_Glm : public Glm_Vec3_T<T>
{
public:
	using Base		= Glm_Vec3_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Vec3_Basic_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0))
	{
	}

	Vec3_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Vec3_Basic_Data_Glm<T> >
struct Vec3_Basic_Glm : public DATA
{
public:
	using Base = DATA;
	using Data = DATA;

	using Vec3		= Vec3_Basic_Glm;
	using Tuple3	= Tuple3_T<T>;
	using Vec2		= Vec2_T<T>;

	template<class T2, class DATA2> using Vec3_T = Vec3_Basic_Glm<T2, DATA2>;

	using ElementType	= typename Base::ElementType;
	using SizeType		= typename Base::SizeType;
	using IndexType		= typename Base::IndexType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::data;

public:
	static constexpr size_t s_kElementCount = 3;

public:
	static Vec3 s_zero();
	static Vec3 s_one();
	static Vec3 s_forward();
	static Vec3 s_up();
	static Vec3 s_right();
	static Vec3 s_back();
	static Vec3 s_down();
	static Vec3 s_left();
	static Vec3 s_inf();
	static Vec3 s_negInf();

	static Vec3 s_xAxis();
	static Vec3 s_yAxis();
	static Vec3 s_zAxis();

	template<class T2, class DATA2> static Vec3 s_cast(const Vec3_T<T2, DATA2>& rhs);

public:
	Vec3() = default;
	Vec3(T x_, T y_, T z_);
	Vec3(const Tuple3& r);
	Vec3(const Vec2& r, T z_);
	template<class T2, class DATA2> explicit Vec3(const Vec3_T<T2, DATA2>& rhs);

	operator Tuple3() const;

	void	set				(T x_, T y_, T z_);
	void	set				(const Tuple3& rhs);
	void	set				(const Vec2& rhs, T z_);
	void	setAll			(T val);

	bool	equals	(const Vec3& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0	(				  const T& epsilon = math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot			(const Vec3& rhs)		const;
	NMSP_NODISCARD Vec3		cross		(const Vec3& rhs)		const;
	NMSP_NODISCARD Vec3		reflect		(const Vec3& normal)	const;
	NMSP_NODISCARD Vec3		orthogonal	()						const;

	NMSP_NODISCARD T		distance	(const Vec3& rhs)	const;
	NMSP_NODISCARD T		sqrDistance	(const Vec3& rhs)	const;
	NMSP_NODISCARD T		magnitude	()					const;
	NMSP_NODISCARD T		sqrMagnitude()					const;
	NMSP_NODISCARD Vec3		normalize	()					const;

	NMSP_NODISCARD Vec3		lerp		(const Vec3& b, T t)								const;
	NMSP_NODISCARD Vec3		slerp		(const Vec3& b, T t)								const;
	NMSP_NODISCARD Vec3		rotateTo	(const Vec3& target, T maxRadDelta, T maxMagDelta)	const;

	NMSP_NODISCARD Vec2		xy()		const;
	NMSP_NODISCARD Vec2		xz()		const;
	NMSP_NODISCARD Vec2		yz()		const;

	NMSP_NODISCARD Vec3		xyz()		const;
	NMSP_NODISCARD Vec3		xy0()		const;
	NMSP_NODISCARD Vec3		x0z()		const;

	NMSP_NODISCARD Tuple3	toTuple3()	const;
	NMSP_NODISCARD Vec2		toVec2()	const;

	T	operator[](IndexType i) const;
	T&	operator[](IndexType i);

	Vec3 operator-() const;

	Vec3 operator+(T val) const;
	Vec3 operator-(T val) const;
	Vec3 operator*(T val) const;
	Vec3 operator/(T val) const;

	void operator+=(T val);
	void operator-=(T val);
	void operator*=(T val);
	void operator/=(T val);

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator/(const Vec3& rhs) const;

	void operator+=(const Vec3& rhs);
	void operator-=(const Vec3& rhs);
	void operator*=(const Vec3& rhs);
	void operator/=(const Vec3& rhs);

	bool operator==(const Vec3& rhs) const;
	bool operator!=(const Vec3& rhs) const;

public:
	using Glm_Vec3 = typename DATA::Base;
	Vec3(const Glm_Vec3& rhs); // for glm only
	const Data& toData() const;
private:
	const Glm_Vec3& toGlm() const;
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec3_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_zero()
{
	return Vec3{ T(0), T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_one()
{
	return Vec3{ T(1), T(1), T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_forward()
{
	return Vec3{ T(0), T(0), T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_up()
{
	return Vec3{ T(0), T(1), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_right()
{
	return Vec3{ T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_back()
{
	return Vec3{ T(0), T(0), -T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_down()
{
	return Vec3{ T(0), -T(1), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_left()
{
	return Vec3{ -T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_inf()
{
	auto f = math::inf<T>();
	return Vec3{ f, f, f};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_negInf()
{
	return -s_inf();
}

template<class T, class DATA> inline typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_xAxis() { return Vec3{ 1.0, 0.0, 0.0 }; }
template<class T, class DATA> inline typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_yAxis() { return Vec3{ 0.0, 1.0, 0.0 }; }
template<class T, class DATA> inline typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_zAxis() { return Vec3{ 0.0, 0.0, 1.0 }; }

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_cast(const Vec3_T<T2, DATA2>& rhs)
{
	return Vec3{ T(rhs.x), T(rhs.y), T(rhs.z) };
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(T x_, T y_, T z_)
{
	set(x_, y_, z_);
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Tuple3& rhs)
{
	set(rhs);
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Vec2& rhs, T z_)
{
	set(rhs, z_);
}

template<class T, class DATA> 
template<class T2, class DATA2>  inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Vec3_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z));
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::operator Tuple3() const 
{
	return toTuple3(); 
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(T x_, T y_, T z_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(const Tuple3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(const Vec2& rhs, T z_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = z_;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::setAll			(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::equals	(const Vec3& rhs, const T& epsilon) const
{
	return math::equals(x, rhs.x, epsilon)
		&& math::equals(y, rhs.y, epsilon)
		&& math::equals(z, rhs.z, epsilon);
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::equals0	(				  const T& epsilon) const
{
	return math::equals0(x, epsilon)
		&& math::equals0(y, epsilon)
		&& math::equals0(z, epsilon);
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::dot		(const Vec3& rhs)		const
{
	return glm::dot(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::cross		(const Vec3& rhs)		const
{
	return glm::cross(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::reflect	(const Vec3& normal)	const
{
	return glm::reflect(toGlm(), normal.toGlm());
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::orthogonal	()						const
{
	T x0 = math::abs(this->x);
	T y0 = math::abs(this->y);
	T z0 = math::abs(this->z);

	Vec3 other = x0 < y0 ? (x0 < z0 ? s_xAxis() : s_zAxis()) : (y0 < z0 ? s_yAxis() : s_zAxis());
	return this->cross(other);
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::distance	(const Vec3& rhs)		const
{
	return glm::distance(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::sqrDistance(const Vec3& rhs)		const
{
	return glm::distance2(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T Vec3_Basic_Glm<T, DATA>::magnitude	()	const
{
	return glm::length(toGlm());
}

template<class T, class DATA> inline
T Vec3_Basic_Glm<T, DATA>::sqrMagnitude	()	const
{
	return glm::length2(toGlm());
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3 
Vec3_Basic_Glm<T, DATA>::normalize		()	const
{
	return glm::normalize(toGlm());
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::lerp			(const Vec3& b, T t)									const
{
	return glm::lerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::slerp			(const Vec3& b, T t)									const
{
	return glm::slerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::rotateTo		(const Vec3& target, T maxRadDelta, T maxMagDelta)	const
{
	_notYetSupported()
	return {};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec2		
Vec3_Basic_Glm<T, DATA>::xy()	const
{
	return Vec2{ x, y };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec2		
Vec3_Basic_Glm<T, DATA>::xz()	const
{
	return Vec2{ x, z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec2		
Vec3_Basic_Glm<T, DATA>::yz()	const
{
	return Vec2{ y, z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3		
Vec3_Basic_Glm<T, DATA>::xyz()	const
{
	return Vec3{ x, y, z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3		
Vec3_Basic_Glm<T, DATA>::xy0()	const
{
	return Vec3{ x, y, 0 };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3		
Vec3_Basic_Glm<T, DATA>::x0z()	const
{
	return Vec3{ x, 0, z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Tuple3	Vec3_Basic_Glm<T, DATA>::toTuple3()	const
{
	return Tuple3{ x, y, z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec2		Vec3_Basic_Glm<T, DATA>::toVec2()	const
{
	return Vec2{ x, y };
}

template<class T, class DATA> inline
T	Vec3_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec3_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
T&	Vec3_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec3_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator-()		const
{
	return Vec3{ -x, -y, -z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator+(T val)	const
{
	return Vec3{ x + val, y + val, z + val };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator-(T val)	const
{
	return Vec3{ x - val, y - val, z - val };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator*(T val)	const
{
	return Vec3{ x * val, y * val, z * val };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator/(T val)	const
{
	return Vec3{ x / val, y / val, z / val };
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator/=(T val)
{
	x /= val; y /= val; z /= val;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator+(const Vec3& rhs)	const
{
	return Vec3{ x + rhs.x, y + rhs.y, z + rhs.z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator-(const Vec3& rhs)	const
{
	return Vec3{ x - rhs.x, y - rhs.y, z - rhs.z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator*(const Vec3& rhs)	const
{
	return Vec3{ x * rhs.x, y * rhs.y, z * rhs.z };
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator/(const Vec3& rhs)	const
{
	return Vec3{ x / rhs.x, y / rhs.y, z / rhs.z };
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator+=(const Vec3& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator-=(const Vec3& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator*=(const Vec3& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z;
}

template<class T, class DATA> inline
void	Vec3_Basic_Glm<T, DATA>::operator/=(const Vec3& rhs)
{
	x /= rhs.x; y /= rhs.y; z /= rhs.z;
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::operator==(const Vec3& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::operator!=(const Vec3& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Glm_Vec3& rhs) // for glm only
	: Base(rhs)
{

}

template<class T, class DATA> inline
const typename Vec3_Basic_Glm<T, DATA>::Data& Vec3_Basic_Glm<T, DATA>::toData() const
{
	return sCast<const Data&>(*this);
}

template<class T, class DATA> inline
const typename Vec3_Basic_Glm<T, DATA>::Glm_Vec3& Vec3_Basic_Glm<T, DATA>::toGlm() const
{
	return sCast<const Glm_Vec3&>(*this);
}

#endif

#if 0
#pragma mark --- Vec3_Basic_Glm-Impl ---
#endif // 0
#if 1

namespace math 
{

template<class T, class DATA> inline
void 
sincos(const Vec3_Basic_Glm<T, DATA>& th, Vec3_Basic_Glm<T, DATA>& outSin, Vec3_Basic_Glm<T, DATA>& outCos) 
{
	math::sincos(th.x, outSin.x, outCos.x);
	math::sincos(th.y, outSin.y, outCos.y);
	math::sincos(th.z, outSin.z, outCos.z);
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>
min(const Vec3_Basic_Glm<T, DATA>& a, const Vec3_Basic_Glm<T, DATA>& b) 
{
	return Vec3_Basic_Glm<T, DATA>( math::min(a.x, b.x),
									math::min(a.y, b.y),
									math::min(a.z, b.z));
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>
max(const Vec3_Basic_Glm<T, DATA>& a, const Vec3_Basic_Glm<T, DATA>& b) 
{
	return Vec3_Basic_Glm<T, DATA>( math::max(a.x, b.x),
									math::max(a.y, b.y),
									math::max(a.z, b.z));
}

template<class T, class DATA> inline constexpr
Vec3_Basic_Glm<T, DATA> 
clamp(const Vec3_Basic_Glm<T, DATA>& v, const Vec3_Basic_Glm<T, DATA>& a, const Vec3_Basic_Glm<T, DATA>& b) 
{
	return Vec3_Basic_Glm<T, DATA>(	math::clamp(v.x, a.x, b.x),
									math::clamp(v.y, a.y, b.y),
									math::clamp(v.z, a.z, b.z));
}

template<class T, class DATA, class W> inline
Vec3_Basic_Glm<T, DATA> 
lerp(const Vec3_Basic_Glm<T, DATA>& a, const Vec3_Basic_Glm<T, DATA>& b, const W& weight) 
{
	return Vec3_Basic_Glm<T, DATA>(
		lerp(a.x, b.x, weight),
		lerp(a.y, b.y, weight),
		lerp(a.z, b.z, weight)
	);
}

}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
