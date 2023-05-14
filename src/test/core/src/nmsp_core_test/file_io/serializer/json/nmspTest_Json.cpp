#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_FILE_IO || NMSP_TEST_ALL_MODULE

#include <nmsp_file_io.h>
#include <nmsp_file_io/serializer/json/nmspJson.h>

namespace nmsp {


template<class T>
struct TempTestJsonInner
{
	T inner;
};

template<class T>
struct TempTestJson
{
	T t;
};

struct TestOnJson
{
	template<class SE> friend struct JsonIO;

	TestOnJson()
	{
		size_t N = 5;
		_vI32.resize(N);
		_vTmpTestJsonInner.resize(N);
		for (int i = 0; i < N; i++)
		{
			_vI32[i] = i;
		}

		_vTmpTestJsonInner.resize(N);
		for (int i = 0; i < N; i++)
		{
			_vI32[i] = i;
		}
		
	}

	i32 a;
	i32 b;
	i32 c;
	TempTestJson<TempTestJsonInner<i32> > ttj;
	StringT str;
	TempStringA_T<> tmpStr;
	bool bool_;
	Vector_T<int, 32> _vI32;
	Vector_T<TempStringA_T<>, 32> _vTmpStr;
	Vector_T<TempTestJsonInner<i32>, 32> _vTmpTestJsonInner;

	ColorType ct = ColorType::BC6h;
};

template<class T>
struct JsonIO<TempTestJsonInner<T> >
{
	template<class SE>
	static void onJson(SE& se, TempTestJsonInner<T>& v)
	{
		NMSP_NAMED_FIXED_IO(se, v, inner);
	}
};

template<class T>
struct JsonIO<TempTestJson<T> >
{
	template<class SE>
	static void onJson(SE& se, TempTestJson<T>& v)
	{
		NMSP_NAMED_FIXED_IO(se, v, t);
	}
};

template<>
struct JsonIO<TestOnJson >
{
	template<class SE>
	static void onJson(SE& se, TestOnJson& v)
	{
		NMSP_NAMED_FIXED_IO(se, v, a);
		NMSP_NAMED_FIXED_IO(se, v, b);
		NMSP_NAMED_FIXED_IO(se, v, c);
		NMSP_NAMED_FIXED_IO(se, v, ttj);
		NMSP_NAMED_FIXED_IO(se, v, str);
		NMSP_NAMED_FIXED_IO(se, v, tmpStr);
		NMSP_NAMED_FIXED_IO(se, v, bool_);
		NMSP_NAMED_FIXED_IO(se, v, _vI32);
		NMSP_NAMED_FIXED_IO(se, v, _vTmpStr);
		NMSP_NAMED_FIXED_IO(se, v, _vTmpTestJsonInner);
		NMSP_NAMED_FIXED_IO(se, v, ct);
	}
};

class Test_Json : public UnitTest
{
public:
	void test()
	{
		{
			using Json = nlohmann::json;
			Json j;
			j["key"] = 12;

			_NMSP_DUMP_VAR(j.dump(4));
			//j.begin();
		}


		{
			Json_T j;
			JsonSerializer_T se{j};
			TestOnJson t;
			size_t N = 5;
			t._vTmpStr.resize(5);
			for (size_t i = 0; i < N; i++)
			{
				StrUtil::convertToStr(t._vTmpStr[i], i);
				//t._vTmpStr[i] = StrUtil::toStr(i);
			}
			se.fixed_io(t);

			_NMSP_DUMP_VAR(j.dump(4));

			TestOnJson t2;

			{
				auto str = j.dump(4);
				Json_T j2 = Json_T::parse(str.begin(), str.end());

				JsonDeserializer_T dse{ j2 };
				dse.fixed_io(t2);
				NMSP_TEST_CHECK(t._vTmpStr == t2._vTmpStr);
			}

			if (!Path::isExist(fmtAs_T<StringT>("{}/asset", Path::getCurrentDir())))
			{
				Path::setCurrentDir("../../../../../example/Test000");
				_NMSP_DUMP_VAR(Path::getCurrentDir());
			}

			JsonUtil::writeFileIfChanged(StrViewA_T{ "JsonUtil_text.txt" }, t2, true);

			TestOnJson t3;
			JsonUtil::readFile(StrViewA_T{ "JsonUtil_text.txt" }, t3);
			NMSP_TEST_CHECK(t2._vTmpStr == t3._vTmpStr);

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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Json);


}


void test_Json()
{
	_NMSP_PROFILE_SECTION("test_Json");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Json, test());
}


#endif // NMSP_TEST_MODULE_STL



