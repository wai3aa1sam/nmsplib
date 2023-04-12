#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_PROFILER || NMSP_TEST_ALL_MODULE

namespace nmsp {

class Test_Profiler : public UnitTest
{
public:
	void test()
	{
		size_t n = 0;
		while (n < 10000)
		{
			NMSP_PROFILE_FRAME();

			NMSP_PROFILE_SECTION("TestLoop");
			//int* p = NMSP_ALLOC(p, 10); NMSP_UNUSED(p);
			n++;

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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Profiler);


}


void test_Profiler()
{
	_NMSP_PROFILE_SECTION("test_Profiler");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Profiler, test());
}


#endif // NMSP_TEST_MODULE_STL



