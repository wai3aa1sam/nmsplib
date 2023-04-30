#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_FILE_IO || NMSP_TEST_ALL_MODULE

#include <nmsp_file_io.h>

namespace nmsp {

class Test_FileIO : public UnitTest
{
public:
	void test()
	{
		nlohmann::json js;
		js.find("asdsd");

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



