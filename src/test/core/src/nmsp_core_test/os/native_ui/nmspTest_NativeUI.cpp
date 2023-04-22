#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os/native_ui/nmspNativeUI.h"

namespace nmsp {

class Test_NativeUI : public UnitTest
{
public:
	void test()
	{
		{
			NativeUIWindow_T window;
			window.create(NativeUIWindow_T::makeCDesc());
			_NMSP_DUMP_VAR(NMSP_SRCLOC);

			//NativeUIApp_T app;
			//app.run(app.makeCDesc());
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_NativeUI);


}


void test_NativeUI()
{
	_NMSP_PROFILE_SECTION("test_NativeUI");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_NativeUI, test());
}


#endif // NMSP_TEST_MODULE_STL



