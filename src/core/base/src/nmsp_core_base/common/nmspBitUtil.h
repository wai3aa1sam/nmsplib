#pragma once

#include "nmspTypeTraits_Common.h"

/*
references:
- src/core/base/BitUtil.h in [https://github.com/SimpleTalkCpp/SimpleGameEngine](https://github.com/SimpleTalkCpp/SimpleGameEngine)
*/

namespace nmsp {

struct BitUtil 
{
public:
	using SizeType = CoreBaseTraits::SizeType;

public:
	BitUtil() = delete;

public:
	template<class T>	constexpr	static bool	has		 (T  value, T bits)				;
	template<class T>	constexpr	static bool	hasAny	 (T  value, T bits)				;
	template<class T>	constexpr	static bool	hasOnly	 (T  value, T bits)				;
	template<class T>	constexpr	static bool	hasButNot(T  value, T bits, T NotBits)	;
	template<class T>	constexpr	static void	set		 (T& value, T bits, bool b)		;
	template<class T>	constexpr	static void	set		 (T& value, T bits)				;
	template<class T>	constexpr	static void	unset	 (T& value, T bits)				;
	template<class T>	constexpr	static void	toggle	 (T& value, T bits)				;
	template<class T>	constexpr	static int	count1	 (T  value);
	template<class T>	constexpr	static int	count0	 (T  value);
	template<class T>	constexpr	static int	highest	 (T  value);
	template<class T>	constexpr	static int	lowest	 (T  value);

	template<class T>	constexpr	static T	bit		(T bits_)				;
	template<class T>	constexpr	static bool	hasBit	(T value, T bits)		;
	template<class T>	constexpr	static void	setBit	(T& value, int nth)		;
	template<class T>	constexpr	static void	unsetBit(T& value, int nth)		;

	template<class T>	constexpr	static SizeType	bitSize();
	template<class T>	constexpr	static T		bitSize(T bytes);

	template<class T>	constexpr	static T		toByte(T bits);

	template<class T>	constexpr	static T setN(T n);

};

template<class T>	inline constexpr bool	BitUtil::has		(T  value, T bits)				{ return (value & bits) == bits; }	
template<class T>	inline constexpr bool	BitUtil::hasAny		(T  value, T bits)				{ return (value & bits) != T(0);    }
template<class T>	inline constexpr bool	BitUtil::hasOnly	(T  value, T bits)				{ return (value & bits) == bits && (value & ~bits) == T(0); }	
template<class T>	inline constexpr bool	BitUtil::hasButNot	(T  value, T bits, T NotBits)	{ return (value & bits) == bits && !hasAny(value, NotBits); }	
template<class T>	inline constexpr void	BitUtil::set		(T& value, T bits, bool b)		{ b ? set(value, bits) : unset(value, bits); }
template<class T>	inline constexpr void	BitUtil::set		(T& value, T bits)				{ value |=  bits; }
template<class T>	inline constexpr void	BitUtil::unset		(T& value, T bits)				{ value &= ~bits; }
template<class T>	inline constexpr void	BitUtil::toggle		(T& value, T bits)				{ value ^=  bits; }
template<class T>	inline constexpr int	BitUtil::count0		(T  value)						{ return count1(~value); }

template<class T>	inline constexpr T		BitUtil::bit		(T bits_)				{ static_assert(IsIntegral<T>, "bit()"); return T(0x01) << bits_;  }
template<class T>	inline constexpr bool	BitUtil::hasBit		(T value, T bits)		{ return has(value, bit(bits)); }

template<class T>	inline constexpr void	BitUtil::setBit		(T& value, int nth)		{ NMSP_ASSERT(nth < byteSize<T>()); value |=  bit(nth); }
template<class T>	inline constexpr void	BitUtil::unsetBit	(T& value, int nth)		{ NMSP_ASSERT(nth < byteSize<T>()); value &= ~bit(nth); }

template<class T>	constexpr	static BitUtil::SizeType	BitUtil::bitSize()			{ return sizeof(T) * 8; }
template<class T>	constexpr	static T					BitUtil::bitSize(T bytes)	{ return bytes * 8; }
template<class T>	constexpr	static T					BitUtil::toByte(T bits)		{ return bits / 8; }

template<class T>	constexpr	static T	BitUtil::setN(T n)
{
	T res = 0;
	for (T i = 0; i < n; i++)
	{
		set(res, bit(i));
	}
	return res;
}

template<class T> constexpr
int BitUtil::highest(T value) {
	int result = -1;
	int n = sizeof(T) * 8;
	T m = T(1 << (n - 1));
	for (int i = n - 1; i >= 0; i--) {
		if (hasAny(value, m))
			return i;
		m >>= 1;
	}
	return result;
}

template<class T> constexpr
int BitUtil::lowest(T value) {
	int result = -1;
	int n = sizeof(T) * 8;
	T m = T(1);
	for (int i = 0; i < n; i++) {
		if (hasAny(value, m))
			return i;
		m <<= 1;
	}
	return result;
}

template<class T> constexpr
int BitUtil::count1(T value) {
	int result = 0;
	int n = sizeof(T) * 8;
	T m = T(1);
	for (int i = 0; i < n; i++) {
		if (hasAny(value, m)) result++;
		m <<= 1;
	}
	return result;
}

}