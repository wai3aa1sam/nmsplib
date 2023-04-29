#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os.h"

namespace nmsp {

class Test_Process : public UnitTest
{
public:
	void test()
	{
		{
			//Process_T process;
		}

		{
			CmdLine_T cli;
			cli.execute("echo Hello World");
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Process);


}


void test_Process()
{
	_NMSP_PROFILE_SECTION("test_Process");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Process, test());
}


#endif // NMSP_TEST_MODULE_STL



