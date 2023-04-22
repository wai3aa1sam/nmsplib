#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include <nmsp_os.h>

#include <nmsp_os/file/nmspFileSteam.h>

namespace nmsp {

class Test_OS : public UnitTest
{
public:
	void test()
	{
		{
			FileStream_T fs;
			auto v = fs.kInvalid(); NMSP_UNUSED(v);
			auto cd = FileStream_T::makeCD();
			
			FileStream_T fs2{cd};

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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_OS);



}


void test_OS()
{
	_NMSP_PROFILE_SECTION("test_OS");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_OS, test());
}


#endif // NMSP_TEST_MODULE_STL



