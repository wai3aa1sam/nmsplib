#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_FILE_IO || NMSP_TEST_ALL_MODULE

#include <nmsp_file_io.h>

namespace nmsp {

template<class T>
constexpr T con(T t)
{
	return t;
}

template<class T>
constexpr T con2(T t)
{
	return con(t);
}


class Test_FileIO : public UnitTest
{
public:
	void test()
	{
		nlohmann::json js;
		js.find("asdsd");

		//_NMSP_LOG("{}", ColorModel::None);
		//_NMSP_LOG("{}", ColorType::Rb);

		{
			//auto res = TypeBitMixture_T<TestEnum>::s_make({ 1, (u8)2, (u8)4 });
			//_NMSP_LOG("TypeBitMixture_T<TestEnum>: {}", enumInt(res));
		}
		{
			/*Tuple_T t = { 1, 2.0f, 4.0f };
			constexpr size_t i = 0;
			t.get<0>();*/

			
			//decltype(t)::Base st;
			auto st = std::make_tuple(1, 2.0f, 4.0f);
			auto st0 = std::get<0>(st);
			_NMSP_LOG("{}", st0);

		}
		{
			auto t = std::make_tuple(1, 2.0f, "123");
			/*for (constexpr size_t i = 0; i < 3; i++)
			{
				auto t0 = std::get<i>(t);
				_NMSP_LOG("{}", t0);
			}*/
			/*for... (auto elem : t) {
				std::cout << elem << " "; 
			}*/

		}
		{
			auto t = std::make_tuple(1, 2.0f, "123");
			auto testFunc = [](auto& v, auto i)
			{
				_NMSP_LOG("{}", v);
			};
			//tupleLoop(testFunc, t);
		}

		{
			//constexpr int 
			//_NMSP_DUMP_VAR(sCast<int>(TestEnum::k));
			constexpr Tuple_T<int, u8> t = Tuple_T<int, u8>{1, (u8)2};
			constexpr auto t0	= std::get<0>(t); NMSP_UNUSED(t0);
			constexpr auto t0_1 = t.get<0>(); NMSP_UNUSED(t0_1);

			_NMSP_DUMP_VAR(t0_1);

		}
		{
			_NMSP_DUMP_VAR(enumInt(TestEnum::k1));
			_NMSP_DUMP_VAR(enumInt(TestEnum::k2));

			constexpr auto a = con2(4); NMSP_UNUSED(a);


		}

		{
			auto a = makeTBM_offsets<TestEnum>;
			_NMSP_DUMP_VAR(a[0], a[1], a[2]);
		}

		{
			/*size_t arr[3] = { 1, 2, 3 };
			auto cm = sCast < EnumInt<ColorModel> >(arr[0]);
			_NMSP_DUMP_VAR(cm);*/

		}

		{
			auto arr = makeArray<std::integer_sequence<size_t, 1, 2, 3>>;
			_NMSP_DUMP_VAR(arr[0]);
		}

		{
			//Array_T<int, 1> a;
			//std::array<int, 1> n;
		}

		{
			constexpr auto t = Tuple_T<int, u8, u8>{1, (u8)2, (u8)1};
			decltype(t)::ElementType<0> a = 10;
			_NMSP_DUMP_VAR(a);

			TypeBitMixture_T<TestEnum>::Types::ElementType<1> b = 20;
			_NMSP_DUMP_VAR(b);

			//auto tmArr = makeTBMValue<TestEnum>(t);
			constexpr auto ca = t.get<0>();
			_NMSP_DUMP_VAR(ca);
		}

		{
			//constexpr auto t = Tuple_T<int, u8, u8>{1, (u8)2, (u8)1};
			//TypeBitMixture_T<TestEnum>::s_make({1, 1, 1});

			constexpr auto a2 = TestEnum::k6;
			_NMSP_DUMP_VAR((int)a2);
		}

		{
			_NMSP_DUMP_VAR(ColorType::Rf);
			_NMSP_DUMP_VAR(ColorType::BC7);

			//_NMSP_DUMP_VAR(TBM<ColorType>::gett());

			_NMSP_DUMP_VAR(TBM<ColorType>::getElementValue<0>(ColorType::Rs));

			_NMSP_DUMP_VAR(ColorR_T<f32>::s_kColorModel);
			_NMSP_DUMP_VAR(ColorR_T<f32>::s_kColorElementType);
			_NMSP_DUMP_VAR((u16)ColorBC1_T::s_kColorType);
			_NMSP_DUMP_VAR(ColorBC1_T::s_kColorElementType);
			
			
		}
		{
			_NMSP_DUMP_VAR(BitUtil::setN(4));
		}
	}

	virtual void onSetup() override
	{
	}

	virtual void onTest() override
	{

	}

	virtual void onBenchmark() override
	{

	}

private:

};
NMSP_REGISTER_UNIT_TEST_CLASS(Test_FileIO);


}


void test_FileIO()
{
	_NMSP_PROFILE_SECTION("test_FileIO");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_FileIO, test());
}


#endif // NMSP_TEST_MODULE_STL



