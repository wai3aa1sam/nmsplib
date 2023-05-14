#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_JOB_SYSTEM || NMSP_TEST_ALL_MODULE

#include <nmsp_job_system.h>

#include <nmsp_stl/extra/nmspFunction.h>

namespace nmsp {

class Test_JobSystem : public UnitTest
{
public:
	void test()
	{
		{
			Function_T<void(void), 32> func{[]() {}};
			auto lamb = []()
			{
				int a = 1;
				_NMSP_DUMP_VAR(a);

			};
			func = lamb;

			func();
			_NMSP_DUMP_VAR(sizeof(func));
			_NMSP_DUMP_VAR(sizeof(lamb));

			_NMSP_DUMP_VAR(sizeof(LocalBuffer_T<12, 8>));
			_NMSP_DUMP_VAR(sizeof(MallocAllocator_T<8>));
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
NMSP_REGISTER_UNIT_TEST_CLASS(Test_JobSystem);


}


void test_JobSystem()
{
	_NMSP_PROFILE_SECTION("test_JobSystem");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_JobSystem, test());
}


#endif // NMSP_TEST_MODULE_STL



