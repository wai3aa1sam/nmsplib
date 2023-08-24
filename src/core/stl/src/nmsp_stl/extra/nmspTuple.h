#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp {

#if 0
#pragma mark --- Tuple_T-Decl ---
#endif // 0
#if 1


//template<class... ARGS> using Tuple_T = std::tuple<ARGS...>;
//
//template<class T> inline constexpr
//size_t tupleLength()
//{
//	return std::tuple_size<T>();
//}
//
//template<size_t I, class... ARGS> inline constexpr
//decltype(auto) tupleGet(const Tuple_T<ARGS...>& t)
//{
//	//return 0;
//	return std::get<I>(t);
//}

template<size_t I, class TUPLE>
struct TupleElementT
{
	using Type = typename std::tuple_element<I, typename TUPLE::Base>::type;
};
template<size_t I, class TUPLE> using TupleElement = typename TupleElementT<I, TUPLE>::Type;



template<class... ARGS>
class Tuple_T : public std::tuple<ARGS...>
{
public:
	using Base = std::tuple<ARGS...>;
	using This = Tuple_T<ARGS...>;

	template<size_t I> using ElementType = typename TupleElement<I, This>;

public:
	Tuple_T() = default;

	template<class... ARGS> constexpr
	Tuple_T(ARGS&&... args)
		: Base(nmsp::forward<ARGS>(args)...)
	{

	}

	/*template<class... ARGS> // enable if , but need a extra struct helper
	Tuple_T(const std::tuple<ARGS...>& t)
		: Base(t)
	{

	}*/

	static constexpr size_t s_length()
	{
		return std::tuple_size<Base>::value;
	}

	template<size_t I> constexpr
	decltype(auto) get() const
	{
		//return s_make_std(nmsp::forward<ARGS>(args)...);
		//return 0;
		//return std::get<I>((const Base&)(*this));
		return std::get<I>(*this);
	}

	template<class... ARGS_> constexpr
	static Tuple_T<ARGS_...> s_make(ARGS_&&... args)
	{
		return Tuple_T<ARGS_...>(nmsp::forward<ARGS_>(args)...);
	}

private:

	template<class... ARGS_> constexpr
	static std::tuple<ARGS...> s_make_std(Tuple_T<ARGS_...> tp)
	{
		return std::tuple<ARGS...>(tp.);
	}
};

template<class... ARGS_> constexpr
Tuple_T<ARGS_...> makeTuple(ARGS_&&... args)
{
	return Tuple_T<ARGS_...>(nmsp::forward<ARGS_>(args)...);
}

//inline size_t tupleSize()

template<class FUNC, size_t I = 0, class... ARGS> inline 
EnableIf<I == sizeof...(ARGS)> tupleLoop(FUNC func, Tuple_T<ARGS...>& t)
{ 
}

template<class FUNC, size_t I = 0, class... ARGS> inline 
EnableIf<I < sizeof...(ARGS)> tupleLoop(FUNC func, Tuple_T<ARGS...>& t)
{
	func(t.get<I>(), I);
	tupleLoop<FUNC, I + 1, ARGS...>(func, t);
}

//template<class FUNC, size_t I = 0, class... ARGS> inline 
//EnableIf<I == sizeof...(ARGS)> tupleLoop(FUNC func, std::tuple<ARGS...>& t)
//{ 
//}
//
//template<class FUNC, size_t I = 0, class... ARGS> inline 
//EnableIf<I < sizeof...(ARGS)> tupleLoop(FUNC func, std::tuple<ARGS...>& t)
//{
//	func(std::get<I>(t), I);
//	tupleLoop<FUNC, I + 1, ARGS...>(func, t);
//}


#endif


template<size_t I, class... ARGS>
struct GetElementT
{
	using Type = typename std::tuple_element<I, typename Tuple_T<ARGS...> >::type;
};
template<size_t I, class... ARGS> using GetElement = typename GetElementT<I, ARGS...>::Type;

}