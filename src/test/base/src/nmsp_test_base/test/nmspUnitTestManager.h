#pragma once

#include "../common/nmsp_test_base_common.h"
#include "nmspUnitTest.h"


namespace nmsp {

#if 0
#pragma mark --- UnitTestManager-Decl ---
#endif // 0
#if 1

class UnitTestManager : public NonCopyable
{
public:
	static UnitTestManager* instance();
	static UnitTestManager* create();
	static void				destroy();

	UnitTestManager();
	~UnitTestManager()	= default;

	void registerUnitTest(UnitTest* ut);
	void benchmark(int* argc, char* argv[]);

private:
	static UnitTestManager* s_instance;
};

#endif


}