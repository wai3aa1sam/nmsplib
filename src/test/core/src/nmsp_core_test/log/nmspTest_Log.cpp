#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_LOG || NMSP_TEST_ALL_MODULE

#include <nmsp_log.h>

namespace nmsp {

class Test_Log : public UnitTest
{
public:
	void test()
	{
		#if 1
		Logger_T logger;
		{
			auto cd = Logger_T::makeCD();
			//cd.coreOutputFilepath = "../../../../../../log/log.txt";
			logger.create(cd);
		}
		NMSP_LOG("Hello World {} {}", 123, "Bye");
		NMSP_CORE_LOG("Hello World {} {}", 123, "Bye");

		{
			class NT : public NativeThread
			{
			public:
				virtual ~NT() { join(); }
				virtual void* onRoutine() override
				{
					NMSP_LOG("Hello World {} {}", 123, "Bye");
					NMSP_CORE_LOG_DEBUG("Hello World {} {}", 123, "Bye");

					return nullptr;
				}
			};
			{
				NT nt;
				auto cd = NT::makeCD();
				//cd.name = "Render Thread";
				cd.affinityIdx = 10;
				nt.create(cd);
			}
		}


		{
			{
				auto cd = Logger_T::makeCD();
				Logger_T::instance();

				Logger_T::instance();
				Logger_T::instance();
				Logger_T::instance();

			}
			NMSP_LOG("Hello World {} {}", 123, "Bye");
		}

		#endif // 1

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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_Log);



}


void test_Log()
{
	_NMSP_PROFILE_SECTION("test_Log");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_Log, test());
}


#endif // NMSP_TEST_MODULE_STL



