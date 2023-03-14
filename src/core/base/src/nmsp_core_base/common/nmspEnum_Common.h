#pragma once

#include <type_traits>

/*
references:
- sge_marco.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

template<class T> inline constexpr typename std::underlying_type<T>::type		 enumInt(T e)	  { return		 static_cast<	   typename std::underlying_type<T>::type >(e); }
template<class T> inline constexpr typename std::underlying_type<T>::type&		 enumIntRef(T& e) { return *reinterpret_cast<	   typename std::underlying_type<T>::type*>(e); }
template<class T> inline constexpr typename std::underlying_type<T>::type const& enumIntRef(T& e) { return *reinterpret_cast<const typename std::underlying_type<T>::type*>(e); }

}

#define NMSP_ENUM_BITWISE_OPERATOR(T) \
	constexpr T operator~ (T  a)			{ return static_cast<T>(~enumInt(a)); } \
	constexpr T operator| (T  a, T b)		{ return static_cast<T>(enumInt(a) | enumInt(b)); } \
	constexpr T operator& (T  a, T b)		{ return static_cast<T>(enumInt(a) & enumInt(b)); } \
	constexpr T operator^ (T  a, T b)		{ return static_cast<T>(enumInt(a) ^ enumInt(b)); } \
	constexpr void operator|=(T& a, T b)	{ a = static_cast<T>(enumInt(a) | enumInt(b)); } \
	constexpr void operator&=(T& a, T b)	{ a = static_cast<T>(enumInt(a) & enumInt(b)); } \
	constexpr void operator^=(T& a, T b)	{ a = static_cast<T>(enumInt(a) ^ enumInt(b)); } \
//--------

#define NMSP_ENUM_ARITHMETIC_OPERATOR(T) \
	constexpr T operator+ (T  a, T b)		{ return static_cast<T>(enumInt(a) + enumInt(b)); } \
	constexpr T operator- (T  a, T b)		{ return static_cast<T>(enumInt(a) - enumInt(b)); } \
	constexpr T operator* (T  a, T b)		{ return static_cast<T>(enumInt(a) * enumInt(b)); } \
	constexpr T operator/ (T  a, T b)		{ return static_cast<T>(enumInt(a) / enumInt(b)); } \
	constexpr void operator+=(T& a, T b)	{ a = static_cast<T>(enumInt(a) + enumInt(b)); } \
	constexpr void operator-=(T& a, T b)	{ a = static_cast<T>(enumInt(a) - enumInt(b)); } \
	constexpr void operator*=(T& a, T b)	{ a = static_cast<T>(enumInt(a) * enumInt(b)); } \
	constexpr void operator/=(T& a, T b)	{ a = static_cast<T>(enumInt(a) / enumInt(b)); } \
//--------

#define NMSP_ENUM_ARITHMETIC_OPERATOR_INT(T) \
	constexpr T operator+ (T  a, int b)		{ return static_cast<T>(enumInt(a) + b); } \
	constexpr T operator- (T  a, int b)		{ return static_cast<T>(enumInt(a) - b); } \
	constexpr T operator* (T  a, int b)		{ return static_cast<T>(enumInt(a) * b); } \
	constexpr T operator/ (T  a, int b)		{ return static_cast<T>(enumInt(a) / b); } \
	constexpr void operator+=(T& a, int b)	{ a = static_cast<T>(enumInt(a) + b); } \
	constexpr void operator-=(T& a, int b)	{ a = static_cast<T>(enumInt(a) - b); } \
	constexpr void operator*=(T& a, int b)	{ a = static_cast<T>(enumInt(a) * b); } \
	constexpr void operator/=(T& a, int b)	{ a = static_cast<T>(enumInt(a) / b); } \
//--------

#define NMSP_ENUM_ALL_OPERATOR(T) \
	NMSP_ENUM_BITWISE_OPERATOR(T) \
	NMSP_ENUM_ARITHMETIC_OPERATOR(T) \
	NMSP_ENUM_ARITHMETIC_OPERATOR_INT(T) \
//-------
