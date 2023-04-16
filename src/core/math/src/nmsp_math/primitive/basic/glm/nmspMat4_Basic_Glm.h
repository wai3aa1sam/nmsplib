#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/nmspMath.h"
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

	using SizeType	= size_t;
	using IndexType	= i32;

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

	template<clas T2> using Vec4_T		= Vec4_T<T2>;

	template<class T2, class DATA2> using Mat4_T = Mat4_Basic_Glm<T2, DATA2>;
	
	using SizeType	= typename Base::SizeType;
	using IndexType = typename Base::IndexType;

public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::data;

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
	const Vec4&	row		(SizeType i) const;
	void		setCol	(SizeType i, const Vec4& v);
	void		setRow	(SizeType i, const Vec4& v);
	void		set		(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_);
	
	bool	equals	(const Mat4& rhs, const T& epsilon = Math::epsilon<T>()) const;
	bool	equals0	(				  const T& epsilon = Math::epsilon<T>()) const;

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

private:
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
	return Mat4{ T(0), T(0), T(0)};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_one		()
{
	return Mat4{ T(1), T(1), T(1)};
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_one		()
{
	return Mat4{ T(1), T(1), T(1)};
}

template<class T, class DATA> 
template<class T2, class DATA2> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_cast(const Mat4_T<T2, DATA2>& rhs)
{
	return Mat4{ Vec4(rhs.cx), Vec4(rhs.cy), Vec4(rhs.cz), Vec4(rhs.cw) };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_identity()
{
	return Mat4{ 
		  Vec4(rhs.cx)
		, Vec4(rhs.cy)
		, Vec4(rhs.cz)
		, Vec4(rhs.cw) };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_translate(const Vec3& t)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotate	(const Vec3& r)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateX	(T rad)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateY	(T rad)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_rotateZ	(T rad)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_scale	(const Vec3& r)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_shear	(const Vec3& r)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_quat		(const Quat4& q)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TRS(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TRS(const Vec3 & translate, const Quat4& rotate, const Vec3 & scale)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_TS (const Vec3 & translate, const Vec3 & scale)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_perspective	(T fovy_rad, T aspect, T zNear, T zFar)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_ortho		(T left, T right, T bottom, T top, T zNear, T zFar)
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::s_lookAt		(const Vec3 & eye, const Vec3 & aim, const Vec3 & up)
{

}

template<class T, class DATA> inline
Mat4_Basic_Glm<T, DATA>::Mat4_Basic_Glm(const Vec4& cx_, const Vec4& cy_, const Vec4& cz_, const Vec4& cw_)
{
	set(cx_, cy_, cz_, cw_);
}

template<class T, class DATA> inline
const typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::col		(SizeType i) const
{

}

template<class T, class DATA> inline
const typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::row		(SizeType i) const
{

}

template<class T, class DATA> inline
void Mat4_Basic_Glm<T, DATA>::setCol	(SizeType i, const Vec4& v)
{

}

template<class T, class DATA> inline
void Mat4_Basic_Glm<T, DATA>::setRow	(SizeType i, const Vec4& v)
{

}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::equals	(const Mat4& rhs, const T& epsilon) const
{
	return Math::equals(cx, rhs.cx, epsilon)
		&& Math::equals(cy, rhs.cy, epsilon)
		&& Math::equals(cz, rhs.cz, epsilon)
		&& Math::equals(cw, rhs.cw, epsilon);
}

template<class T, class DATA> inline
bool Mat4_Basic_Glm<T, DATA>::equals0	(const T& epsilon) const
{
	return Math::equals0(cx, epsilon)
		&& Math::equals0(cy, epsilon)
		&& Math::equals0(cz, epsilon)
		&& Math::equals0(cw, epsilon);
}


template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::transpose()	const
{

}

template<class T, class DATA> inline
T	Mat4_Basic_Glm<T, DATA>::determinant3x3() const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse			() const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse3x3			() const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::inverse3x3Transpose() const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec4	Mat4_Basic_Glm<T, DATA>::mulPoint		(const Vec4& v) const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulPoint4x3	(const Vec3& v) const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulVector		(const Vec3& v) const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::mulNormal		(const Vec3& v) const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::unprojectPoint			(const Vec3& screenPos, const Rect2& viewport) const
{

}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Vec3	Mat4_Basic_Glm<T, DATA>::unprojectPointFromInv	(const Vec3& screenPos, const Rect2& viewport) const
{

}

template<class T, class DATA> inline
const	typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::operator[](IndexType i) const
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat4_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[i];
}

template<class T, class DATA> inline
		typename Mat4_Basic_Glm<T, DATA>::Vec4&	Mat4_Basic_Glm<T, DATA>::operator[](IndexType i)
{
	NMSP_ASSERT(i >= 0 && i < s_kColumnCount, "Mat4_Basic_Glm<T, DATA>::operator[]");
	return Base::operator[i];
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-()		const
{
	return Mat4{ -x, -y, -z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+(T val)	const
{
	return Mat4{ x + val, y + val, z + val };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-(T val)	const
{
	return Mat4{ x - val, y - val, z - val };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*(T val)	const
{
	return Mat4{ x * val, y * val, z * val };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/(T val)	const
{
	return Mat4{ x / val, y / val, z / val };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+=(T val)
{
	x += val; y += val; z += val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-=(T val)
{
	x -= val; y -= val; z -= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*=(T val)
{
	x *= val; y *= val; z *= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/=(T val)
{
	x /= val; y /= val; z /= val;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+(const Mat4& rhs)	const
{
	return Mat4{ x + rhs.x, y + rhs.y, z + rhs.z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-(const Mat4& rhs)	const
{
	return Mat4{ x - rhs.x, y - rhs.y, z - rhs.z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*(const Mat4& rhs)	const
{
	return Mat4{ x * rhs.x, y * rhs.y, z * rhs.z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/(const Mat4& rhs)	const
{
	return Mat4{ x / rhs.x, y / rhs.y, z / rhs.z };
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator+=(const Mat4& rhs)
{
	x += rhs.x; y += rhs.y; z += rhs.z;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator-=(const Mat4& rhs)
{
	x -= rhs.x; y -= rhs.y; z -= rhs.z;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator*=(const Mat4& rhs)
{
	x *= rhs.x; y *= rhs.y; z *= rhs.z;
}

template<class T, class DATA> inline
typename Mat4_Basic_Glm<T, DATA>::Mat4	Mat4_Basic_Glm<T, DATA>::operator/=(const Mat4& rhs)
{
	x /= rhs.x; y /= rhs.y; z /= rhs.z;
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
