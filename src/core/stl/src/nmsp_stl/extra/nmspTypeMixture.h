#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include "nmspIntSeq.h"

namespace nmsp {

#define NMSP_TM_CALCULATE_VALUE_IMPL(I, T, TUPLE) ( TypeMixture_T<T>::getIntValue<I>(TUPLE) )
#define NMSP_TM_MAKE_SELECT(COUNT)		NMSP_IDX_LIST_##COUNT
#define NMSP_TM_MAKE(T, ...) \
NMSP_IDENTITY(NMSP_CALL(NMSP_TM_MAKE_SELECT, NMSP_VA_ARGS_COUNT(__VA_ARGS__)) (|, NMSP_TM_CALCULATE_VALUE_IMPL, NMSP_ARGS(, T, TypeMixture_T<T>::Types(__VA_ARGS__) ) ))

#if 0
#pragma mark --- TypeMixture_T-Decl ---
#endif // 0
#if 1

#if 1

#endif // 0

template<class T, class IMPL>	struct TypeMixture_T;
template<class T>				struct TypeMixture_Impl;

template<class T>
struct TypeMixture_Impl
{
	//using Types							= Tuple_T<int, u8, u8>;
	//static constexpr size_t s_kSizes[3]	=		 {  4,	2,	4};
};

template<class T>
struct TM
{
	using TypeMixture	= TypeMixture_T<T, TypeMixture_Impl<T> >;
	using ValueType		= typename TypeMixture::ValueType;
	using IntType		= typename TypeMixture::IntType;
	using Types			= typename TypeMixture::Types;
	template<class VAL_T, class... ARGS> static constexpr ValueType make	(const VAL_T& v, ARGS&&... args) { return TypeMixture::make		(v, nmsp::forward<ARGS>(args)...); }
	template<class VAL_T, class... ARGS> static constexpr IntType	makeInt	(const VAL_T& v, ARGS&&... args) { return TypeMixture::makeInt	(v, nmsp::forward<ARGS>(args)...); }
};

template<class T, class IMPL = TypeMixture_Impl<T> >
struct TypeMixture_T : public IMPL
{
public:
	using Base = IMPL;

	using ValueType = T;
	using IntType	= typename EnumInt<ValueType>;
	using typename Base::Types;
	//template<size_t I> using ElementType = typename Base::ElementType<I>;

	using SizeType = StlTraits::SizeType;

public:
	using Base::s_kSizes;
	static constexpr SizeType s_kElementCount	= Types::s_length();
	static constexpr SizeType s_kByteSize		= sizeof(ValueType) * 8;
	static constexpr SizeType s_kByteUsed		= accumulator(s_kSizes);
	static constexpr SizeType s_kByteRemain		= s_kByteSize - s_kByteUsed;

public:
	template<class VAL_T, class... ARGS> static constexpr ValueType make	(const VAL_T& v, ARGS&&... args);
	template<class VAL_T, class... ARGS> static constexpr IntType	makeInt	(const VAL_T& v, ARGS&&... args);
	
	template<size_t I>				static constexpr IntType	getIntValue	(const Types& t);
	template<size_t I, class VAL_T> static constexpr ValueType	getVal		(const VAL_T& v);

	template<size_t I>	static constexpr SizeType	offset();
						static constexpr SizeType	offsets(SizeType i);

private:
	template<size_t I = 0, class VAL_T>					static constexpr ValueType _make(const VAL_T& v);
	template<size_t I = 0, class VAL_T, class... ARGS>	static constexpr ValueType _make(const VAL_T& v, ARGS&&... args);

public:
	template<size_t... NS> static constexpr IntType _addValue(); // unused, legacy
};

template<class T, size_t N = TypeMixture_T<T>::s_kElementCount>
constexpr auto makeTM_offsets
{
	[]() constexpr
	{
		using TM = TypeMixture_T<T>;
		std::array<size_t, N> res{};
		//size_t res[N];
		res[0] = 0;
		for (int j = 1; j < N; ++j)
		{
			// eq to res[j] = accumulateTo<j>(TM::s_kSizes);
			size_t sum = 0;
			for (int i = 0; i < j; ++i)
			{
				sum = std::plus()(sum, TM::s_kSizes[i]);
			}
			res[j] = sum;
		}
		return res; 
	}()
};

#endif

#if 0
#pragma mark --- TypeMixtureOffset-Impl ---
#endif // 0
#if 1

template<size_t N>
struct TypeMixtureOffset
{
	constexpr 
	TypeMixtureOffset(const size_t sizes[])
	{
		_offsets[0] = 0;
		for (size_t i = 1; i < N; i++)
		{
			_offsets[i] = _offsets[i - 1] + sizes[i - 1];
		}
	}

	const size_t* offsets() const { return _offsets; }

private:
	size_t _offsets[N];
};

#endif

#if 0
#pragma mark --- TypeMixture_T-Impl ---
#endif // 0
#if 1

template<class T, class IMPL>
template<class VAL_T, class... ARGS> inline constexpr 
typename TypeMixture_T<T, IMPL>::ValueType 
TypeMixture_T<T, IMPL>::make(const VAL_T& v, ARGS&&... args)
{
	NMSP_S_ASSERT(s_kElementCount == sizeof...(ARGS) + 1);
	NMSP_S_ASSERT(s_kByteUsed <= s_kByteSize);
	return _make<0>(v, nmsp::forward<ARGS>(args)...);
}

template<class T, class IMPL>
template<class VAL_T, class... ARGS> inline constexpr
typename TypeMixture_T<T, IMPL>::IntType 
TypeMixture_T<T, IMPL>::makeInt(const VAL_T& v, ARGS&&... args)
{
	return sCast<IntType>(make(v, nmsp::forward<ARGS>(args)...));
}

template<class T, class IMPL>
template<size_t I> inline constexpr
typename TypeMixture_T<T, IMPL>::IntType TypeMixture_T<T, IMPL>::getIntValue(const Types& t)
{
	NMSP_S_ASSERT(s_kByteUsed <= s_kByteSize);
	return sCast<IntType>(getVal<I>(t.get<I>()));
}

template<class T, class IMPL>
template<size_t I, class VAL_T> inline constexpr
typename TypeMixture_T<T, IMPL>::ValueType TypeMixture_T<T, IMPL>::getVal(const VAL_T& v)
{
	return sCast<ValueType>(sCast<IntType>(v) << offset<I>());
}

template<class T, class IMPL>
template<size_t I> inline constexpr
typename TypeMixture_T<T, IMPL>::SizeType 
TypeMixture_T<T, IMPL>::offset()
{
	if constexpr (I == 0)
	{
		return 0;
	}
	else
	{
		return accumulateTo<I>(s_kSizes);
	}
}
template<class T, class IMPL>
template<size_t I, class VAL_T> inline constexpr 
typename TypeMixture_T<T, IMPL>::ValueType 
TypeMixture_T<T, IMPL>::_make(const VAL_T& v)
{
	return getVal<I>(v);
}

template<class T, class IMPL>
template<size_t I, class VAL_T, class... ARGS> inline constexpr 
typename TypeMixture_T<T, IMPL>::ValueType 
TypeMixture_T<T, IMPL>::_make(const VAL_T& v, ARGS&&... args)
{
	return sCast<ValueType>(sCast<IntType>(getVal<I>(v)) | sCast<IntType>(_make<I + 1>(nmsp::forward<ARGS>(args)...) ) );
}


template<class T, class IMPL> inline constexpr
typename TypeMixture_T<T, IMPL>::SizeType 
TypeMixture_T<T, IMPL>::offsets(SizeType i)
{
	constexpr auto off = makeTM_offsets<T>;
	return off[i];
}

template<class T, class IMPL>
template<size_t... NS> inline constexpr
typename TypeMixture_T<T, IMPL>::IntType 
TypeMixture_T<T, IMPL>::_addValue()
{
	constexpr size_t N	= s_kElementCount;
	auto intSeq			= IntSeq_T<size_t, NS...>();
	static_assert(intSeq.size() == N, "");

	constexpr auto vals	= makeArray<decltype(intSeq)>;
	constexpr auto off	= makeTM_offsets<T>;

	IntType res(IntType(0));
	for (int i = 0; i < N; ++i)
	{
		res |= (vals[i] << off[i]);
	}
	return res;
}


#endif // 1


#if 0

#if 0

template<size_t OUT, class... ARGS> inline constexpr 
size_t testOut(Tuple_T<ARGS...> t)
{
	return t.get<0>();
}
struct TTT { using Ty = int; };
template<TTT::Ty OUT> constexpr
TTT::Ty ooo()
{
	using TM = TypeMixture_T<TestEnum>;

	constexpr size_t arr[] = { 10, 20, 30 };
	//return (TTT::Ty)accumulator(arr);
	return (TTT::Ty)TM::_s_calOffset<1>();
	//return 10;
	//return TypeMixture_Helper<>;
}

enum Te
{
	//k = make( std::tuple<ColorModel, ColorElementType>{ ColorModel::R,		ColorElementType::UNorm8 } ),
};

#endif // 0

#if 0

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I == sizeof...(ARGS), typename TypeMixture_Impl<T>::IntType> _TypeMixture_internal_make(Tuple_T<ARGS...>  t)
{
	using TM = TypeMixture_T<T>;
	using IntType = typename TM::IntType;
	return RET_V;
}
template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I < sizeof...(ARGS), typename TypeMixture_Impl<T>::IntType> _TypeMixture_internal_make(Tuple_T<ARGS...>  t)
{
	using TM = TypeMixture_T<T>;
	using IntType = typename TM::IntType;
	//constexpr IntType o = sCast<IntType>(RET_V | (sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>()) );
	constexpr auto i = 0;//std::get<I>(t);
	//constexpr auto i = std::get<I>(Ts{ 1,		(u8)1, (u8)1 });
	//constexpr auto i = std::get<I>(t);

	//constexpr IntType o = TM::addValue<RET_V, sCast<IntType>(i), TM::_s_calOffset<I>() >();

	//constexpr IntType o = (IntType)(TM::_s_calOffset<I>());
	return _TypeMixture_internal_make<T, i, I + 1, ARGS...>(t);
}

template<class T>
struct TypeMixture_Helper
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;

	template<class... ARGS>
	static constexpr T s_make_impl(Tuple_T<ARGS...> t)
	{
		return sCast<T>(_TypeMixture_internal_make<T, 0, 0, ARGS...>(t));
	}
};

template<class... ARGS> inline constexpr
int make(const Tuple_T<ARGS...>&  t)
{
	using TM = typename TypeMixture_T<TestEnum>;
	using IntType = typename TM::IntType;

	//return testOut<t.get<0>()>(t);
	//return ooo<10>();
	return (int)TypeMixture_Helper<TestEnum>::s_make_impl(t);
	//return (int)TM::_s_calOffset<2>();
	//return (int)tupleGet<0>(t);
	//return (int)std::get<1>(t);
	//return 4 | (int)sCast<IntType>(tupleGet<2>(t)) << TM::_s_calOffset<2>();
}
#endif // 0

#if 0

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I == sizeof...(ARGS), typename TypeMixture_Impl<T>::IntType> test3(const Tuple_T<ARGS...>& t)
{
	return RET_V;
}

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I < sizeof...(ARGS), typename TypeMixture_Impl<T>::IntType> test3(const Tuple_T<ARGS...>& t)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	//constexpr IntType o = TM::addValue<RET_V, 0, TM::_s_calOffset<I>() >();
	//sCast<IntType>(std::get<I>(t))
	constexpr IntType o = RET_V | (std::get<I>(t) << TM::_s_calOffset<I>());

	return test3<T, o, I + 1>(t);

	//return test3<T, RET_V | (std::get<I>(t) << TM::_s_calOffset<I>()), I + 1>(t);
}

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t BEG, size_t END, class TUPLE> inline constexpr
EnableIf<BEG == END, typename TypeMixture_Impl<T>::IntType> test_(TUPLE&& t)
{
	return RET_V;
}

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t BEG, size_t END, class TUPLE> inline constexpr
EnableIf<BEG < END, typename TypeMixture_Impl<T>::IntType> test_(TUPLE&& t)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	//constexpr IntType o = TM::addValue<RET_V, 0, TM::_s_calOffset<I>() >();
	//sCast<IntType>(std::get<I>(t))
	//constexpr IntType o = RET_V | (std::get<I>(t) << TM::_s_calOffset<I>());

	//return test_<T, TUPLE, RET_V | (std::get<TUPLE>(t) << TM::_s_calOffset<BEG>()), BEG + 1, END>(nmsp::forward<TUPLE>(t));
	return test_<T, TUPLE, RET_V | (std::get<TUPLE>(t) << TM::_s_calOffset<BEG>()), BEG + 1, END>(nmsp::forward<TUPLE>(t));

}

template<class T, class TUPLE> inline constexpr
typename TypeMixture_Impl<T>::IntType test2_(TUPLE&& t)
{
	return test_<T, 0, 0, 3>(nmsp::forward<TUPLE>(t));
}

template<class T, typename TypeMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
typename TypeMixture_Impl<T>::IntType test2(const Tuple_T<ARGS...>& t)
{
	return test3<T, 0, 0>(t);
}

template<class T, size_t I, class... ARGS> inline constexpr
typename TypeMixture_Impl<T>::IntType cal_make(const Tuple_T<ARGS...>& t)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	return sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>();
}

template<class T, size_t I, class... ARGS>
struct Cal
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;

	static constexpr IntType get(const Tuple_T<ARGS...>& t)
	{
		if constexpr (I == 0)
		{
			return sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>();
		}
		else
		{
			return Cal<T, I - 1, ARGS...>::get(t) | sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>();
		}
		//return sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>();
	}
	//static constexpr IntType value = sCast<IntType>(tupleGet<I>(t)) << TM::_s_calOffset<I>();
};

template<class T, typename TypeMixture_Impl<T>::IntType... VALS>
typename TypeMixture_Impl<T>::IntType getVal()
{
	return 0;
}


template<class T, class TUPLE, size_t... IDXS> inline constexpr
typename TypeMixture_Impl<T>::IntType make_0_impl(const TUPLE& t, std::index_sequence<IDXS...>)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	//constexpr IntType o = 0;
	//constexpr IntType o = ( (cal_make<T, IDXS>(t) | cal_make<T, IDXS - 1>(t)), ... );
	return ( (cal_make<T, IDXS>(t)), ... );
	//return getVal<T, cal_make<T, IDXS>(t), ...>();
	//return Cal<T
}

template<class T, class... ARGS> inline constexpr
typename TypeMixture_Impl<T>::IntType make_0(const Tuple_T<ARGS...>& t)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	//return make_0_impl<T>(t, std::index_sequence_for<ARGS...>{});
	//return Cal<T, sizeof...(ARGS)>::get(t);
	//return cal_make<T, 1>(t);

	return NMSP_IDENTITY(sizeof...(ARGS));
}

template<class T, class... ARGS> inline constexpr
typename TypeMixture_Impl<T>::IntType test4(const Tuple_T<ARGS...>& t)
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;
	constexpr auto o = ( 0 | (sCast<IntType>(tupleGet<0>(t)) << TM::_s_calOffset<0>()) );
	return sCast<IntType>(o);
	//return test3<T, 0, 0>(t);
}


template <class T, class TUPLE, size_t... IDXS>
static constexpr auto makeTMValue_impl(const TUPLE& t, IntSeq_T<size_t, IDXS...> indices) /* -> std::array<INT_T, sizeof...(IDXS)> */
{
	using TM		= TypeMixture_T<T>;
	using IntType	= typename TM::IntType;

	constexpr auto off	= makeTM_offsets<T>;
	//constexpr std::array<IntType, sizeof...(IDXS)> arr{ (sCast<IntType>( t.get<IDXS>() ) << off[IDXS])...};
	return  ( sCast<IntType>(0) |  (sCast<IntType>( t.get<IDXS>() ) << off[IDXS]), ...);
}

template <class T, class... ARGS>
static constexpr auto makeTMValue(const Tuple_T<ARGS...>& t)
{
	NMSP_ASSERT(false, "not working");
	using TM = TypeMixture_T<T>;
	auto indices = IdxSeq_T<TM::s_kElementCount>{};
	return makeTMValue_impl<T>(t, indices);
}

#endif // 0
#endif // 0

#if 0
#pragma mark --- TestEnum-Impl ---
#endif // 0
#if 1

// for example only
enum class TestEnum : int;
template<>
struct TypeMixture_Impl<TestEnum>
{
	using Types							= Tuple_T<int, u8, u8>;
	static constexpr size_t s_kSizes[3] =		 {  4,	2,	4};
};

enum class TestEnum : int
{
	k1 = NMSP_TM_MAKE(TestEnum, 1, (u8)1, (u8)1),
	k2 = 20,
	k3 = TypeMixture_T<TestEnum>::_addValue<1, 1, 1>(),
	k4 = TypeMixture_T<TestEnum>::_addValue<1, 1, 1>(),
	k5 = Tuple_T<int, u8, u8>{1, (u8)2, (u8)1}.get<0>(),
	k6 = TM<TestEnum>::make(1, 1, 1),
	k7 = TypeMixture_T<TestEnum>::offsets(1),
};

#endif // 1



}