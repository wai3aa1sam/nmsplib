#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_FILE_IO || NMSP_TEST_ALL_MODULE

#include <nmsp_file_io.h>
#include <nmsp_file_io/image/nmspImage.h>

namespace nmsp {

class Test_Image : public UnitTest
{
public:
	void test()
	{
		Path::setCurrentDir("../../../../../example/Test000");
		_NMSP_DUMP_VAR(Path::getCurrentDir());

		Image_T image;
		image.loadPngFile("asset/texture/uvChecker.png");
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Image);


}


void test_Image()
{
	_NMSP_PROFILE_SECTION("test_Image");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Image, test());
}


#endif // NMSP_TEST_MODULE_STL



