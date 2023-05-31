#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

#include "nmsp_stl/container/nmspArray.h"
#include "nmsp_stl/extra/nmspTuple.h"

namespace nmsp {

#if 0
#pragma mark --- IntSeq_T-Decl ---
#endif // 0
#if 1

template<class T, T... VALS>	using IntSeq_T = std::integer_sequence<T, VALS...>;
template<size_t N>				using IdxSeq_T = std::make_index_sequence<N>;

#endif

template <class SEQ>
struct MakeArray_Impl;

template <class V, template <V N> class C, V... VALS>
struct MakeArray_Impl<Tuple_T<C<VALS>... >> 
{
	static constexpr std::array value{VALS... };
	//static constexpr Array_T value = _value;

};

template <class T, T... VALS>
struct MakeArray_Impl<std::integer_sequence<T, VALS...> > 
{
	static constexpr std::array value{VALS... };
	
	//static constexpr Array_T value{NS...};
};

template <class SEQ>
constexpr auto makeArray = MakeArray_Impl<SEQ>::value;


}