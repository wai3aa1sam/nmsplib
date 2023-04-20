#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

#include "nmsp_math/primitive/nmspVec4.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Quat4_T-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Quat4_T = glm::qua<T, glm::lowp>;

template<class T>
struct Quat4_Basic_Data_Glm : public Glm_Quat4_T<T>
{
public:
	using Base		= Glm_Quat4_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Quat4_Basic_Data_Glm()
		: Base(T(0.0), T(0.0), T(0.0), T(0.0))
	{
	}

	Quat4_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Quat4_Basic_Data_Glm<T> >
struct Quat4_Basic_Glm : public DATA
{
public:
	using Base = DATA;
	using Data = DATA;

	using Quat4		= Quat4_Basic_Glm;
	using Tuple4	= Tuple4_T<T>;
	using Vec2		= Vec2_T<T>;
	using Vec3		= Vec3_T<T>;

	template<class T2, class DATA2> using Quat4_T = Quat4_Basic_Glm<T2, DATA2>;

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
	static constexpr SizeType s_kElementCount = 4;

public:
	static Quat4 s_identity();
	static Quat4 s_angleAxis(T rad, const Vec3& axis);

	static Quat4 s_euler	(const Vec3& rad);
	static Quat4 s_eulerDeg	(const Vec3& deg);
	static Quat4 s_eulerX	(T rad);
	static Quat4 s_eulerY	(T rad);
	static Quat4 s_eulerZ	(T rad);

	static Quat4 s_eulerDegX(T deg);
	static Quat4 s_eulerDegY(T deg);
	static Quat4 s_eulerDegZ(T deg);

	static Quat4 s_fromAToB(const Vec3& from, const Vec3& to);

	template<class T2, class DATA2> static Quat4 s_cast(const Quat4_T<T2, DATA2>& rhs);

public:
	explicit constexpr Quat4() = default;
	explicit constexpr Quat4(T x_, T y_, T z_, T w_);
	template<class T2, class DATA2> explicit Quat4(const Quat4_T<T2, DATA2>& rhs);

	constexpr void set(T x_, T y_, T z_, T w_);

	bool	equals (const Quat4& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0(const Quat4& rhs, const T& epsilon = math::epsilon<T>()) const;

	T	 angle() const;
	Vec3 axis () const;

	void setEuler (const Vec3& rad);
	void setEulerX(T rad);
	void setEulerY(T rad);
	void setEulerZ(T rad);

	void setEulerDegX(T deg);
	void setEulerDegY(T deg);
	void setEulerDegZ(T deg);

	Vec3 euler () const;
	T	 eulerX() const;
	T	 eulerY() const;
	T	 eulerZ() const;

	Quat4 conjugate	() const;
	Quat4 inverse	() const;
	Quat4 normalize	() const;

	T dot(const Quat4& r) const;

	bool operator==(const Quat4& r) const;
	bool operator!=(const Quat4& r) const;

	Quat4 operator-() const;

	Quat4 operator*(const Quat4& r) const;
	Vec3  operator*(const Vec3&  v) const;

	Quat4 operator+(const Quat4& r) const;
	Quat4 operator-(const Quat4& r) const;

	Quat4 operator*(const T&    v) const;
	Quat4 operator/(const T&    v) const;

public:
	using Glm_Quat4 = typename DATA::Base;
	Quat4(const Glm_Quat4& rhs); // for glm only
	const Data& toData() const;
private:
	const Glm_Quat4& toGlm() const;
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Quat4_T-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_identity()
{
	return Quat4{ T(0), T(0), T(0), T(1) };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_angleAxis(T rad, const Vec3& axis)
{
	return glm::angleAxis(rad, axis);
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_euler(const Vec3& rad)
{
	Vec3 s, c;
	Math::sincos(r * T(0.5), s, c);
	return Quat4{
		s.x * c.y * c.z - c.x * s.y * s.z,
		c.x * s.y * c.z + s.x * c.y * s.z,
		c.x * c.y * s.z - s.x * s.y * c.z,
		c.x * c.y * c.z + s.x * s.y * s.z
	};
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerDeg(const Vec3& deg)
{
	return s_euler( math::radians(deg) );
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerX	(T rad)
{
	T s, c; Math::sincos(rad * T(0.5), s, c); return Quat4(s,0,0,c);
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerY	(T rad)
{
	T s, c; Math::sincos(rad * T(0.5), s, c); return Quat4(0,s,0,c);
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerZ	(T rad)
{
	T s, c; Math::sincos(rad * T(0.5), s, c); return Quat4(0,0,s,c);
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerDegX(T deg)
{
	return s_eulerX(math::radians(deg));
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerDegY(T deg)
{
	return s_eulerY(math::radians(deg));

}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_eulerDegZ(T deg)
{
	return s_eulerZ(math::radians(deg));
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_fromAToB(const Vec3& from, const Vec3& to)
{
	// Based on Stan Melax's article in Game Programming Gems
	// Copy, since cannot modify local
	Vec3 u = from.normalize();
	Vec3 v = to.normalize();
	
	const f32 cos_theta = u.dot(v);

	if (m::equals(cos_theta, T(1.0))) // both are same
	{
		return s_identity();
	}
	else if (m::equals(cos_theta, T(-1.0))) // exactly opposite
	{
		auto orth = u.orthogonal();
		return Quat4(orth.x, orth.y, orth.z, 0);
	}
	
	T offset	= m::sqrt(from.sqrMagnitude() * to.sqrMagnitude());
	Vec3 dir	= u.cross(v);
	Quat4 ret	= Quat4{ dir.x, dir.y, dir.z, cos_theta + offset };
	return ret.normalize();
}

template<class T, class DATA>
template<class T2, class DATA2> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::s_cast(const Quat4_Basic_Glm<T2, DATA2>& rhs)
{
	return Quat4{ T(rhs.x), T(rhs.y), T(rhs.z), T(rhs.w) };
}

template<class T, class DATA> inline constexpr
Quat4_Basic_Glm<T, DATA>::Quat4_Basic_Glm(T x_, T y_, T z_, T w_)
{
	set(x_, y_, z_, w_);
}

template<class T, class DATA>
template<class T2, class DATA2>  inline
Quat4_Basic_Glm<T, DATA>::Quat4_Basic_Glm(const Quat4_Basic_Glm<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z), sCast<T>(rhs.w));
}

template<class T, class DATA> inline constexpr
void Quat4_Basic_Glm<T, DATA>::set(T x_, T y_, T z_, T w_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->w = w_;
}

template<class T, class DATA> inline
bool Quat4_Basic_Glm<T, DATA>::equals(const Quat4& rhs, const T& epsilon) const
{
	return math::equals(x, rhs.x, epsilon)
		&& math::equals(y, rhs.y, epsilon)
		&& math::equals(z, rhs.z, epsilon)
		&& math::equals(w, rhs.w, epsilon);
}

template<class T, class DATA> inline
bool Quat4_Basic_Glm<T, DATA>::equals0(const Quat4& rhs, const T& epsilon) const
{
	return math::equals0(x, rhs.x, epsilon)
		&& math::equals0(y, rhs.y, epsilon)
		&& math::equals0(z, rhs.z, epsilon)
		&& math::equals0(w, rhs.w, epsilon);
}


template<class T, class DATA> inline
T										Quat4_Basic_Glm<T, DATA>::angle() const
{
	return glm::angle(toGlm());
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Vec3	Quat4_Basic_Glm<T, DATA>::axis () const
{
	return glm::axis(toGlm());
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEuler(const Vec3& rad)
{
	*this = Glm_Quat4{ rad.toData() };
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerX(T rad)
{
	*this = s_eulerX(rad);
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerY(T rad)
{
	*this = s_eulerY(rad);
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerZ(T rad)
{
	*this = s_eulerZ(rad);
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerDegX(T deg)
{
	*this = s_eulerX(math::radians(deg));
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerDegY(T deg)
{
	*this = s_eulerY(math::radians(deg));
}

template<class T, class DATA> inline
void Quat4_Basic_Glm<T, DATA>::setEulerDegZ(T deg)
{
	*this = s_eulerZ(math::radians(deg));
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Vec3	Quat4_Basic_Glm<T, DATA>::euler() const
{
	return Vec3(eulerX(), eulerY(), eulerZ()); // it is better
}

template<class T, class DATA> inline
T Quat4_Basic_Glm<T, DATA>::eulerX() const
{
	return math::atan2(T(2) * (y * z + w * x), w * w - x * x - y * y + z * z);
}

template<class T, class DATA> inline
T Quat4_Basic_Glm<T, DATA>::eulerY() const
{
	return math::asin(math::clamp(T(-2) * (x * z - w * y), T(-1), T(1)));
}

template<class T, class DATA> inline
T Quat4_Basic_Glm<T, DATA>::eulerZ() const
{
	return math::atan2(T(2) * (x * y + w * z), w * w + x * x - y * y - z * z);
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::conjugate	() const
{
	return Quat4{ -x, -y, -z, -w };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::inverse	() const
{
	return glm::inverse(toGlm());
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::normalize	() const
{
	return glm::normalize(toGlm());
}

template<class T, class DATA> inline
T	Quat4_Basic_Glm<T, DATA>::dot(const Quat4& r) const
{
	glm::dot(toGlm(), r.toGlm());
}

template<class T, class DATA> inline
bool Quat4_Basic_Glm<T, DATA>::operator==(const Quat4& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Quat4_Basic_Glm<T, DATA>::operator!=(const Quat4& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator-() const
{
	return Quat4{ -x, -y, -z, -w };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator*(const Quat4& r) const
{
	return toGlm() * r.toGlm();
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Vec3		Quat4_Basic_Glm<T, DATA>::operator*(const Vec3& v)  const
{
	return toGlm() * v.toData();
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator+(const Quat4& r) const
{
	return Quat4{ x + r.x, y + r.y, z + r.z, w + r.w };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator-(const Quat4& r) const
{
	return Quat4{ x - r.x, y - r.y, z - r.z, w - r.w };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator*(const T&    v) const
{
	return Quat4{ x * v, y * v, z * v, w * v };
}

template<class T, class DATA> inline
typename Quat4_Basic_Glm<T, DATA>::Quat4	Quat4_Basic_Glm<T, DATA>::operator/(const T&    v) const
{
	return Quat4{ x / v, y / v, z / v, w / v };
}

template<class T, class DATA> inline
Quat4_Basic_Glm<T, DATA>::Quat4_Basic_Glm(const Glm_Quat4& rhs) // for glm only
	: Base(rhs)
{

}

template<class T, class DATA> inline
const typename Quat4_Basic_Glm<T, DATA>::Data& Quat4_Basic_Glm<T, DATA>::toData() const
{
	return sCast<const Data&>(*this);
}

template<class T, class DATA> inline
const typename Quat4_Basic_Glm<T, DATA>::Glm_Quat4& Quat4_Basic_Glm<T, DATA>::toGlm() const
{
	return sCast<const Glm_Quat4&>(*this);
}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
