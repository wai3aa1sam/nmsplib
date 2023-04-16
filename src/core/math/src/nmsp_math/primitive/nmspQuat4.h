#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/nmspMath.h"
#include "nmsp_math/primitive/nmspTuple4.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Quat4_T-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Quat4_T = glm::vec<4, T, glm::lowp>;

template<class T> 
struct Quat4_Basic_Data_Glm : public Glm_Quat4_T<T>
{
public:
	using Base		= Glm_Quat4_T<T>;
	using SizeType	= size_t;

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
struct Quat4_T : public DATA
{
public:
	using Base		= DATA;
	using Quat4		= Quat4_T;
	using Tuple4	= Tuple4_T<T>;
	using Vec2		= Vec2_T<T>;
	using Vec3		= Vec3_T<T>;

	template<class T2, class DATA2> using Quat4_T = Quat4_T<T2, DATA2>;

	using SizeType = typename Base::SizeType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::w;
	using Base::data;

public:
	static constexpr size_t s_kElementCount = 4;

public:
	static Quat4 s_zero		();
	static Quat4 s_one		();
	static Quat4 s_forward	();
	static Quat4 s_up		();
	static Quat4 s_right		();
	static Quat4 s_back		();
	static Quat4 s_down		();
	static Quat4 s_left		();
	static Quat4 s_inf		();
	static Quat4 s_negInf	();

	template<class T2, class DATA2> static Quat4 s_cast(const Quat4_T<T2, DATA2>& rhs);

public:
	Quat4() = default;
	Quat4(T x_, T y_, T z_, T w_);
	Quat4(const Tuple4& r);
	Quat4(const Vec3& r, T w_);
	Quat4(const Vec2& r, T z_, T w_);
	template<class T2, class DATA2> Quat4(const Quat4_T<T2, DATA2>& rhs);

	void	set				(T x_, T y_, T z_, T w_);
	void	set				(const Tuple4& rhs);
	void	set				(const Vec3& rhs, T w_);
	void	set				(const Vec2& rhs, T z_, T w_);
	void	setAll			(T val);

	bool	equals	(const Quat4& rhs, const T& epsilon = Math::epsilon<T>()) const;
	bool	equals0	(const Quat4& rhs, const T& epsilon = Math::epsilon<T>()) const;

	NMSP_NODISCARD T		dot				(const Quat4& rhs)									const;
	NMSP_NODISCARD Quat4		cross			(const Quat4& rhs)									const;
	NMSP_NODISCARD Quat4		reflect			(const Quat4& normal)								const;
	NMSP_NODISCARD Quat4		orthogonal		()													const;

	NMSP_NODISCARD T		distance		(const Quat4& rhs)									const;
	NMSP_NODISCARD T		sqrDistance		(const Quat4& rhs)									const;
	NMSP_NODISCARD T		magnitude		()													const;
	NMSP_NODISCARD T		sqrMagnitude	()													const;
	NMSP_NODISCARD T		normalize		()													const;

	NMSP_NODISCARD Quat4		lerp			(const Quat4& b, T t)								const;
	NMSP_NODISCARD Quat4		slerp			(const Quat4& b, T t)								const;
	NMSP_NODISCARD Quat4		rotateTo		(const Quat4& target, T maxRadDelta, T maxMagDelta)	const;

	NMSP_NODISCARD Tuple4	toTuple4()	const;
	NMSP_NODISCARD Vec2		toVec2()	const;
	NMSP_NODISCARD Vec3		toVec3()	const;

	T	operator[](SizeType i) const;
	T&	operator[](SizeType i);

	Quat4 operator-() const;

	Quat4 operator+(T val) const;
	Quat4 operator-(T val) const;
	Quat4 operator*(T val) const;
	Quat4 operator/(T val) const;

	Quat4 operator+=(T val);
	Quat4 operator-=(T val);
	Quat4 operator*=(T val);
	Quat4 operator/=(T val);

	Quat4 operator+(const Quat4& rhs) const;
	Quat4 operator-(const Quat4& rhs) const;
	Quat4 operator*(const Quat4& rhs) const;
	Quat4 operator/(const Quat4& rhs) const;

	Quat4 operator+=(const Quat4& rhs);
	Quat4 operator-=(const Quat4& rhs);
	Quat4 operator*=(const Quat4& rhs);
	Quat4 operator/=(const Quat4& rhs);

	bool operator==(const Quat4& rhs) const;
	bool operator!=(const Quat4& rhs) const;

private:
	using Glm_Quat4 = typename DATA::Base;
	Quat4(const Glm_Quat4& rhs); // for glm only

	/*operator Glm_Quat4<T>() const	{ return Glm_Quat4<T>{x, y, z}; }
	operator Glm_Quat4<T>()			{ return Glm_Quat4<T>{x, y, z}; }*/
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Quat4_T-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_zero		()
{
	return Quat4{ T(0), T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_one		()
{
	return Quat4{ T(1), T(1), T(1), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_forward	()
{
	return Quat4{ T(0), T(0), T(1), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_up		()
{
	return Quat4{ T(0), T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_right	()
{
	return Quat4{ T(1), T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_back		()
{
	return Quat4{ T(0), T(0), -T(1), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_down		()
{
	return Quat4{ T(0), -T(1), T(0), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_left		()
{
	return Quat4{ -T(1), T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_inf		()
{
	auto f = Math::inf<T>();
	return Quat4{ f, f, f, f};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_negInf	()
{
	return -s_inf();
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::s_cast(const Quat4_T<T2, DATA2>& rhs)
{
	return Quat4{ T(rhs.x), T(rhs.y), T(rhs.z), T(rhs.w)};
}

template<class T, class DATA> inline
Quat4_T<T, DATA>::Quat4_T(T x_, T y_, T z_, T w_)
{
	set(x_, y_, z_, w_);
}

template<class T, class DATA> inline
Quat4_T<T, DATA>::Quat4_T(const Tuple4& rhs)
{
	set(rhs);
}

template<class T, class DATA> inline
Quat4_T<T, DATA>::Quat4_T(const Vec3& rhs, T w_)
{
	set(rhs, w_);
}

template<class T, class DATA> inline
Quat4_T<T, DATA>::Quat4_T(const Vec2& rhs, T z_, T w_)
{
	set(rhs, w_, z_);
}

template<class T, class DATA> 
template<class T2, class DATA2>  inline
Quat4_T<T, DATA>::Quat4_T(const Quat4_T<T2, DATA2>& rhs)
{
	set(sCast<T>(rhs.x), sCast<T>(rhs.y), sCast<T>(rhs.z), sCast<T>(rhs.w));
}

template<class T, class DATA> inline
void Quat4_T<T, DATA>::set				(T x_, T y_, T z_, T w_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->w = w_;
}

template<class T, class DATA> inline
void Quat4_T<T, DATA>::set				(const Tuple4& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

template<class T, class DATA> inline
void Quat4_T<T, DATA>::set				(const Vec3& rhs, T w_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = w_;
}

template<class T, class DATA> inline
void Quat4_T<T, DATA>::set				(const Vec2& rhs, T z_, T w_)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = z_;
	this->w = w_;
}

template<class T, class DATA> inline
void Quat4_T<T, DATA>::setAll			(T val)
{
	this->x = val;
	this->y = val;
	this->z = val;
}

template<class T, class DATA> inline
bool Quat4_T<T, DATA>::equals	(const Quat4& rhs, const T& epsilon) const
{
	return Math::equals(x, rhs.x, epsilon)
		&& Math::equals(y, rhs.y, epsilon)
		&& Math::equals(z, rhs.z, epsilon)
		&& Math::equals(w, rhs.w, epsilon);
}

template<class T, class DATA> inline
bool Quat4_T<T, DATA>::equals0	(const Quat4& rhs, const T& epsilon) const
{
	return Math::equals0(x, rhs.x, epsilon)
		&& Math::equals0(y, rhs.y, epsilon)
		&& Math::equals0(z, rhs.z, epsilon)
		&& Math::equals0(w, rhs.w, epsilon);
}

template<class T, class DATA> inline
T										Quat4_T<T, DATA>::dot		(const Quat4& rhs)		const
{
	return glm::dot(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(rhs));
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::cross		(const Quat4& rhs)		const
{
	return glm::cross(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(rhs));
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::reflect	(const Quat4& normal)	const
{
	return glm::reflect(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(normal));
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::orthogonal	()						const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
}

template<class T, class DATA> inline
T										Quat4_T<T, DATA>::distance	(const Quat4& rhs)		const
{
	return glm::distance(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(rhs));
}

template<class T, class DATA> inline
T										Quat4_T<T, DATA>::sqrDistance(const Quat4& rhs)		const
{
	return glm::distance2(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(rhs));
}

template<class T, class DATA> inline
T Quat4_T<T, DATA>::magnitude	()	const
{
	return glm::length(sCast<Glm_Quat4>(*this));
}

template<class T, class DATA> inline
T Quat4_T<T, DATA>::sqrMagnitude	()	const
{
	return glm::length2(sCast<Glm_Quat4>(*this));
}

template<class T, class DATA> inline
T Quat4_T<T, DATA>::normalize		()	const
{
	return glm::normalize(sCast<Glm_Quat4>(*this));
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::lerp			(const Quat4& b, T t)									const
{
	return glm::lerp(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(b), t);
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::slerp			(const Quat4& b, T t)									const
{
	return glm::slerp(sCast<Glm_Quat4>(*this), sCast<Glm_Quat4>(b), t);
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::rotateTo		(const Quat4& target, T maxRadDelta, T maxMagDelta)	const
{
	NMSP_ASSERT(false, "not yet supported");
	return {};
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Tuple4	Quat4_T<T, DATA>::toTuple4()	const
{
	return Tuple4{ x, y, z, w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Vec2		Quat4_T<T, DATA>::toVec2()	const
{
	return Vec2{ x, y };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Vec3		Quat4_T<T, DATA>::toVec3()	const
{
	return Vec3{ x, y, z, T(0) };
}

template<class T, class DATA> inline
T	Quat4_T<T, DATA>::operator[](SizeType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Quat4_T<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
T&	Quat4_T<T, DATA>::operator[](SizeType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kElementCount, "Quat4_T<T, DATA>::operator[]");
	return Base::operator[](i);
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator-()		const
{
	return Quat4{ -x, -y, -z, -w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator+(T val)	const
{
	return Quat4{ x + val, y + val, z + val, w + val };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator-(T val)	const
{
	return Quat4{ x - val, y - val, z - val, w - val };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator*(T val)	const
{
	return Quat4{ x * val, y * val, z * val, w * val };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator/(T val)	const
{
	return Quat4{ x / val, y / val, z / val, w / val };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val; w += val;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val; w -= val;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val; w *= val;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator/=(T val)
{
	x /= val; y /= val; z /= val; w /= val;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator+(const Quat4& rhs)	const
{
	return Quat4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator-(const Quat4& rhs)	const
{
	return Quat4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator*(const Quat4& rhs)	const
{
	return Quat4{ x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator/(const Quat4& rhs)	const
{
	return Quat4{ x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w };
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator+=(const Quat4& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator-=(const Quat4& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator*=(const Quat4& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w;
}

template<class T, class DATA> inline
typename Quat4_T<T, DATA>::Quat4	Quat4_T<T, DATA>::operator/=(const Quat4& rhs)
{
	x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w;
}

template<class T, class DATA> inline
bool Quat4_T<T, DATA>::operator==(const Quat4& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Quat4_T<T, DATA>::operator!=(const Quat4& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Quat4_T<T, DATA>::Quat4_T(const Glm_Quat4& rhs) // for glm only
	: Base(rhs)
{

}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
