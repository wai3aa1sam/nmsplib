#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/nmspMath.h"
#include "nmsp_math/primitive/nmspTuple3.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Vec3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec3_T = glm::vec<3, T, glm::lowp>;

template<class T> 
struct Vec3_Basic_Data_Glm : public Glm_Vec3_T<T>
{
public:
	using Base		= Glm_Vec3_T<T>;
	using SizeType	= size_t;

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

template<class T> class Vec2_T;
template<class T> class Vec4_T;

template<class T, class DATA = Vec3_Basic_Data_Glm<T> >
struct Vec3_Basic_Glm : public DATA
{
public:
	using Base		= DATA;
	using Vec3		= Vec3_Basic_Glm;
	using Tuple3	= Tuple3_T<T>;
	using Vec2		= Vec2_T<T>;
	using Vec4		= Vec4_T<T>;

	template<class T2, class DATA2> using Vec3_T = Vec3_Basic_Glm<T2, DATA2>;

	using SizeType = typename Base::SizeType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::data;

public:
	static constexpr size_t s_kElementCount = 3;

public:
	static Vec3 s_zero		();
	static Vec3 s_one		();
	static Vec3 s_forward	();
	static Vec3 s_up		();
	static Vec3 s_right		();
	static Vec3 s_back		();
	static Vec3 s_down		();
	static Vec3 s_left		();
	static Vec3 s_inf		();
	static Vec3 s_negInf	();

	template<class T2, class DATA2> static Vec3 s_cast(const Vec3_T<T2, DATA2>& rhs);

public:
	Vec3() = default;
	Vec3(T x_, T y_, T z_);
	Vec3(const Tuple3& r);
	Vec3(const Vec2& r, T z_);
	template<class T2, class DATA2> Vec3(const Vec3_T<T2, DATA2>& rhs);

	void	set				(T x_, T y_, T z_);
	void	set				(const Tuple3& r);
	void	set				(Vec2 v2, T z_);
	void	setAll			(T val);

	bool	equals	(const Vec3& rhs, T epsilon = Math::epsilon<T>()) const;
	bool	equals0	(const Vec3& rhs, T epsilon = Math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot				(const Vec3& rhs)											const;
	NMSP_NODISCARD Vec3		cross			(const Vec3& rhs)											const;
	NMSP_NODISCARD Vec3		reflect			(const Vec3& normal)										const;
	NMSP_NODISCARD Vec3		orthogonal		()															const;

	NMSP_NODISCARD T		distance		(const Vec3& rhs)											const;
	NMSP_NODISCARD T		sqrDistance		(const Vec3& rhs)											const;
	NMSP_NODISCARD T		magnitude		()															const;
	NMSP_NODISCARD T		sqrMagnitude	()															const;
	NMSP_NODISCARD T		normalize		()															const;

	NMSP_NODISCARD Vec3		lerp			(const Vec3& b, T t)									const;
	NMSP_NODISCARD Vec3		slerp			(const Vec3& b, T t)									const;
	NMSP_NODISCARD Vec3		rotateTo		(const Vec3& target, T maxRadDelta, T maxMagDelta)	const;

	NMSP_NODISCARD Tuple3	toTuple3()	const;
	NMSP_NODISCARD Vec2		toVec2()	const;
	NMSP_NODISCARD Vec4		toVec4()	const;

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);

	Vec3 operator-() const;

	Vec3 operator+(T val) const;
	Vec3 operator-(T val) const;
	Vec3 operator*(T val) const;
	Vec3 operator/(T val) const;

	Vec3 operator+=(T val);
	Vec3 operator-=(T val);
	Vec3 operator*=(T val);
	Vec3 operator/=(T val);

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator/(const Vec3& rhs) const;

	Vec3 operator+=(const Vec3& rhs);
	Vec3 operator-=(const Vec3& rhs);
	Vec3 operator*=(const Vec3& rhs);
	Vec3 operator/=(const Vec3& rhs);

	bool operator==(const Vec3& rhs) const;
	bool operator!=(const Vec3& rhs) const;

private:
	using Glm_Vec3 = typename DATA::Base;
	Vec3(const Glm_Vec3& rhs); // for glm only

	/*operator Glm_Vec3<T>() const	{ return Glm_Vec3<T>{x, y, z}; }
	operator Glm_Vec3<T>()			{ return Glm_Vec3<T>{x, y, z}; }*/
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec3_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_zero		()
{
	return Vec3{ T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_one		()
{
	return Vec3{ T(1), T(1), T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_forward	()
{
	return Vec3{ T(0), T(0), T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_up		()
{
	return Vec3{ T(0), T(1), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_right	()
{
	return Vec3{ T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_back		()
{
	return Vec3{ T(0), T(0), -T(1)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_down		()
{
	return Vec3{ T(0), -T(1), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_left		()
{
	return Vec3{ -T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_inf		()
{
	auto f = Math::inf<T>();
	return Vec3{ f, f, f};
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_negInf	()
{
	return -s_inf();
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::s_cast(const Vec3_T<T2, DATA2>& rhs)
{
	return Vec3{ T2(rhs.x), T2(rhs.y), T2(rhs.z) };
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(T x_, T y_, T z_)
{
	set(x_, y_, z_);
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Tuple3& r)
{
	set(r);
}

template<class T, class DATA> inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Vec2& r, T z_)
{
	set(r, z_);
}

template<class T, class DATA> 
template<class T2, class DATA2>  inline
Vec3_Basic_Glm<T, DATA>::Vec3_Basic_Glm(const Vec3_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z));
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(T x_, T y_, T z_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(const Tuple3& r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::set				(Vec2 v2, T z)
{
	this->x = r.x;
	this->y = r.y;
	this->z = z;
}

template<class T, class DATA> inline
void Vec3_Basic_Glm<T, DATA>::setAll			(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::equals	(const Vec3& rhs, T epsilon) const
{
	return Math::equals(x, rhs.x, epsilon)
		&& Math::equals(y, rhs.y, epsilon)
		&& Math::equals(z, rhs.z, epsilon);
}

template<class T, class DATA> inline
bool Vec3_Basic_Glm<T, DATA>::equals0	(const Vec3& rhs, T epsilon) const
{
	return Math::equals0(x, rhs.x, epsilon)
		&& Math::equals0(y, rhs.y, epsilon)
		&& Math::equals0(z, rhs.z, epsilon);
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::dot		(const Vec3& rhs)		const
{
	return glm::dot(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(rhs));
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::cross		(const Vec3& rhs)		const
{
	return glm::cross(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(rhs));
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::reflect	(const Vec3& normal)	const
{
	return glm::reflect(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(normal));
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::orthogonal	()						const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::distance	(const Vec3& rhs)		const
{
	return glm::distance(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(rhs));
}

template<class T, class DATA> inline
T										Vec3_Basic_Glm<T, DATA>::sqrDistance(const Vec3& rhs)		const
{
	return glm::distance2(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(rhs));
}

template<class T, class DATA> inline
T Vec3_Basic_Glm<T, DATA>::magnitude	()	const
{
	return glm::length(sCast<Glm_Vec3>(*this));
}

template<class T, class DATA> inline
T Vec3_Basic_Glm<T, DATA>::sqrMagnitude	()	const
{
	return glm::length2(sCast<Glm_Vec3>(*this));
}

template<class T, class DATA> inline
T Vec3_Basic_Glm<T, DATA>::normalize		()	const
{
	return glm::normalize(sCast<Glm_Vec3>(*this));
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::lerp			(const Vec3& b, T t)									const
{
	return glm::lerp(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(b), t);
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::slerp			(const Vec3& b, T t)									const
{
	return glm::slerp(sCast<Glm_Vec3>(*this), sCast<Glm_Vec3>(b), t);
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::rotateTo		(const Vec3& target, T maxRadDelta, T maxMagDelta)	const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
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
typename Vec3_Basic_Glm<T, DATA>::Vec4		Vec3_Basic_Glm<T, DATA>::toVec4()	const
{
	return Vec4{ x, y, z, T(0) };
}

template<class T, class DATA> inline
T	Vec3_Basic_Glm<T, DATA>::operator[](SizeType i) const
{
	return *(sCast<T*>(this) + i);
}

template<class T, class DATA> inline
T&	Vec3_Basic_Glm<T, DATA>::operator[](SizeType i)
{
	return *(sCast<T*>(this) + i);
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
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator/=(T val)
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
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator+=(const Vec3& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator-=(const Vec3& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator*=(const Vec3& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z;
}

template<class T, class DATA> inline
typename Vec3_Basic_Glm<T, DATA>::Vec3	Vec3_Basic_Glm<T, DATA>::operator/=(const Vec3& rhs)
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

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
