#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os/file/nmspFileStream.h"

namespace nmsp {

class Test_FileStream : public UnitTest
{
public:
	void test()
	{
		{
			auto cd= FileStream_T::makeCDesc();
			FileStream_T fs{};
			fs.openWrite("testFs.txt", false);
			
			StringT str;
			str = "get ur ass up";
			fs.writeBytes(makeByteSpan(str));
			fs.flush();
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_FileStream);


}


void test_FileStream()
{
	_NMSP_PROFILE_SECTION("test_FileStream");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_FileStream, test());
}


#endif // NMSP_TEST_MODULE_STL



