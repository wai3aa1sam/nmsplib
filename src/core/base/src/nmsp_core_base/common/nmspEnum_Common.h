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


#define NMSP_ENUM_STR__CASE(V, ...) case NMSP_T::V: return #V;

#define NMSP_ENUM_STR(T) \
	inline const char* enumStr(const T& v) { \
		using NMSP_T = T; \
		switch (v) { \
			T##_ENUM_LIST(NMSP_ENUM_STR__CASE) \
			default: NMSP_ASSERT(false); return ""; \
		} \
	} \
//----

#define NMSP_FORMATTER_ENUM(T) \
	} /* namespace nmsp */ \
	template<> \
	struct fmt::formatter<nmsp::T> { \
		auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); } \
		auto format(const nmsp::T& v, fmt::format_context& ctx) { \
			return nmsp::formatTo(ctx, "{}", nmsp::enumStr(v)); \
		} \
	}; \
	namespace nmsp { \
//-----

#define NMSP_ENUM_TRY_PARSE__CASE(V, ...) if (str == #V) { outValue = NMSP_T::V; return true; }

#define NMSP_ENUM_TRY_PARSE(T) \
	inline bool enumTryParse(T& outValue, StrViewA_T str) { \
		using NMSP_T = T; \
		T##_ENUM_LIST(NMSP_ENUM_TRY_PARSE__CASE) \
		return false; \
	} \
//----

#define NMSP_ENUM_STR_UTIL(T) \
	NMSP_ENUM_STR(T) \
	NMSP_ENUM_TRY_PARSE(T) \
	NMSP_FORMATTER_ENUM(T) \
//----

#define NMSP_ENUM_DECLARE__ITEM(ITEM, VALUE) ITEM VALUE,

#define NMSP_ENUM_DECLARE(T, BASE_TYPE) \
	enum class T : BASE_TYPE { \
		T##_ENUM_LIST(NMSP_ENUM_DECLARE__ITEM) \
	}; \
//----

#define NMSP_ENUM_CLASS(T, BASE_TYPE) \
	NMSP_ENUM_DECLARE(T, BASE_TYPE) \
	NMSP_ENUM_STR_UTIL(T) \
//----