#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

#include "nmsp_math/primitive/nmspTuple2.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Vec2_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Vec2_T = glm::vec<2, T, glm::lowp>;

template<class T> 
struct Vec2_Basic_Data_Glm : public Glm_Vec2_T<T>
{
public:
	using Base		= Glm_Vec2_T<T>;

	using ElementType	= T;
	using SizeType		= NmspMathTraits::SizeType;
	using IndexType		= NmspMathTraits::IndexType;

public:
	Vec2_Basic_Data_Glm()
		: Base(T(0.0), T(0.0))
	{
	}

	Vec2_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Vec2_Basic_Data_Glm<T> >
struct Vec2_Basic_Glm : public DATA
{
public:
	using Base = DATA;
	using Data = DATA;

	using Vec2		= Vec2_Basic_Glm;
	using Tuple2	= Tuple2_T<T>;

	template<class T2, class DATA2> using Vec2_T = Vec2_Basic_Glm<T2, DATA2>;

	using ElementType	= typename Base::ElementType;
	using SizeType		= typename Base::SizeType;
	using IndexType		= typename Base::IndexType;

public:
	using Base::x;
	using Base::y;
	using Base::data;

public:
	static constexpr size_t s_kElementCount = 2;

public:
	static Vec2 s_zero		();
	static Vec2 s_one		();
	static Vec2 s_up		();
	static Vec2 s_right		();
	static Vec2 s_down		();
	static Vec2 s_left		();
	static Vec2 s_inf		();
	static Vec2 s_negInf	();

	template<class T2, class DATA2> static Vec2 s_cast(const Vec2_T<T2, DATA2>& rhs);

public:
	Vec2() = default;
	Vec2(T x_, T y_);
	Vec2(const Tuple2& r);
	template<class T2, class DATA2> explicit Vec2(const Vec2_T<T2, DATA2>& rhs);

	void	set				(T x_, T y_);
	void	set				(const Tuple2& rhs);
	void	setAll			(T val);

	bool	equals	(const Vec2& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0	(				  const T& epsilon = math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot			(const Vec2& rhs)	const;
	NMSP_NODISCARD Vec2		cross		(const Vec2& rhs)	const;
	NMSP_NODISCARD Vec2		reflect		(const Vec2& normal)const;
	NMSP_NODISCARD Vec2		orthogonal	()					const;

	NMSP_NODISCARD T		distance	(const Vec2& rhs)	const;
	NMSP_NODISCARD T		sqrDistance	(const Vec2& rhs)	const;
	NMSP_NODISCARD T		magnitude	()					const;
	NMSP_NODISCARD T		sqrMagnitude()					const;
	NMSP_NODISCARD T		normalize	()					const;

	NMSP_NODISCARD Vec2		lerp	(const Vec2& b, T t)								const;
	NMSP_NODISCARD Vec2		slerp	(const Vec2& b, T t)								const;
	NMSP_NODISCARD Vec2		rotateTo(const Vec2& target, T maxRadDelta, T maxMagDelta)	const;

	T	operator[](IndexType i) const;
	T&	operator[](IndexType i);

	Vec2 operator-() const;

	Vec2 operator+(T val) const;
	Vec2 operator-(T val) const;
	Vec2 operator*(T val) const;
	Vec2 operator/(T val) const;

	void operator+=(T val);
	void operator-=(T val);
	void operator*=(T val);
	void operator/=(T val);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator/(const Vec2& rhs) const;

	void operator+=(const Vec2& rhs);
	void operator-=(const Vec2& rhs);
	void operator*=(const Vec2& rhs);
	void operator/=(const Vec2& rhs);

	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;

public:
	using Glm_Vec2 = typename DATA::Base;
	Vec2(const Glm_Vec2& rhs); // for glm only
	const Data& toData() const;
private:
	const Glm_Vec2& toGlm() const;
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Vec2_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_zero		()
{
	return Vec2{ T(0), T(0) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_one		()
{
	return Vec2{ T(1), T(1) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_up		()
{
	return Vec2{ T(0), T(1) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_right	()
{
	return Vec2{ T(1), T(0) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_down		()
{
	return Vec2{ T(0), -T(1) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_left		()
{
	return Vec2{ -T(1), T(0) };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_inf		()
{
	auto f = math::inf<T>();
	return Vec2{ f, f };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_negInf	()
{
	return -s_inf();
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::s_cast(const Vec2_T<T2, DATA2>& rhs)
{
	return Vec2{ T(rhs.x), T(rhs.y) };
}

template<class T, class DATA> inline
Vec2_Basic_Glm<T, DATA>::Vec2_Basic_Glm(T x_, T y_)
{
	set(x_, y_);
}

template<class T, class DATA> inline
Vec2_Basic_Glm<T, DATA>::Vec2_Basic_Glm(const Tuple2& rhs)
{
	set(rhs);
}

template<class T, class DATA> 
template<class T2, class DATA2>  inline
Vec2_Basic_Glm<T, DATA>::Vec2_Basic_Glm(const Vec2_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y));
}

template<class T, class DATA> inline
void Vec2_Basic_Glm<T, DATA>::set				(T x_, T y_)
{
	this->x = x_;
	this->y = y_;
}

template<class T, class DATA> inline
void Vec2_Basic_Glm<T, DATA>::set				(const Tuple2& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}

template<class T, class DATA> inline
void Vec2_Basic_Glm<T, DATA>::setAll			(T val)
{
	this->x = val;
	this->y = val;
}

template<class T, class DATA> inline
bool Vec2_Basic_Glm<T, DATA>::equals	(const Vec2& rhs, const T& epsilon) const
{
	return math::equals(x, rhs.x, epsilon)
		&& math::equals(y, rhs.y, epsilon);
}

template<class T, class DATA> inline
bool Vec2_Basic_Glm<T, DATA>::equals0	(				  const T& epsilon) const
{
	return math::equals0(x, epsilon)
		&& math::equals0(y, epsilon);
}

template<class T, class DATA> inline
T										Vec2_Basic_Glm<T, DATA>::dot		(const Vec2& rhs)		const
{
	return glm::dot(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::cross		(const Vec2& rhs)		const
{
	return glm::cross(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::reflect	(const Vec2& normal)	const
{
	return glm::reflect(toGlm(), normal.toGlm());
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::orthogonal	()						const
{
	_notYetSupported()
		return {};
}

template<class T, class DATA> inline
T										Vec2_Basic_Glm<T, DATA>::distance	(const Vec2& rhs)		const
{
	return glm::distance(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T										Vec2_Basic_Glm<T, DATA>::sqrDistance(const Vec2& rhs)		const
{
	return glm::distance2(toGlm(), rhs.toGlm());
}

template<class T, class DATA> inline
T Vec2_Basic_Glm<T, DATA>::magnitude	()	const
{
	return glm::length(toGlm());
}

template<class T, class DATA> inline
T Vec2_Basic_Glm<T, DATA>::sqrMagnitude	()	const
{
	return glm::length2(toGlm());
}

template<class T, class DATA> inline
T Vec2_Basic_Glm<T, DATA>::normalize		()	const
{
	return glm::normalize(toGlm());
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::lerp			(const Vec2& b, T t)									const
{
	return glm::lerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::slerp			(const Vec2& b, T t)									const
{
	return glm::slerp(toGlm(), b.toGlm(), t);
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::rotateTo		(const Vec2& target, T maxRadDelta, T maxMagDelta)	const
{
	_notYetSupported()
		return {};
}

template<class T, class DATA> inline
T	Vec2_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec2_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
T&	Vec2_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Vec2_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator-()		const
{
	return Vec2{ -x, -y };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator+(T val)	const
{
	return Vec2{ x + val, y + val };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator-(T val)	const
{
	return Vec2{ x - val, y - val };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator*(T val)	const
{
	return Vec2{ x * val, y * val };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator/(T val)	const
{
	return Vec2{ x / val, y / val };
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator/=(T val)
{
	x /= val; y /= val;
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator+(const Vec2& rhs)	const
{
	return Vec2{ x + rhs.x, y + rhs.y };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator-(const Vec2& rhs)	const
{
	return Vec2{ x - rhs.x, y - rhs.y };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator*(const Vec2& rhs)	const
{
	return Vec2{ x * rhs.x, y * rhs.y };
}

template<class T, class DATA> inline
typename Vec2_Basic_Glm<T, DATA>::Vec2	Vec2_Basic_Glm<T, DATA>::operator/(const Vec2& rhs)	const
{
	return Vec2{ x / rhs.x, y / rhs.y };
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator+=(const Vec2& rhs)
{
	x += rhs.x; y += rhs.y;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator-=(const Vec2& rhs)
{
	x -= rhs.x; y -= rhs.y;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator*=(const Vec2& rhs)
{
	x *= rhs.x; y *= rhs.y;
}

template<class T, class DATA> inline
void	Vec2_Basic_Glm<T, DATA>::operator/=(const Vec2& rhs)
{
	x /= rhs.x; y /= rhs.y;
}

template<class T, class DATA> inline
bool Vec2_Basic_Glm<T, DATA>::operator==(const Vec2& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Vec2_Basic_Glm<T, DATA>::operator!=(const Vec2& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Vec2_Basic_Glm<T, DATA>::Vec2_Basic_Glm(const Glm_Vec2& rhs) // for glm only
	: Base(rhs)
{

}

template<class T, class DATA> inline
const typename Vec2_Basic_Glm<T, DATA>::Data& Vec2_Basic_Glm<T, DATA>::toData() const
{
	return sCast<const Data&>(*this);
}

template<class T, class DATA> inline
const typename Vec2_Basic_Glm<T, DATA>::Glm_Vec2& Vec2_Basic_Glm<T, DATA>::toGlm() const
{
	return sCast<const Glm_Vec2&>(*this);
}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
