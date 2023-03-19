#include "nmsp_core_test-pch.h"

#if NMSP_TEST_ALL_MODULE
	#include <nmsp_core.h>
#endif // NMSP_TEST_ALL_MODULE

void run_temp_test()
{
	#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

	NMSP_RUN_TEST(test_Vector);
	NMSP_RUN_TEST(test_String);

	#endif // NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE
}

#if !NMSP_ENABLE_FUZZ_TESTING

int main(int argc, char* argv[])
{
	using namespace nmsp;
	MemoryLeakReportScope reportScope;

	int exitCode = 0;
	{ 
		#if 1

		run_temp_test();

		#else

		#endif // 1
	}

	return exitCode;
}

#else

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * Data, size_t Size) 
{
	return 0;
}

#endif // !NMSP_ENABLE_FUZZ_TESTING


