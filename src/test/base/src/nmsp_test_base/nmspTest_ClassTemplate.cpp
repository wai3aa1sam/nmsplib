#include "nmsp_test_base/common/nmsp_test_base_common.h"
// #include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_TEMPLATE || NMSP_TEST_ALL_MODULE

namespace nmsp {

class Test_Template : public UnitTest
{
public:
	void test()
	{

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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Template);


}


void test_Template()
{
	_NMSP_PROFILE_SECTION("test_Template");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Template, test());
}


#endif // NMSP_TEST_MODULE_STL



