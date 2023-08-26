#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_JOB_SYSTEM || NMSP_TEST_ALL_MODULE || 1

#include <nmsp_job_system.h>

#include <nmsp_stl/extra/nmspFunction.h>

#include <conio.h>

namespace nmsp {


class PrimeNumberSolver
{
public:
	static constexpr size_t s_kBatchSize = 1;

	static constexpr size_t	s_kPrimeStart = 1000000000LL;
	//static constexpr size_t	s_kPrimeStart	= 2;

	static constexpr size_t	s_kLoopCount = 16 * 1;

private:
	static bool isPrimeNumber(i64 v)
	{
		for (i64 i = 2; i < v; i++)
		{
			if (v % i == 0)
				return false;
		}
		return true;
	}

public:


};

class SolvePrimeParForJob : public JobParFor_Base
{
public:

	SolvePrimeParForJob(int id)
	{
		_id = id;
	}

	void setup()
	{

	}

	virtual void onBegin() override
	{
		Base::onBegin();

		_NMSP_LOG("id: {} --- onBegin()\n", _id);
	}

	virtual void onEnd() override
	{
		Base::onEnd();

		_NMSP_LOG("id: {} --- onEnd()\n", _id);
	}

	void execute(const JobArgs& args) override 
	{
	}

public:
	Vector_T<i64> _result;
	int _id;
};

class Test_JobFlow
{
public:

	JobFlow_T _jf;
};

class Test_JobSystem_OnBegin : public UnitTest
{
public:
	void test()
	{
		{
			JobSystem_T::init();
			auto jsysCDesc			= JobSystem_T::makeCDesc();
			jsysCDesc.workerCount	= OsTraits::logicalThreadCount();
			JobSystem_T::instance()->create(jsysCDesc);
		}

		{
			for (;;)
			{
				poll();

				_NMSP_PROFILE_SECTION("Test_Dispatch");
				_log("use job flow");

				{
					JobFlow_T jf;

					SolvePrimeParForJob parJob		{1};
					SolvePrimeParForJob parJob2		{2};

					auto [h1, h2] = jf.emplace(parJob.prepareDispatch(1000000, 64)
												, parJob2.prepareDispatch(100000, 64));

					h1->runAfter(h2);

					jf.runAndWait();
				}


				if (_isQuit || true)
				{
					break;
				}

			}
			
		}


		JobSystem_T::terminate();
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

	void poll()
	{
		if (_kbhit()) {
			int ch = 0;
			// Stores the pressed key in ch
			ch = _getch();
			_isQuit = true;

		}
	}

private:
	bool		_isQuit = false;
	//JobSystem_T _jsys;
};
NMSP_REGISTER_UNIT_TEST_CLASS(Test_JobSystem_OnBegin);


}


void test_JobSystem_OnBegin()
{
	_NMSP_PROFILE_SECTION("test_JobSystem_OnBegin");

	using namespace nmsp;
	NMSP_TEST_CASE(Test_JobSystem_OnBegin, test());
}


#endif // NMSP_TEST_MODULE_STL



