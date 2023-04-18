#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/nmspMath.h"
#include "nmsp_math/primitive/nmspVec3.h"
#include "nmsp_math/primitive/nmspVec4.h"
#include "nmsp_math/primitive/nmspQuat4.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Mat4_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Mat4_T = glm::mat<4, 4, T, glm::lowp>;

template<class T> 
struct Mat4_Basic_Data_Glm : public Glm_Mat4_T<T>
{
public:
	using Base		= Glm_Mat4_T<T>;
	using Vec4		= Glm_Vec4_T<T>;

	using ElementType	= T;
	using SizeType		= NmspMathTraits::SizeType;
	using IndexType		= NmspMathTraits::IndexType;

public:
	Mat4_Basic_Data_Glm()
		: Base(	  Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec4{ T(0.0), T(0.0), T(0.0), T(0.0) } )
	{
	}

	Mat4_Basic_Data_Glm(const Base& rhs)
		: Base(rhs)
	{
	}
};

template<class T, class DATA = Mat4_Basic_Data_Glm<T> >
struct Mat4_Basic_Glm : public DATA
{
public:
	using Base		= DATA;
	using Mat4		= Mat4_Basic_Glm;
	using Vec4		= Vec4_T<T>;
	using Vec3		= Vec3_T<T>;
	using Quat4		= Quat4_T<T>;

	using Rect2		= /*Rect2_T<T>*/int;

	template<class T2> using Vec4_T		= Vec4_T<T2>;

	template<class T2, class DATA2> using Mat4_T = Mat4_Basic_Glm<T2, DATA2>;
	
	using ElementType	= typename Base::ElementType;
	using SizeType		= typename Base::SizeType;
	using IndexType		= typename Base::IndexType;

public:
	//using Base::cx;
	//using Base::cy;
	//using Base::cz;
	//using Base::cw;
	//using Base::_columns;
	//using Base::data;

public:
	static constexpr size_t s_kElementCount = 16;
	static constexpr size_t s_kRowCount		= 4;
	static constexpr size_t s_kColumnCount	= 4;

public:
	static Mat4 s_zero		();
	static Mat4 s_one		();
	static Mat4 s_identity	();

	template<class T2, class DATA2> static Mat4 s_cast(const Mat4_T<T2, DATA2>& rhs);

	static Mat4 s_translate	(const Vec3& t);
	static Mat4 s_rotate	(const Vec3& r);
	static Mat4 s_rotateX	(T rad);
	static Mat4 s_rotateY	(T rad);
	static Mat4 s_rotateZ	(T rad);
	static Mat4 s_scale		(const Vec3& r);
	static Mat4 s_shear		(const Vec3& r);

	static Mat4	s_quat		(const Quat4& q);

	static Mat4	s_TRS(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale);
	static Mat4	s_TRS(const Vec3 & translate, const Quat4& rotate, const Vec3 & scale);
	static Mat4	s_TS (const Vec3 & translate, const Vec3 & scale);

	static Mat4	s_perspective	(T fovy_rad, T aspect, T zNear, T zFar);
	static Mat4	s_ortho			(T left, T right, T bottom, T top, T zNear, T zFar);
	static Mat4	s_lookAt		(const Vec3 & eye, const Vec3 & aim, const Vec3 & up);

public:
	Mat4() = default;
	Mat4(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_);

	const Vec4&	col		(SizeType i) const;
		  Vec4	row		(SizeType i) const;
	void		setCol	(SizeType i, const Vec4& v);
	void		setRow	(SizeType i, const Vec4& v);
	void		set		(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_);
	
	bool	equals	(const Mat4& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0	(				  const T& epsilon = math::epsilon<T>()) const;

	Mat4 transpose()	const;

	T determinant3x3() const;

	Mat4 inverse			() const;
	Mat4 inverse3x3			() const;
	Mat4 inverse3x3Transpose() const;

	Vec4	mulPoint	(const Vec4& v) const;
	Vec3	mulPoint4x3	(const Vec3& v) const;	// faster than mulPoint but no projection
	Vec3	mulVector	(const Vec3& v) const;	// for vector (direction)
	
	Vec3	mulNormal				(const Vec3& v) const; // for normal non-uniform scale
	Vec3	unprojectPoint			(const Vec3& screenPos, const Rect2& viewport) const;
	Vec3	unprojectPointFromInv	(const Vec3& screenPos, const Rect2& viewport) const;

			Vec4&	operator[](IndexType i);
	const	Vec4&	operator[](IndexType i) const;

	Mat4 operator-() const;

	Mat4 operator+(T val) const;
	Mat4 operator-(T val) const;
	Mat4 operator*(T val) const;
	Mat4 operator/(T val) const;

	Mat4 operator+=(T val);
	Mat4 operator-=(T val);
	Mat4 operator*=(T val);
	Mat4 operator/=(T val);

	Mat4 operator+(const Mat4& rhs) const;
	Mat4 operator-(const Mat4& rhs) const;
	Mat4 operator*(const Mat4& rhs) const;
	Mat4 operator/(const Mat4& rhs) const;

	Mat4 operator+=(const Mat4& rhs);
	Mat4 operator-=(const Mat4& rhs);
	Mat4 operator*=(const Mat4& rhs);
	Mat4 operator/=(const Mat4& rhs);

	bool operator==(const Mat4& rhs) const;
	bool operator!=(const Mat4& rhs) const;

public:
	using Glm_Mat4 = typename DATA::Base;
	Mat4(const Glm_Mat4& rhs); // for glm only
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Mat4_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_zero		()
{
	return Mat4{ Vec4::s_zero(), Vec4::s_zero(), Vec4::s_zero(), Vec4::s_zero() };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_one		()
{
	return Mat4{ Vec4::s_one(), Vec4::s_one(), Vec4::s_one(), Vec4::s_one() };
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_cast(const Mat4_T<T2, DATA2>& rhs)
{
	return Mat4{ Vec4(rhs[0]), Vec4(rhs[1]), Vec4(rhs[2]), Vec4(rhs[3]) };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_identity()
{
	return Mat4{ 
		  Vec4(rhs[0])
		, Vec4(rhs[1])
		, Vec4(rhs[2])
		, Vec4(rhs[3])};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_translate(const Vec3& t)
{
	return glm::translate(t);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotate	(const Vec3& r)
{
	NMSP_ASSERT(false, "not yet support");
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateX	(T rad)
{
	NMSP_ASSERT(false, "not yet support");
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateY	(T rad)
{
	NMSP_ASSERT(false, "not yet support");
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateZ	(T rad)
{
	NMSP_ASSERT(false, "not yet support");
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_scale	(const Vec3& r)
{
	return glm::scale(r);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_shear	(const Vec3& r)
{
	NMSP_ASSERT(false, "not yet support");
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_quat		(const Quat4& q)
{
	return glm::toMat4(q);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TRS(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale)
{
	return s_translate(translate) * s_rotate(rotate) * s_scale(scale);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TRS(const Vec3& translate, const Quat4& rotate, const Vec3& scale)
{
	return s_translate(translate) * s_quat(rotate) * s_scale(scale);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TS (const Vec3 & translate, const Vec3 & scale)
{
	return s_translate(translate) * s_scale(scale);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_perspective	(T fovy_rad, T aspect, T zNear, T zFar)
{
	return glm::perspective(fovy_rad, aspect, zNear, zFar);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_ortho		(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return glm::ortho(left, right, bottom, top, zNear, zFar);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_lookAt		(const Vec3 & eye, const Vec3 & aim, const Vec3 & up)
{
	return glm::lookAt(eye, aim, up);
}

template<class T, class DATA> inline
Mat4_Basic_Glm<T, DATA>::Mat4_Basic_Glm(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_)
{
	set(cx_, cy_, cz_, cw_);
}

template<class T, class DATA> inline
const typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::col		(SizeType i) const
{
	return (*this)[i];
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec4	Mat4_Basic_Glm<T, DATA>::row		(SizeType i) const
{
	return Vec4{ (*this)[0][i], (*this)[1][i], (*this)[2][i], (*this)[3][i] };
}

template<class T, class DATA> inline
void Mat4_Basic_Glm<T, DATA>::setCol	(SizeType i, const Vec4& v)
{
	(*this)[i] = v;
}

template<class T, class DATA> inline
void Mat4_Basic_Glm<T, DATA>::setRow	(SizeType i, const Vec4& v)
{
	(*this)[0][i] = v[0];
	(*this)[1][i] = v[1];
	(*this)[2][i] = v[2];
	(*this)[3][i] = v[3];
}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::equals	(const Mat4& rhs, const T& epsilon) const
{
	return math::equals((*this)[0], rhs[0], epsilon)
		&& math::equals((*this)[1], rhs[1], epsilon)
		&& math::equals((*this)[2], rhs[2], epsilon)
		&& math::equals((*this)[3], rhs[3], epsilon);
}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::equals0	(const T& epsilon) const
{
	return math::equals0((*this)[0], epsilon)
		&& math::equals0((*this)[1], epsilon)
		&& math::equals0((*this)[2], epsilon)
		&& math::equals0((*this)[3], epsilon);
}


template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::transpose()	const
{
	return glm::transpose()
}

template<class T, class DATA> inline
T	Mat4_Basic_Glm<T, DATA>::determinant3x3() const
{
	_notYetSupported();
	return {};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse			() const
{
	return glm::inverse(*this);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse3x3			() const
{
	_notYetSupported();
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse3x3Transpose() const
{
	_notYetSupported();
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec4	Mat4_Basic_Glm<T, DATA>::mulPoint		(const Vec4& v) const
{
	return sCast<Vec4>(*this * v);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulPoint4x3	(const Vec3& v) const
{
	return mulPoint(Vec4{ v, 1.0 }).toVec3();
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulVector		(const Vec3& v) const
{
	return Vec3{ (*this)[0].toVec3() * v.x + (*this)[1].toVec3()* v.y + (*this)[2].toVec3()* v.z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulNormal		(const Vec3& v) const
{
	return this->inverse3x3Transpose().mulVector(v);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::unprojectPoint			(const Vec3& screenPos, const Rect2& viewport) const
{
	return inverse().unprojectPointFromInv(screenPos, viewport);
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::unprojectPointFromInv	(const Vec3& screenPos, const Rect2& viewport) const
{
	auto  tmp = Vec4(screenPos, 1);
	tmp.y = viewport.h - tmp.y; // y is down

	tmp.x = (tmp.x - viewport.x) / viewport.w * 2 - 1;
	tmp.y = (tmp.y - viewport.y) / viewport.h * 2 - 1;

	auto obj = mulPoint(tmp);
	return obj.toVec3();
}

template<class T, class DATA> inline
const	typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat4_Basic_Glm<T, DATA>::operator[]");
	return sCast<const	Vec4&>(Base::operator[](i));
}

template<class T, class DATA> inline
		typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat4_Basic_Glm<T, DATA>::operator[]");
	return sCast<		Vec4&>(Base::operator[](i));
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-()		const
{
	return Mat4{ -(*this)[0], -(*this)[1], -(*this)[2], -(*this)[3] };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+(T val)	const
{
	Vec4 v = {val, val, val, val};
	return Mat4{ (*this)[0] + v, (*this)[1] + v, (*this)[2] + v, (*this)[3] + v};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat4{ (*this)[0] - v, (*this)[1] - v, (*this)[2] - v, (*this)[3] - v };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat4{ (*this)[0] * v, (*this)[1] * v, (*this)[2] * v, (*this)[3] * v };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat4{ (*this)[0] / v, (*this)[1] / v, (*this)[2] / v, (*this)[3] / v };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] += val; (*this)[1] += val; (*this)[2] += val; (*this)[3] += val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] -= val; (*this)[1] -= val; (*this)[2] -= val; (*this)[3] -= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] *= val; (*this)[1] *= val; (*this)[2] *= val; (*this)[3] *= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] /= val; (*this)[1] /= val; (*this)[2] /= val; (*this)[3] /= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+(const Mat4& rhs)	const
{
	return Mat4{ (*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2], (*this)[3] + rhs[3] };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-(const Mat4& rhs)	const
{
	return Mat4{ (*this)[0] - rhs[0], (*this)[1] - rhs[1], (*this)[2] - rhs[2], (*this)[3] - rhs[3] };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*(const Mat4& rhs)	const
{
	return Mat4{ (*this)[0] * rhs[0], (*this)[1] * rhs[1], (*this)[2] * rhs[2], (*this)[3] * rhs[3] };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/(const Mat4& rhs)	const
{
	return Mat4{ (*this)[0] / rhs[0], (*this)[1] / rhs[1], (*this)[2] / rhs[2], (*this)[3] / rhs[3] };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+=(const Mat4& rhs)
{
	(*this)[0] += rhs[0];
	(*this)[1] += rhs[1];
	(*this)[2] += rhs[2];
	(*this)[3] += rhs[3];
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-=(const Mat4& rhs)
{
	(*this)[0] -= rhs[0];
	(*this)[1] -= rhs[1];
	(*this)[2] -= rhs[2];
	(*this)[3] -= rhs[3];
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*=(const Mat4& rhs)
{
	(*this)[0] *= rhs[0];
	(*this)[1] *= rhs[1];
	(*this)[2] *= rhs[2];
	(*this)[3] *= rhs[3];
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/=(const Mat4& rhs)
{
	(*this)[0] /= rhs[0];
	(*this)[1] /= rhs[1];
	(*this)[2] /= rhs[2];
	(*this)[3] /= rhs[3];
}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::operator==(const Mat4& rhs) const
{
	return equals(rhs);
}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::operator!=(const Mat4& rhs) const
{
	return !operator==();
}

template<class T, class DATA> inline
Mat4_Basic_Glm<T, DATA>::Mat4_Basic_Glm(const Glm_Mat4& rhs) // for glm only
	: Base(rhs)
{
	
}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
