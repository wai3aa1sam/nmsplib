#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#include <nmsp_stl/string/nmspStrUtil.h>

namespace nmsp {

class Test_StrUtil : public UnitTest
{
public:
	void test()
	{
		{
			#define NMSP_TRY_PARSE_TEST(T) \
			{ \
				T v; \
				bool valid = StrUtil::tryParse("20.689", v); \
				_NMSP_LOG("{} --- {} {}: [{}]", valid ? "prase succeed" : "prase failed", #T, "v", v); \
			} \
			//--------
			
			NMSP_TRY_PARSE_TEST(u8 );
			NMSP_TRY_PARSE_TEST(u16);
			NMSP_TRY_PARSE_TEST(u32);
			NMSP_TRY_PARSE_TEST(u64);

			NMSP_TRY_PARSE_TEST(i8 );
			NMSP_TRY_PARSE_TEST(i16);
			NMSP_TRY_PARSE_TEST(i32);
			NMSP_TRY_PARSE_TEST(i64);

			NMSP_TRY_PARSE_TEST(f32 );
			NMSP_TRY_PARSE_TEST(f64 );
			NMSP_TRY_PARSE_TEST(f128);


			#undef NMSP_TRY_PARSE_TEST
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_StrUtil);


}


void test_StrUtil()
{
	_NMSP_PROFILE_SECTION("test_StrUtil");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_StrUtil, test());
}


#endif // NMSP_TEST_MODULE_STL



