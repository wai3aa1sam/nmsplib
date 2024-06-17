#pragma once

#include "nmsp_math/primitive/nmspMathPrimitve_Common.h"

#include "nmsp_math/primitive/nmspVec3.h"
#include "nmsp_math/primitive/nmspVec4.h"
#include "nmsp_math/primitive/nmspQuat4.h"

#if NMSP_MATH_BACKEND_GLM

namespace nmsp {
#if 0
#pragma mark --- Mat3_Basic_Glm-Decl ---
#endif // 0
#if 1

template<class T> using Glm_Mat3_T = glm::mat<3, 3, T, RDS_MATH_GLM_QUALIFIER>;

template<class T> 
struct Mat3_Basic_Data_Glm : public Glm_Mat3_T<T>
{
public:
	using Base		= Glm_Mat3_T<T>;
	using Vec4		= Glm_Vec4_T<T>;

	using ElementType	= T;
	using SizeType		= MathTraits::SizeType;
	using IndexType		= MathTraits::IndexType;

public:
	Mat3_Basic_Data_Glm()
		: Base(	  Vec3{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec3{ T(0.0), T(0.0), T(0.0), T(0.0) }
				, Vec3{ T(0.0), T(0.0), T(0.0), T(0.0) } )
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
	using Data		= DATA;
	using Base		= DATA;
	using Mat3		= Mat3_Basic_Glm;
	using Vec4		= Vec4_T<T>;
	using Vec3		= Vec3_T<T>;
	using Quat4		= Quat4_T<T>;

	using Rect2		= /*Rect2_T<T>*/int;

	template<class T2> using Vec4_T		= Vec4_T<T2>;

	template<class T2, class DATA2> using Mat3_T = Mat3_Basic_Glm<T2, DATA2>;
	
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
	static Mat3 s_zero		();
	static Mat3 s_one		();
	static Mat3 s_identity	();

	template<class T2, class DATA2> static Mat3 s_cast(const Mat3_T<T2, DATA2>& rhs);

	static Mat3 s_translate	(const Vec3& t);
	static Mat3 s_rotate	(const Vec3& rad);
	static Mat3 s_rotateX	(T rad);
	static Mat3 s_rotateY	(T rad);
	static Mat3 s_rotateZ	(T rad);
	static Mat3 s_scale		(const Vec3& r);
	static Mat3 s_shear		(const Vec3& r);

	static Mat3	s_quat		(const Quat4& q);

	static Mat3	s_TRS(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale);
	static Mat3	s_TRS(const Vec3 & translate, const Quat4& rotate, const Vec3 & scale);
	static Mat3	s_TS (const Vec3 & translate, const Vec3 & scale);

	static Mat3	s_perspective	(T fovy_rad, T aspect, T zNear, T zFar);
	static Mat3	s_ortho			(T left, T right, T bottom, T top, T zNear, T zFar);
	static Mat3	s_lookAt		(const Vec3 & eye, const Vec3 & aim, const Vec3 & up);

public:
	Mat3() = default;
	Mat3(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_);

	void set(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_);

	const Vec4&	col		(IndexType i) const;
		  Vec4	row		(IndexType i) const;
	void		setCol	(IndexType i, const Vec4& v);
	void		setRow	(IndexType i, const Vec4& v);
	
	bool	equals	(const Mat3& rhs, const T& epsilon = math::epsilon<T>()) const;
	bool	equals0	(				  const T& epsilon = math::epsilon<T>()) const;

	Mat3 transpose()	const;

	T determinant3x3() const;

	Mat3 inverse			() const;
	Mat3 inverse3x3			() const;
	Mat3 inverse3x3Transpose() const;

	Vec4	mulPoint	(const Vec4& v) const;
	Vec3	mulPoint4x3	(const Vec3& v) const;	// faster than mulPoint but no projection
	Vec3	mulVector	(const Vec3& v) const;	// for vector (direction)
	
	Vec3	mulNormal				(const Vec3& v) const; // for normal non-uniform scale
	Vec3	unprojectPoint			(const Vec3& screenPos, const Rect2& viewport) const;
	Vec3	unprojectPointFromInv	(const Vec3& screenPos, const Rect2& viewport) const;

			Vec4&	operator[](IndexType i);
	const	Vec4&	operator[](IndexType i) const;

	Mat3 operator-() const;

	Mat3 operator+(T val) const;
	Mat3 operator-(T val) const;
	Mat3 operator*(T val) const;
	Mat3 operator/(T val) const;

	void operator+=(T val);
	void operator-=(T val);
	void operator*=(T val);
	void operator/=(T val);

	Mat3 operator+(const Mat3& rhs) const;
	Mat3 operator-(const Mat3& rhs) const;
	Mat3 operator*(const Mat3& rhs) const;
	Mat3 operator/(const Mat3& rhs) const;

	void operator+=(const Mat3& rhs);
	void operator-=(const Mat3& rhs);
	void operator*=(const Mat3& rhs);
	void operator/=(const Mat3& rhs);

	bool operator==(const Mat3& rhs) const;
	bool operator!=(const Mat3& rhs) const;

public:
	using Glm_Mat3 = typename DATA::Base;
	Mat3(const Glm_Mat3& rhs); // for glm only
	const Data& toData() const;

private:
	const Glm_Mat3& toGlm() const;
};
#endif // NMSP_MATH_BACKEND_GLM


#if 0
#pragma mark --- Mat3_Basic_Glm-Impl ---
#endif // 0
#if 1

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_zero		()
{
	return Mat3{ Vec4::s_zero(), Vec4::s_zero(), Vec4::s_zero(), Vec4::s_zero() };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_one		()
{
	return Mat3{ Vec4::s_one(), Vec4::s_one(), Vec4::s_one(), Vec4::s_one() };
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_cast(const Mat3_T<T2, DATA2>& rhs)
{
	return Mat3{ Vec4(rhs[0]), Vec4(rhs[1]), Vec4(rhs[2]), Vec4(rhs[3]) };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_identity()
{
	return Mat3{
			  Vec4{1.0, 0.0, 0.0, 0.0}
			, Vec4{0.0, 1.0, 0.0, 0.0}
			, Vec4{0.0, 0.0, 1.0, 0.0}
			, Vec4{0.0, 0.0, 0.0, 1.0}
		};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_translate(const Vec3& t)
{
	return glm::translate(t);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_rotate	(const Vec3& rad)
{
	if (rad.equals0()) return s_identity();

	Vec3 s, c;
	math::sincos(rad.x, s.x, c.x);
	math::sincos(rad.y, s.y, c.y);
	math::sincos(rad.z, s.z, c.z);

	return Mat3(
		{(c.y*c.z), (s.x*s.y*c.z - c.x*s.z), (s.x*s.z + c.x*s.y*c.z), 0},
		{(c.y*s.z), (c.x*c.z + s.x*s.y*s.z), (c.x*s.y*s.z - s.x*c.z), 0},
		{(-s.y),    (s.x*c.y),               (c.x*c.y),               0},
		{0,         0,                        0,                      1}
	);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_rotateX	(T rad)
{
	if (math::equals0(rad)) return s_identity();

	T s, c;
	math::sincos(rad, s, c);
	return Mat3({1, 0, 0, 0},
				{0, c, s, 0},
				{0,-s, c, 0},
				{0, 0, 0, 1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_rotateY	(T rad)
{
	if (math::equals0(rad)) return s_identity();

	T s, c;
	math::sincos(rad, s, c);
	return Mat3({c, 0,-s, 0},
				{0, 1, 0, 0},
				{s, 0, c, 0},
				{0, 0, 0, 1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_rotateZ	(T rad)
{
	if (math::equals0(rad)) return s_identity();

	T s, c;
	math::sincos(rad, s, c);
	return Mat3({ c, s, 0, 0},
				{-s, c, 0, 0},
				{ 0, 0, 1, 0},
				{ 0, 0, 0, 1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_scale	(const Vec3& r)
{
	return glm::scale(r);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_shear	(const Vec3& r)
{
	return Mat3( {  1,   0,  0,  0},
				 {v.x,   1,  0,  0},
				 {v.y, v.z,  1,  0},
				 {  0,   0,  0,  1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_quat		(const Quat4& q)
{
	return glm::toMat3(q);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_TRS(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale)
{
	Vec3 s, c;
	Math::sincos(rotate.x, s.x, c.x);
	Math::sincos(rotate.y, s.y, c.y);
	Math::sincos(rotate.z, s.z, c.z);

	return Mat3(
		{scale.x * (c.y*c.z),				scale.x * (c.y*s.z),				scale.x * (-s.y),		0},
		{scale.y * (s.x*s.y*c.z - c.x*s.z),	scale.y * (c.x*c.z + s.x*s.y*s.z),	scale.y * (s.x*c.y),	0},
		{scale.z * (s.x*s.z + c.x*s.y*c.z),	scale.z * (c.x*s.y*s.z - s.x*c.z),	scale.z * (c.x*c.y),	0},
		{translate.x,						translate.y,						translate.z,			1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_TRS(const Vec3& translate, const Quat4& rotate, const Vec3& scale)
{
	return s_translate(translate) * s_quat(rotate) * s_scale(scale);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_TS (const Vec3 & translate, const Vec3 & scale)
{
	return Mat3({scale.x, 0, 0, 0},
				{0, scale.y, 0, 0},
				{0, 0, scale.z, 0},
				{translate.x, translate.y, translate.z, 1});
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_perspective	(T fovy_rad, T aspect, T zNear, T zFar)
{
	return glm::perspective(fovy_rad, aspect, zNear, zFar);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_ortho		(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return glm::ortho(left, right, bottom, top, zNear, zFar);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::s_lookAt		(const Vec3 & eye, const Vec3 & aim, const Vec3 & up)
{
	return glm::lookAt(eye, aim, up);
}

template<class T, class DATA> inline
Mat3_Basic_Glm<T, DATA>::Mat3_Basic_Glm(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_)
{
	set(cx_, cy_, cz_, cw_);
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::set(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_)
{
	(*this)[0] = cx_;
	(*this)[1] = cy_;
	(*this)[2] = cz_;
	(*this)[3] = cw_;
}

template<class T, class DATA> inline
const typename Mat3_Basic_Glm<T, DATA>::Vec4&	Mat3_Basic_Glm<T, DATA>::col		(IndexType i) const
{
	return (*this)[i];
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec4	Mat3_Basic_Glm<T, DATA>::row		(IndexType i) const
{
	return Vec4{ (*this)[0][i], (*this)[1][i], (*this)[2][i], (*this)[3][i] };
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::setCol	(IndexType i, const Vec4& v)
{
	(*this)[i] = v;
}

template<class T, class DATA> inline
void Mat3_Basic_Glm<T, DATA>::setRow	(IndexType i, const Vec4& v)
{
	(*this)[0][i] = v[0];
	(*this)[1][i] = v[1];
	(*this)[2][i] = v[2];
	(*this)[3][i] = v[3];
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::equals	(const Mat3& rhs, const T& epsilon) const
{
	return math::equals((*this)[0], rhs[0], epsilon)
		&& math::equals((*this)[1], rhs[1], epsilon)
		&& math::equals((*this)[2], rhs[2], epsilon)
		&& math::equals((*this)[3], rhs[3], epsilon);
}

template<class T, class DATA> inline
bool Mat3_Basic_Glm<T, DATA>::equals0	(const T& epsilon) const
{
	return math::equals0((*this)[0], epsilon)
		&& math::equals0((*this)[1], epsilon)
		&& math::equals0((*this)[2], epsilon)
		&& math::equals0((*this)[3], epsilon);
}


template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::transpose()	const
{
	return glm::transpose(*this);
}

template<class T, class DATA> inline
T	Mat3_Basic_Glm<T, DATA>::determinant3x3() const
{
	_notYetSupported();
	return {};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::inverse			() const
{
	return glm::inverse(*this);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::inverse3x3			() const
{
	_notYetSupported();
	return {};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::inverse3x3Transpose() const
{
	_notYetSupported();
	return {};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec4	Mat3_Basic_Glm<T, DATA>::mulPoint		(const Vec4& v) const
{
	return sCast<Vec4>(*this * v);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec3	Mat3_Basic_Glm<T, DATA>::mulPoint4x3	(const Vec3& v) const
{
	return mulPoint(Vec4{ v, 1.0 }).xyz();
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec3	Mat3_Basic_Glm<T, DATA>::mulVector		(const Vec3& v) const
{
	return Vec3{ (*this)[0].xyz() * v.x + (*this)[1].xyz()* v.y + (*this)[2].xyz()* v.z };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec3	Mat3_Basic_Glm<T, DATA>::mulNormal		(const Vec3& v) const
{
	return this->inverse3x3Transpose().mulVector(v);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec3	Mat3_Basic_Glm<T, DATA>::unprojectPoint			(const Vec3& screenPos, const Rect2& viewport) const
{
	return inverse().unprojectPointFromInv(screenPos, viewport);
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Vec3	Mat3_Basic_Glm<T, DATA>::unprojectPointFromInv	(const Vec3& screenPos, const Rect2& viewport) const
{
	auto  tmp = Vec4(screenPos, 1);
	tmp.y = viewport.h - tmp.y; // y is down

	tmp.x = (tmp.x - viewport.x) / viewport.w * 2 - 1;
	tmp.y = (tmp.y - viewport.y) / viewport.h * 2 - 1;

	auto obj = mulPoint(tmp);
	return obj.toVec3();
}

template<class T, class DATA> inline
const	typename Mat3_Basic_Glm<T, DATA>::Vec4&	Mat3_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat3_Basic_Glm<T, DATA>::operator[]");
	return sCast<const	Vec4&>(Base::operator[](i));
}

template<class T, class DATA> inline
		typename Mat3_Basic_Glm<T, DATA>::Vec4&	Mat3_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat3_Basic_Glm<T, DATA>::operator[]");
	return sCast<		Vec4&>(Base::operator[](i));
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-()		const
{
	return Mat3{ -(*this)[0], -(*this)[1], -(*this)[2], -(*this)[3] };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+(T val)	const
{
	Vec4 v = {val, val, val, val};
	return Mat3{ (*this)[0] + v, (*this)[1] + v, (*this)[2] + v, (*this)[3] + v};
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat3{ (*this)[0] - v, (*this)[1] - v, (*this)[2] - v, (*this)[3] - v };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat3{ (*this)[0] * v, (*this)[1] * v, (*this)[2] * v, (*this)[3] * v };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/(T val)	const
{
	Vec4 v = { val, val, val, val };
	return Mat3{ (*this)[0] / v, (*this)[1] / v, (*this)[2] / v, (*this)[3] / v };
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator+=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] += val; (*this)[1] += val; (*this)[2] += val; (*this)[3] += val;
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator-=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] -= val; (*this)[1] -= val; (*this)[2] -= val; (*this)[3] -= val;
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator*=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] *= val; (*this)[1] *= val; (*this)[2] *= val; (*this)[3] *= val;
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator/=(T val)
{
	Vec4 v = { val, val, val, val };
	(*this)[0] /= val; (*this)[1] /= val; (*this)[2] /= val; (*this)[3] /= val;
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator+(const Mat3& rhs)	const
{
	return Mat3{ (*this)[0] + rhs[0], (*this)[1] + rhs[1], (*this)[2] + rhs[2], (*this)[3] + rhs[3] };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator-(const Mat3& rhs)	const
{
	return Mat3{ (*this)[0] - rhs[0], (*this)[1] - rhs[1], (*this)[2] - rhs[2], (*this)[3] - rhs[3] };
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator*(const Mat3& rhs)	const
{
	return toGlm() * rhs.toGlm();
}

template<class T, class DATA> inline
typename Mat3_Basic_Glm<T, DATA>::Mat3	Mat3_Basic_Glm<T, DATA>::operator/(const Mat3& rhs)	const
{
	return toGlm() / rhs.toGlm();
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator+=(const Mat3& rhs)
{
	(*this)[0] += rhs[0];
	(*this)[1] += rhs[1];
	(*this)[2] += rhs[2];
	(*this)[3] += rhs[3];
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator-=(const Mat3& rhs)
{
	(*this)[0] -= rhs[0];
	(*this)[1] -= rhs[1];
	(*this)[2] -= rhs[2];
	(*this)[3] -= rhs[3];
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator*=(const Mat3& rhs)
{
	*this = *this * rhs;
}

template<class T, class DATA> inline
void	Mat3_Basic_Glm<T, DATA>::operator/=(const Mat3& rhs)
{
	(*this)[0] /= rhs[0];
	(*this)[1] /= rhs[1];
	(*this)[2] /= rhs[2];
	(*this)[3] /= rhs[3];
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

template<class T, class DATA> inline
const typename Mat3_Basic_Glm<T, DATA>::Data&	Mat3_Basic_Glm<T, DATA>::toData() const
{
	return sCast<const Data&>(*this);
}

template<class T, class DATA> inline
const typename Mat3_Basic_Glm<T, DATA>::Glm_Mat3& Mat3_Basic_Glm<T, DATA>::toGlm() const
{
	return sCast<const Glm_Mat3&>(*this);
}

#endif

}

#endif // NMSP_MATH_BACKEND_GLM
