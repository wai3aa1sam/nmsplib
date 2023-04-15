#pragma once

#include "nmsp_math/common/nmsp_math_common.h"

#include "nmsp_math/primitive/nmspTuple3.h"

#if NMSP_MATH_BACKEND_NMSP


namespace nmsp {
#if 0
#pragma mark --- Vec3_Basic_Nmsp-Decl ---
#endif // 0
#if 1

template<class T> using Vec3_Basic_Data_Nmsp = Tuple3<T>;

template<class T, class DATA = Vec3_Basic_Data_Nmsp<T> >
struct Vec3_Basic_Nmsp : public DATA
{
public:
	using SizeType = size_t;

public:
	using Base = DATA;
public:
	using Base::x;
	using Base::y;
	using Base::z;
	using Base::data;
public:



private:

};

#endif // NMSP_MATH_BACKEND_NMSP


#if 0
#pragma mark --- Vec3_Basic_Nmsp-Impl ---
#endif // 0
#if 1


#endif


}
#endif // NMSP_MATH_BACKEND_NMSP
