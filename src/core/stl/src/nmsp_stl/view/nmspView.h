#pragma once

#include "nmspSpan.h"
#include "nmspStringView.h"

namespace nmsp {

inline StrViewA_T makeStrView(ByteSpan_T bs)
{
	return StrViewA_T{ reinterpret_cast<const char*>(bs.data()), bs.size()};
}

inline StrViewA_T makeStrView(Span_T<u8> sp)
{
	return StrViewA_T{ reinterpret_cast<const char*>(sp.data()), sp.size()};
}

inline ByteSpan_T makeByteSpan(StrViewA_T sv)
{
	return ByteSpan_T{ reinterpret_cast<const u8*>(sv.data()), sv.size()};
}

inline ByteSpan_T makeByteSpan(Span_T<u8> sv)
{
	return ByteSpan_T{ reinterpret_cast<const u8*>(sv.data()), sv.size()};
}


}