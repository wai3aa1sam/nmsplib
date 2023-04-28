#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os/file/nmspMemMapFile.h"

namespace nmsp {

class Test_MemMapFile : public UnitTest
{
public:
	void test()
	{
		{
			auto cd = MemMapFile_T::makeCDesc();
			MemMapFile_T mmf{};
			//cd.filename = "xxx.txt";
			try
			{
				mmf.open(cd);
				_NMSP_LOG("mmf: {}", std::string(mmf.strview().data()));
			}
			catch (...)
			{
				_NMSP_LOG("no file found");
			}
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_MemMapFile);


}


void test_MemMapFile()
{
	_NMSP_PROFILE_SECTION("test_MemMapFile");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_MemMapFile, test());
}


#endif // NMSP_TEST_MODULE_STL



