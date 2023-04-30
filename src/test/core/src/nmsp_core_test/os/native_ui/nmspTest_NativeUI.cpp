#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

#include "nmsp_os/native_ui/nmspNativeUI.h"

#include "nmsp_os/app/ProjectSetting.h"
#include "nmsp_os/file/nmspDirectory.h"

namespace nmsp {

class Test_NativeUI : public UnitTest
{
public:
	void test()
	{
		{
			class NTWnd : public NativeUIWindow_T
			{
			public:

				virtual void onUIMouseEvent(UIMouseEvent& ev) override
				{
					#define NMSP_TEST_MOUSE(func) func ? _log(#func) : nullptr;

					auto& MouseEv = ev;
					NMSP_TEST_MOUSE(MouseEv.isUp());
					NMSP_TEST_MOUSE(MouseEv.isDown());
					NMSP_TEST_MOUSE(MouseEv.isDragging());
					NMSP_TEST_MOUSE(MouseEv.isMove());
					NMSP_TEST_MOUSE(MouseEv.isScroll());

				}

				virtual void onUIKeyboardEvent(UIKeyboardEvent& ev) override
				{
					#define NMSP_TEST_MOUSE(func) func ? _log(#func) : nullptr;

					auto& keyEv = ev;
					NMSP_TEST_MOUSE(keyEv.isUp(UIKeyboardEventButton::A));
					NMSP_TEST_MOUSE(keyEv.isDown(UIKeyboardEventButton::A));
					NMSP_TEST_MOUSE(keyEv.isHold(UIKeyboardEventButton::A));

				}


				virtual void onCloseButton()
				{
					isQuit = true;
				}
				bool isQuit = false;
			};

			class NTApp : public NativeUIApp_T
			{
			public:
				NTApp()
				{
					_mainWnd = NMSP_NEW(_mainWnd);
					_mainWnd->create(_mainWnd->makeCDesc());
				}

			protected:
				virtual void onRun() override
				{
					
					while (!_mainWnd->isQuit)
					{
						

						pollMsg();
					}

					willQuit();
				}

				virtual void willQuit() override
				{
					_mainWnd->isQuit = true;
					NMSP_DELETE(_mainWnd);
				}

			protected:
				bool isQuit = false;
				NTWnd* _mainWnd = nullptr;
			};

			NTApp app;
			app.run(app.makeCDesc());
		}

		{
			ProjectSetting_T prjs;
			ProjectSetting_T::instance()->setProjectRoot("../../../../..");

			_NMSP_DUMP_VAR(Directory::getCurrent());

			AppBase_T app;
			
			_NMSP_DUMP_VAR(app.getExecutableFilename());
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



