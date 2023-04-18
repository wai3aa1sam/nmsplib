#pragma once

#include "common/nmsp_math_common.h"

/*
references:
- Math.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {
namespace Math {

template<class T> constexpr T max(const T& a, const T& b) { return a > b ? a : b; }
template<class T> constexpr T min(const T& a, const T& b) { return a < b ? a : b; }

template<class T> inline constexpr T max(const std::initializer_list<T>& initList) 
{
	T res;
	auto beg = initList.begin();
	auto end = initList.end();
	auto& v = *beg;
	res = max(v, *(++beg));
	while (beg != end)
	{
		res = max(res, *beg);
		++beg;
	}
	return res;
}

template<class T> constexpr T clamp		(const T& v, const T& a, const T& b) { return max(a, min(v, b)) ; }
template<class T> constexpr T clamp01	(const T& v) { return clamp(v, T(0), T(1)); }
template<class T> constexpr T saturate	(const T& v) { return clamp01(v); }

template<class T> constexpr T byteToK(const T& v) { return v / 1024; }
template<class T> constexpr T byteToM(const T& v) { return v / (1024 * 1024); }
template<class T> constexpr T byteToG(const T& v) { return v / (1024 * 1024 * 1024); }

struct _Helper {
	template<class T>
	static constexpr T alignTo_uint(T n, T a) {
		static_assert(std::is_unsigned<T>::value, "");
		T r = n % a;
		return r ? (n + a - r) : n;
		//	return (n + a - 1) / a * a;
	}
};

constexpr size_t alignTo(size_t n, size_t a) { return _Helper::alignTo_uint(n, a); }

template<class T>
constexpr T divideTo(T n, T divisor)
{
	// overestimate
	static_assert(std::is_unsigned<T>::value, "");
	return (n + divisor - 1) / divisor;
}

//--------
template< class T > constexpr T		NaN		() { return std::numeric_limits<T>::quiet_NaN(); }
template< class T > constexpr bool	isNaN	( const T& v )	{ return std::isnan(v); }

template < class T > constexpr T	inf		()				{ return std::numeric_limits<T>::infinity(); }
template < class T > constexpr bool	isInf	( const T& v )	{ return std::numeric_limits<T>::has_infinity && v == inf<T>(); }

//--------
constexpr u64 nextPow2(u64 x) {
	x -= 1;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x |= (x >> 32);
	return x + 1;
}

template<class T> T pow(const T& left, const T& right) { return std::pow(left, right); }

template<class T> constexpr T pow2(T v_)				{ return (T(0x01) << v_); }

template<typename T> constexpr T log2 (T val) {
	//static_assert(std::is_unsigned_v<T>());
	if (val == 0) return std::numeric_limits<T>::max();
	if (val == 1) return 0;
	T ret = 0;
	while (val > 1) {
		val >>= 1;
		ret++;
	}
	return ret;
}

//--------------

//Splits a floating-point value into fractional and integer parts
NMSP_INLINE float	modf	( float  v, float  *i ) { return std::modf( v, i ); }
NMSP_INLINE double	modf	( double v, double *i ) { return std::modf( v, i ); }

NMSP_INLINE float	frac	( float  v )	{ float  intPart; return modf(v, &intPart); }
NMSP_INLINE double	frac	( double v )	{ double intPart; return modf(v, &intPart); }

NMSP_INLINE float	ceil	( float  a )	{ return std::ceil(a); }
NMSP_INLINE double	ceil	( double a )	{ return std::ceil(a); }

NMSP_INLINE float	floor	( float  a )	{ return std::floor(a); }
NMSP_INLINE double	floor	( double a )	{ return std::floor(a); }

//get remainder
NMSP_INLINE float	fmod	( float  a, float  b ) { return std::fmod(a,b); }
NMSP_INLINE double	fmod	( double a, double b ) { return std::fmod(a,b); }

#if NMSP_COMPILER_VC | NMSP_OS_CYGWIN
NMSP_INLINE float  trunc	( float  n )	{ float  i; return std::modf( n, &i ); }
NMSP_INLINE double trunc	( double n )	{ double i; return std::modf( n, &i ); }

NMSP_INLINE float  round	( float  a )	{ return a > 0 ? floor(a+0.5f) : ceil(a-0.5f); }
NMSP_INLINE double round	( double a )	{ return a > 0 ? floor(a+0.5 ) : ceil(a-0.5 ); }
#else
NMSP_INLINE float  trunc	( float  n )	{ return std::trunc(n); }
NMSP_INLINE double trunc	( double n )	{ return std::trunc(n); }

NMSP_INLINE float  round	( float  a )	{ return std::round(a); }
NMSP_INLINE double round	( double a )	{ return std::round(a); }
#endif

NMSP_INLINE int	truncToInt	( float  a )	{ return static_cast<int>( trunc(a) ); }
NMSP_INLINE int	truncToInt	( double a )	{ return static_cast<int>( trunc(a) ); }

NMSP_INLINE int	roundToInt	( float  a )	{ return static_cast<int>( round(a) ); }
NMSP_INLINE int	roundToInt	( double a )	{ return static_cast<int>( round(a) ); }

NMSP_INLINE int	floorTo_Int	( float  a )	{ return static_cast<int>( floor(a) ); }
NMSP_INLINE int	floorTo_Int	( double a )	{ return static_cast<int>( floor(a) ); }

NMSP_INLINE int	ceilToInt	( float  a )	{ return static_cast<int>( ceil (a) ); }
NMSP_INLINE int	ceilToInt	( double a )	{ return static_cast<int>( ceil (a) ); }

//----------

#if 0
#pragma mark ------ Trigonometry ------
#endif
template< class T> constexpr T	PI()	{ return static_cast<T>(3.14159265358979323846); }

template<class T> constexpr T	twoPI	()		{ return PI<T>() * 2; }
template<class T> constexpr T	halfPI	()		{ return PI<T>() * 0.5; }

template<class T> NMSP_INLINE T	radians	(T deg) { return deg * (PI<T>() / static_cast<T>(180)); }
template<class T> NMSP_INLINE T	degrees	(T rad) { return rad * (static_cast<T>(180) / PI<T>()); }


NMSP_INLINE float  sin(float  rad) { return ::sinf(rad); }
NMSP_INLINE double sin(double rad) { return ::sin (rad); }

NMSP_INLINE float  cos(float  rad) { return ::cosf(rad); }
NMSP_INLINE double cos(double rad) { return ::cos (rad); }

NMSP_INLINE float  tan(float  rad) { return ::tanf(rad); }
NMSP_INLINE double tan(double rad) { return ::tan (rad); }

#if NMSP_OS_MACOSX
NMSP_INLINE void sincos( float  rad, float  & out_sin, float  & out_cos ) { ::__sincosf(rad, &out_sin, &out_cos); }
NMSP_INLINE void sincos( double rad, double & out_sin, double & out_cos ) { ::__sincos (rad, &out_sin, &out_cos); }
#elif NMSP_OS_LINUX
NMSP_INLINE void sincos( float  rad, float  & out_sin, float  & out_cos ) { ::sincosf(rad, &out_sin, &out_cos); }
NMSP_INLINE void sincos( double rad, double & out_sin, double & out_cos ) { ::sincos (rad, &out_sin, &out_cos); }
#else
NMSP_INLINE void sincos( float  rad, float  & out_sin, float  & out_cos ) { out_sin = sin(rad); out_cos = cos(rad); }
NMSP_INLINE void sincos( double rad, double & out_sin, double & out_cos ) { out_sin = sin(rad); out_cos = cos(rad); }
#endif

NMSP_INLINE float  asin(float  rad) { return ::asinf(rad); }
NMSP_INLINE double asin(double rad) { return ::asin (rad); }

NMSP_INLINE float  acos(float  rad) { return ::acosf(rad); }
NMSP_INLINE double acos(double rad) { return ::acos (rad); }

NMSP_INLINE float  atan(float  rad) { return ::atanf(rad); }
NMSP_INLINE double atan(double rad) { return ::atan (rad); }

#if 0
#pragma mark ----------------
#endif

template<class T> T abs(const T& v) { return v < 0 ? -v : v; }

#if 0
#pragma mark --- Epsilon-Impl ---
#endif // 0
#if 1

template<class T> struct Epsilon;
template<>
struct Epsilon<i32>
{
	using ValueType = i32;
	static constexpr ValueType s_kValue = 0;
					constexpr ValueType operator()()		NMSP_NOEXCEPT	{ return s_kValue; }
	NMSP_NODISCARD	constexpr ValueType operator()() const	NMSP_NOEXCEPT	{ return s_kValue; }
};

template<>
struct Epsilon<f32>
{
	using ValueType = f32;
	static constexpr ValueType s_kValue = FLT_EPSILON;
					constexpr ValueType operator()()		NMSP_NOEXCEPT	{ return s_kValue; }
	NMSP_NODISCARD	constexpr ValueType operator()() const	NMSP_NOEXCEPT	{ return s_kValue; }
};

template<>
struct Epsilon<f64>
{
	using ValueType = f64;
	static constexpr ValueType s_kValue = DBL_EPSILON;
					constexpr ValueType operator()()		NMSP_NOEXCEPT	{ return s_kValue; }
	NMSP_NODISCARD	constexpr ValueType operator()() const	NMSP_NOEXCEPT	{ return s_kValue; }
};

template<>
struct Epsilon<f128>
{
	using ValueType = f128;
	static constexpr ValueType s_kValue = LDBL_EPSILON;
					constexpr ValueType operator()()		NMSP_NOEXCEPT	{ return s_kValue; }
	NMSP_NODISCARD	constexpr ValueType operator()() const	NMSP_NOEXCEPT	{ return s_kValue; }
};

template<class T> constexpr const T& epsilon() { return Epsilon<T>::s_kValue; }

#endif // 0

#if 0
#pragma mark --- Epsilon-Impl ---
#endif // 0
#if 1

template<class T, class ENABLE = void>
struct EqualsHelper
{
	template<class T, class EP = T> NMSP_INLINE static bool equals_Impl (const T& a, const T& b, const EP& ep = epsilon<T>()) { return abs(a-b) <= ep; }
	template<class T, class EP = T> NMSP_INLINE static bool equals0_Impl(const T& a,             const EP& ep = epsilon<T>()) { return abs( a ) <= ep; }
};

template<class T, class ENABLE = void>
struct hasMathEquals : public FalseType {};

template<class T>
struct hasMathEquals<T, EnableIf< IsMemPtr<decltype(&T::equals)> > > : public TrueType {};

template<class T, class ENABLE = void>
struct has_equals : public FalseType {};

template<class T>
struct has_equals<T, EnableIf< IsMemPtr<decltype(&T::equals)> > > : public TrueType {};

template<class T> inline constexpr bool	Ishas_equals  = IsMemPtr<decltype(&T::equals)>;


template<class T>
struct EqualsHelper<T, EnableIf<Ishas_equals<T>  > >
{
	template<class T, class EP = typename T::ElementType> NMSP_INLINE static bool equals_Impl (const T& a, const T& b, const EP& ep = epsilon<typename T::ElementType>()) { return a.equals (b, ep); }
	template<class T, class EP = typename T::ElementType> NMSP_INLINE static bool equals0_Impl(const T& a,             const EP& ep = epsilon<typename T::ElementType>()) { return a.equals0(ep); }
};

template<class T, class EP = T> NMSP_INLINE bool equals (const T& a, const T& b, const EP& ep = epsilon<T>()) { return EqualsHelper<T>::equals_Impl (a, b, ep); }
template<class T, class EP = T> NMSP_INLINE bool equals0(const T& a,             const EP& ep = epsilon<T>()) { return EqualsHelper<T>::equals0_Impl(a,	ep); }

#endif // 1


//-------------- Lerp ----------------
//! linear interpolation out = a+w*(b-a)

template<class T, class W>
NMSP_INLINE T	lerp(const T& a, const T& b, const W& w );

template<class T, class ENABLE = std::enable_if< std::is_floating_point_v<T> > >
NMSP_INLINE T	lerp(T a, T b, T w ) { return (1-w)*a + w*b; }

template<class T, class ENABLE = std::enable_if< std::is_integral_v<T> > >
NMSP_INLINE T	lerp(T a, T b, double w ) {
	double a_ = static_cast<double>(a);
	double b_ = static_cast<double>(b);
	return static_cast<T>(lerp<double>(a_, b_, w));
}

//---------
NMSP_INLINE float	sqrt(float  n) { return std::sqrt(n); }
NMSP_INLINE double	sqrt(double n) { return std::sqrt(n); }
NMSP_INLINE int		sqrt(int    n) { return static_cast<int>(std::sqrt(static_cast<double>(n))); }

NMSP_INLINE float	cbrt(float  n) { return std::cbrt(n); }
NMSP_INLINE double	cbrt(double n) { return std::cbrt(n); }
NMSP_INLINE int		cbrt(int    n) { return static_cast<int>(std::cbrt(static_cast<double>(n))); }

//------- reciprocal square root ---------------
NMSP_INLINE float rsqrt_fast(float n) {
	#if NMSP_CPU_FEATURE_SSE2
	return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(n)));
	#else // https://en.wikipedia.org/wiki/Fast_inverse_square_root
	uint32_t i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = n * 0.5f;
	y = n;
	i = *reinterpret_cast<uint32_t *>(&y);
	i = 0x5F375A86UL - (i >> 1);
	y = *reinterpret_cast<float *>(&i);
	y = y * (threehalfs - (x2 * y * y));
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return y;
	#endif
}

inline double rsqrt_fast(double n) {
	uint64_t i;
	double x2, y;
	const float threehalfs = 1.5;

	x2 = n * 0.5f;
	y = n;
	i = *reinterpret_cast<uint64_t *>(&y);
	i = 0x5FE6EB50C7B537A9ULL - (i >> 1);
	y = *reinterpret_cast<double *>(&i);
	y = y * (threehalfs - (x2 * y * y));
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return y;
}

inline int rsqrt_fast(int n) {
	double d = static_cast<double>(n);
	return roundToInt(rsqrt_fast(d));
}

NMSP_INLINE float rsqrt(float v) {
	#if 0 //NMSP_CPU_FEATURE_SSE2
	float  xrsqrt_est = rsqrt_fast(v);
	return xrsqrt_est * (1.5f - v * 0.5f * xrsqrt_est * xrsqrt_est); // NR iteration
	#else
	return 1.0f / sqrt(v); 
	#endif
}

NMSP_INLINE double rsqrt(double v) { return 1.0 / sqrt(v); }
NMSP_INLINE int    rsqrt(int    v) { return roundToInt(rsqrt(static_cast<double>(v))); }

}
}