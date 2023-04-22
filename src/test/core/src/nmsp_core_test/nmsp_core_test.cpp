#include "nmsp_core_test-pch.h"

#if NMSP_TEST_ALL_MODULE
	#include <nmsp_core.h>
#endif // NMSP_TEST_ALL_MODULE

void run_temp_test()
{
	//NMSP_RUN_TEST(test_Log);
	//NMSP_RUN_TEST(test_Profiler);
	//NMSP_RUN_TEST(test_Math);
	NMSP_RUN_TEST(test_OS);
	NMSP_RUN_TEST(test_FileStream);
	NMSP_RUN_TEST(test_NativeUI);
}

// TODO: add a test manager class, then no need add to here
void run_all_test()
{
	#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_Vector);
	NMSP_RUN_TEST(test_String);

	#endif // NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

	#if NMSP_TEST_MODULE_OS || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_OS);

	#endif // NMSP_TEST_MODULE_MATH || NMSP_TEST_ALL_MODULE

	#if NMSP_TEST_MODULE_LOG || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_Log);

	#endif // NMSP_TEST_MODULE_LOG || NMSP_TEST_ALL_MODULE

	#if NMSP_TEST_MODULE_PROFILER || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_Profiler);

	#endif // NMSP_TEST_MODULE_PROFILER || NMSP_TEST_ALL_MODULE


	#if NMSP_TEST_MODULE_MATH || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_Math);

	#endif // NMSP_TEST_MODULE_MATH || NMSP_TEST_ALL_MODULE
}

#if !NMSP_ENABLE_FUZZ_TESTING

int main(int argc, char* argv[])
{
	using namespace nmsp;

	int exitCode = 0;
	UnitTestManager unitTestManager;
	unitTestManager.create();

	{
		MemoryLeakReportScope reportScope;
		_NMSP_PROFILE_FRAME();
		{
			#if 1
			run_temp_test();
			#else
			run_all_test();
			#endif // 1
		}
	}
	#if NMSP_ENABLE_BENCHMARK
	{
		UnitTestManager::instance()->benchmark(&argc, argv);
	}
	#endif // 0
	
	return exitCode;
}

#else

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * Data, size_t Size) 
{
	return 0;
}

#endif // !NMSP_ENABLE_FUZZ_TESTING


