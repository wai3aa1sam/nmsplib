#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"
#include "nmspIntSeq.h"

namespace nmsp {

#define NMSP_TBM_CALCULATE_VALUE_IMPL(I, T, TUPLE) ( TypeBitMixture_T<T>::getIntValue<I>(TUPLE) )
#define NMSP_TBM_MAKE_SELECT(COUNT)		NMSP_IDX_SEQ_##COUNT
#define NMSP_TBM_MAKE(T, ...) \
NMSP_IDENTITY(NMSP_CALL(NMSP_TBM_MAKE_SELECT, NMSP_VA_ARGS_COUNT(__VA_ARGS__)) (|, NMSP_TBM_CALCULATE_VALUE_IMPL, NMSP_ARGS(, T, TypeBitMixture_T<T>::Types(__VA_ARGS__) ) ))

#if 0
#pragma mark --- TypeBitMixture_T-Decl ---
#endif // 0
#if 1

template<class T, class IMPL>	struct TypeBitMixture_T;
template<class T>				struct TypeBitMixture_Impl;

template<class T>
struct TypeBitMixture_Impl
{
	//using Types							= Tuple_T<int, u8, u8>;
	//static constexpr size_t s_kSizes[3]	=		 {  4,	2,	4};
};

template<class T>
struct TBM : public TypeBitMixture_T<T, TypeBitMixture_Impl<T> >
{
	//using TypeBitMixture	= TypeBitMixture_T<T, TypeBitMixture_Impl<T> >;
	//using ValueType		= typename TypeBitMixture::ValueType;
	//using IntType		= typename TypeBitMixture::IntType;
	//using Types			= typename TypeBitMixture::Types;

	//template<size_t I> using ElementType = Types::ElementType<I>;

	//template<class VAL_T, class... ARGS> static constexpr ValueType make	(const VAL_T& v, ARGS&&... args) { return TypeBitMixture::make		(v, nmsp::forward<ARGS>(args)...); }
	//template<class VAL_T, class... ARGS> static constexpr IntType	makeInt	(const VAL_T& v, ARGS&&... args) { return TypeBitMixture::makeInt	(v, nmsp::forward<ARGS>(args)...); }
};

template<class T, class IMPL = TypeBitMixture_Impl<T> >
struct TypeBitMixture_T : public IMPL
{
public:
	using Base = IMPL;

	using ValueType = T;
	using IntType	= typename EnumInt<ValueType>;

	using Types = typename Base::Types;
	template<size_t I> using ElementType	= typename TupleElement<I, Types>;
	template<size_t I> using ElementIntType = typename EnumInt<ElementType<I> >;

	//template<size_t I> using ElementIntType = typename Types::ElementType<I>;

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
	template<size_t I, class VAL_T> static constexpr ValueType	getValue	(const VAL_T& v);

	template<size_t I> static constexpr ElementIntType<I>	getElementIntValue	(const ValueType& v);
	template<size_t I> static constexpr ElementType<I>		getElementValue		(const ValueType& v);

	template<size_t I>	static constexpr SizeType	offset();
						static constexpr SizeType	offsets(SizeType i);

private:
	template<size_t I = 0, class VAL_T>					static constexpr ValueType _make(const VAL_T& v);
	template<size_t I = 0, class VAL_T, class... ARGS>	static constexpr ValueType _make(const VAL_T& v, ARGS&&... args);

public:
	template<size_t... NS> static constexpr IntType _addValue(); // unused, legacy
};

template<class T, size_t N = TypeBitMixture_T<T>::s_kElementCount>
constexpr auto makeTBM_offsets
{
	[]() constexpr
	{
		using TBM = TypeBitMixture_T<T>;
		std::array<size_t, N> res{};
		//size_t res[N];
		res[0] = 0;
		for (int j = 1; j < N; ++j)
		{
			// eq to res[j] = accumulateTo<j>(TBM::s_kSizes);
			size_t sum = 0;
			for (int i = 0; i < j; ++i)
			{
				sum = std::plus()(sum, TBM::s_kSizes[i]);
			}
			res[j] = sum;
		}
		return res; 
	}()
};

#endif

#if 0
#pragma mark --- TypeBitMixtureOffset-Impl ---
#endif // 0
#if 1

template<size_t N>
struct TypeBitMixtureOffset
{
	constexpr 
	TypeBitMixtureOffset(const size_t sizes[])
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
#pragma mark --- TypeBitMixture_T-Impl ---
#endif // 0
#if 1

template<class T, class IMPL>
template<class VAL_T, class... ARGS> inline constexpr 
typename TypeBitMixture_T<T, IMPL>::ValueType 
TypeBitMixture_T<T, IMPL>::make(const VAL_T& v, ARGS&&... args)
{
	NMSP_S_ASSERT(s_kElementCount == sizeof...(ARGS) + 1);
	NMSP_S_ASSERT(s_kByteUsed <= s_kByteSize);
	return _make<0>(v, nmsp::forward<ARGS>(args)...);
}

template<class T, class IMPL>
template<class VAL_T, class... ARGS> inline constexpr
typename TypeBitMixture_T<T, IMPL>::IntType 
TypeBitMixture_T<T, IMPL>::makeInt(const VAL_T& v, ARGS&&... args)
{
	return sCast<IntType>(make(v, nmsp::forward<ARGS>(args)...));
}

template<class T, class IMPL>
template<size_t I> inline constexpr
typename TypeBitMixture_T<T, IMPL>::IntType TypeBitMixture_T<T, IMPL>::getIntValue(const Types& t)
{
	NMSP_S_ASSERT(s_kByteUsed <= s_kByteSize);
	return sCast<IntType>(getValue<I>(t.get<I>()));
}

template<class T, class IMPL>
template<size_t I, class VAL_T> inline constexpr
typename TypeBitMixture_T<T, IMPL>::ValueType TypeBitMixture_T<T, IMPL>::getValue(const VAL_T& v)
{
	return sCast<ValueType>(sCast<IntType>(v) << offset<I>());
}

template<class T, class IMPL>
template<size_t I> inline constexpr 
typename TypeBitMixture_T<T, IMPL>::ElementIntType<I>
TypeBitMixture_T<T, IMPL>::getElementIntValue(const ValueType& v)
{
	return sCast<ElementIntType<I> >(getElementValue<I>(v));
}

template<class T, class IMPL>
template<size_t I> inline constexpr
typename TypeBitMixture_T<T, IMPL>::ElementType<I>
TypeBitMixture_T<T, IMPL>::getElementValue(const ValueType& v)
{
	auto mask = BitUtil::setN(s_kSizes[I]);
	auto res = sCast<SizeType>(v) & mask;
	return sCast<ElementType<I> >((res) >> offset<I>());
}

template<class T, class IMPL>
template<size_t I> inline constexpr
typename TypeBitMixture_T<T, IMPL>::SizeType 
TypeBitMixture_T<T, IMPL>::offset()
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
typename TypeBitMixture_T<T, IMPL>::ValueType 
TypeBitMixture_T<T, IMPL>::_make(const VAL_T& v)
{
	return getValue<I>(v);
}

template<class T, class IMPL>
template<size_t I, class VAL_T, class... ARGS> inline constexpr 
typename TypeBitMixture_T<T, IMPL>::ValueType 
TypeBitMixture_T<T, IMPL>::_make(const VAL_T& v, ARGS&&... args)
{
	return sCast<ValueType>(sCast<IntType>(getValue<I>(v)) | sCast<IntType>(_make<I + 1>(nmsp::forward<ARGS>(args)...) ) );
}

template<class T, class IMPL> inline constexpr
typename TypeBitMixture_T<T, IMPL>::SizeType 
TypeBitMixture_T<T, IMPL>::offsets(SizeType i)
{
	constexpr auto off = makeTBM_offsets<T>;
	return off[i];
}

template<class T, class IMPL>
template<size_t... NS> inline constexpr
typename TypeBitMixture_T<T, IMPL>::IntType 
TypeBitMixture_T<T, IMPL>::_addValue()
{
	constexpr size_t N	= s_kElementCount;
	auto intSeq			= IntSeq_T<size_t, NS...>();
	static_assert(intSeq.size() == N, "");

	constexpr auto vals	= makeArray<decltype(intSeq)>;
	constexpr auto off	= makeTBM_offsets<T>;

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
	using TBM = TypeBitMixture_T<TestEnum>;

	constexpr size_t arr[] = { 10, 20, 30 };
	//return (TTT::Ty)accumulator(arr);
	return (TTT::Ty)TBM::_s_calOffset<1>();
	//return 10;
	//return TypeBitMixture_Helper<>;
}

enum Te
{
	//k = make( std::tuple<ColorModel, ColorElementType>{ ColorModel::R,		ColorElementType::UNorm8 } ),
};

#endif // 0

#if 0

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I == sizeof...(ARGS), typename TypeBitMixture_Impl<T>::IntType> _TypeBitMixture_internal_make(Tuple_T<ARGS...>  t)
{
	using TBM = TypeBitMixture_T<T>;
	using IntType = typename TBM::IntType;
	return RET_V;
}
template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I < sizeof...(ARGS), typename TypeBitMixture_Impl<T>::IntType> _TypeBitMixture_internal_make(Tuple_T<ARGS...>  t)
{
	using TBM = TypeBitMixture_T<T>;
	using IntType = typename TBM::IntType;
	//constexpr IntType o = sCast<IntType>(RET_V | (sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>()) );
	constexpr auto i = 0;//std::get<I>(t);
	//constexpr auto i = std::get<I>(Ts{ 1,		(u8)1, (u8)1 });
	//constexpr auto i = std::get<I>(t);

	//constexpr IntType o = TBM::addValue<RET_V, sCast<IntType>(i), TBM::_s_calOffset<I>() >();

	//constexpr IntType o = (IntType)(TBM::_s_calOffset<I>());
	return _TypeBitMixture_internal_make<T, i, I + 1, ARGS...>(t);
}

template<class T>
struct TypeBitMixture_Helper
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;

	template<class... ARGS>
	static constexpr T s_make_impl(Tuple_T<ARGS...> t)
	{
		return sCast<T>(_TypeBitMixture_internal_make<T, 0, 0, ARGS...>(t));
	}
};

template<class... ARGS> inline constexpr
int make(const Tuple_T<ARGS...>&  t)
{
	using TBM = typename TypeBitMixture_T<TestEnum>;
	using IntType = typename TBM::IntType;

	//return testOut<t.get<0>()>(t);
	//return ooo<10>();
	return (int)TypeBitMixture_Helper<TestEnum>::s_make_impl(t);
	//return (int)TBM::_s_calOffset<2>();
	//return (int)tupleGet<0>(t);
	//return (int)std::get<1>(t);
	//return 4 | (int)sCast<IntType>(tupleGet<2>(t)) << TBM::_s_calOffset<2>();
}
#endif // 0

#if 0

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I == sizeof...(ARGS), typename TypeBitMixture_Impl<T>::IntType> test3(const Tuple_T<ARGS...>& t)
{
	return RET_V;
}

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
EnableIf<I < sizeof...(ARGS), typename TypeBitMixture_Impl<T>::IntType> test3(const Tuple_T<ARGS...>& t)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	//constexpr IntType o = TBM::addValue<RET_V, 0, TBM::_s_calOffset<I>() >();
	//sCast<IntType>(std::get<I>(t))
	constexpr IntType o = RET_V | (std::get<I>(t) << TBM::_s_calOffset<I>());

	return test3<T, o, I + 1>(t);

	//return test3<T, RET_V | (std::get<I>(t) << TBM::_s_calOffset<I>()), I + 1>(t);
}

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t BEG, size_t END, class TUPLE> inline constexpr
EnableIf<BEG == END, typename TypeBitMixture_Impl<T>::IntType> test_(TUPLE&& t)
{
	return RET_V;
}

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t BEG, size_t END, class TUPLE> inline constexpr
EnableIf<BEG < END, typename TypeBitMixture_Impl<T>::IntType> test_(TUPLE&& t)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	//constexpr IntType o = TBM::addValue<RET_V, 0, TBM::_s_calOffset<I>() >();
	//sCast<IntType>(std::get<I>(t))
	//constexpr IntType o = RET_V | (std::get<I>(t) << TBM::_s_calOffset<I>());

	//return test_<T, TUPLE, RET_V | (std::get<TUPLE>(t) << TBM::_s_calOffset<BEG>()), BEG + 1, END>(nmsp::forward<TUPLE>(t));
	return test_<T, TUPLE, RET_V | (std::get<TUPLE>(t) << TBM::_s_calOffset<BEG>()), BEG + 1, END>(nmsp::forward<TUPLE>(t));

}

template<class T, class TUPLE> inline constexpr
typename TypeBitMixture_Impl<T>::IntType test2_(TUPLE&& t)
{
	return test_<T, 0, 0, 3>(nmsp::forward<TUPLE>(t));
}

template<class T, typename TypeBitMixture_Impl<T>::IntType RET_V, size_t I = 0, class... ARGS> inline constexpr
typename TypeBitMixture_Impl<T>::IntType test2(const Tuple_T<ARGS...>& t)
{
	return test3<T, 0, 0>(t);
}

template<class T, size_t I, class... ARGS> inline constexpr
typename TypeBitMixture_Impl<T>::IntType cal_make(const Tuple_T<ARGS...>& t)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	return sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>();
}

template<class T, size_t I, class... ARGS>
struct Cal
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;

	static constexpr IntType get(const Tuple_T<ARGS...>& t)
	{
		if constexpr (I == 0)
		{
			return sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>();
		}
		else
		{
			return Cal<T, I - 1, ARGS...>::get(t) | sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>();
		}
		//return sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>();
	}
	//static constexpr IntType value = sCast<IntType>(tupleGet<I>(t)) << TBM::_s_calOffset<I>();
};

template<class T, typename TypeBitMixture_Impl<T>::IntType... VALS>
typename TypeBitMixture_Impl<T>::IntType getValue()
{
	return 0;
}


template<class T, class TUPLE, size_t... IDXS> inline constexpr
typename TypeBitMixture_Impl<T>::IntType make_0_impl(const TUPLE& t, std::index_sequence<IDXS...>)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	//constexpr IntType o = 0;
	//constexpr IntType o = ( (cal_make<T, IDXS>(t) | cal_make<T, IDXS - 1>(t)), ... );
	return ( (cal_make<T, IDXS>(t)), ... );
	//return getValue<T, cal_make<T, IDXS>(t), ...>();
	//return Cal<T
}

template<class T, class... ARGS> inline constexpr
typename TypeBitMixture_Impl<T>::IntType make_0(const Tuple_T<ARGS...>& t)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	//return make_0_impl<T>(t, std::index_sequence_for<ARGS...>{});
	//return Cal<T, sizeof...(ARGS)>::get(t);
	//return cal_make<T, 1>(t);

	return NMSP_IDENTITY(sizeof...(ARGS));
}

template<class T, class... ARGS> inline constexpr
typename TypeBitMixture_Impl<T>::IntType test4(const Tuple_T<ARGS...>& t)
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;
	constexpr auto o = ( 0 | (sCast<IntType>(tupleGet<0>(t)) << TBM::_s_calOffset<0>()) );
	return sCast<IntType>(o);
	//return test3<T, 0, 0>(t);
}


template <class T, class TUPLE, size_t... IDXS>
static constexpr auto makeTBMValue_impl(const TUPLE& t, IntSeq_T<size_t, IDXS...> indices) /* -> std::array<INT_T, sizeof...(IDXS)> */
{
	using TBM		= TypeBitMixture_T<T>;
	using IntType	= typename TBM::IntType;

	constexpr auto off	= makeTBM_offsets<T>;
	//constexpr std::array<IntType, sizeof...(IDXS)> arr{ (sCast<IntType>( t.get<IDXS>() ) << off[IDXS])...};
	return  ( sCast<IntType>(0) |  (sCast<IntType>( t.get<IDXS>() ) << off[IDXS]), ...);
}

template <class T, class... ARGS>
static constexpr auto makeTBMValue(const Tuple_T<ARGS...>& t)
{
	NMSP_ASSERT(false, "not working");
	using TBM = TypeBitMixture_T<T>;
	auto indices = IdxSeq_T<TBM::s_kElementCount>{};
	return makeTBMValue_impl<T>(t, indices);
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
struct TypeBitMixture_Impl<TestEnum>
{
	using Types							= Tuple_T<int, u8, u8>;
	static constexpr size_t s_kSizes[3] =		 {  4,	2,	4};
};

enum class TestEnum : int
{
	k1 = NMSP_TBM_MAKE(TestEnum, 1, (u8)1, (u8)1),
	k2 = 20,
	k3 = TypeBitMixture_T<TestEnum>::_addValue<1, 1, 1>(),
	k4 = TypeBitMixture_T<TestEnum>::_addValue<1, 1, 1>(),
	k5 = Tuple_T<int, u8, u8>{ 1, (u8)2, (u8)1 }.get<0>(),
	k6 = TBM<TestEnum>::make(1, 1, 1),
	k7 = TypeBitMixture_T<TestEnum>::offsets(1),
	//k9 = Index<TypeBitMixture_T<TestEnum>::T1, TBM<TestEnum>::Types>::value,
	//k10 = Index<TypeBitMixture_T<TestEnum>::T2, TBM<TestEnum>::Types>::value,
	k11 = BitUtil::setN(4),
};

#endif // 1



}