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


class CheckJobValid
{
public:
	static constexpr u64 s_kInvalid = ~u64(0);

	CheckJobValid(JobHandle_T job, u64 id)
	{
		_job = job;
		_id = id;
	}

	JobHandle_T jobHandle() { return _job; }

	bool isValidId() const { return _id != s_kInvalid; }

	u64 _id = s_kInvalid;

public:
	double _startTime	= -1.0f;
	double _endTime		= -1.0f;

	JobHandle_T				_job = nullptr;
	Vector_T<JobHandle_T>	_runBefore;
	Vector_T<JobHandle_T>	_runAfter;
};

class Test_JobFlow
{
public:
	using JobHandle = JobHandle_T;

	Test_JobFlow()
	{
		getTime();
	}

	template<class... JOB> 
	auto emplace(JOB&&... job)
	{
		auto tuple = _jf.emplace(nmsp::forward<JOB>(job)...);
		(_jobValids.emplace_back(makeUPtr<CheckJobValid>(nmsp::forward<JOB>(job), _jobValids.size())), ...);
		return tuple;
	}

	template<class... JOB>
	void xDependOnY(JobHandle x, JOB&&... y)
	{
		_jf.xDependOnY(x, nmsp::forward<JOB>(y)...);

		auto* x_jobValid = getJobValid(x);
		(x_jobValid->_runAfter.emplace_back(nmsp::forward<JOB>(y)), ...);

		(_xRunBeforeY(nmsp::forward<JOB>(y), x), ...);
	}

	void run() { _jf.run(); }
	void runAndWait() 
	{ 
		_jf.runAndWait();
		checkValid();
	}

	
	static double getTime() { static HiResTimer_T			_timer; return _timer.get(); }

	CheckJobValid* getJobValid(u64 id)
	{
		for (auto& jv : _jobValids)
		{
			auto& e = *jv;
			if (e._id == id && e._id != CheckJobValid::s_kInvalid)
				return &e;
		}

		NMSP_ASSERT(false, "");
		return nullptr;
	}

	CheckJobValid* getJobValid(JobHandle jh)
	{
		for (auto& jv : _jobValids)
		{
			auto& e = *jv;
			if (e.jobHandle() == jh)
				return &e;
		}

		NMSP_ASSERT(false, "");
		return nullptr;
	}

private:
	void _xRunBeforeY(JobHandle x, JobHandle y)
	{
		auto* x_jobValid = getJobValid(x);
		(x_jobValid->_runBefore.emplace_back(y));
	}

	void checkValid()
	{
		for (auto& jv : _jobValids)
		{
			auto& e = *jv;

			for (auto& jh : e._runAfter)
			{
				auto* jobValid = getJobValid(jh);
				
				bool isValid = e._startTime > jobValid->_startTime && e._endTime > jobValid->_endTime;
				bool isValidTime = !math::equals(e._startTime, -1.0) && !math::equals(e._endTime, -1.0)
									&& !math::equals(jobValid->_startTime, -1.0) && !math::equals(jobValid->_endTime, -1.0);

				throwIf(!isValid || !isValidTime, "runAfter failed: x_id: {}, y_id: {}, isValid: {}, isValidTime: {}", e._id, jobValid->_id, isValid, isValidTime);
				throwIf(!isValid || !isValidTime, "");
			}

			for (auto& jh : e._runBefore)
			{
				auto* jobValid = getJobValid(jh);
				
				bool isValid = e._startTime < jobValid->_startTime && e._endTime < jobValid->_endTime;
				bool isValidTime = !math::equals(e._startTime, -1.0) && !math::equals(e._endTime, -1.0)
									&& !math::equals(jobValid->_startTime, -1.0) && !math::equals(jobValid->_endTime, -1.0);

				throwIf(!isValid || !isValidTime, "runAfter failed: x_id: {}, y_id: {}, isValid: {}, isValidTime: {}", e._id, jobValid->_id, isValid, isValidTime);
				throwIf(!isValid || !isValidTime, "");
			}
		}
	}

public:
	JobFlow_T _jf;
	Vector_T<UPtr_T<CheckJobValid>>	_jobValids;
};


class SolvePrimeParForJob : public JobParFor_Base
{
public:

	void setup(u64 id, Test_JobFlow* tjf)
	{
		_id = id;
		_tjf = tjf;

		_jobValid = tjf->getJobValid(_id);
	}

	virtual void onBegin() override
	{
		NMSP_PROFILE_SCOPED();

		Base::onBegin();

		_jobValid->_startTime = Test_JobFlow::getTime();
		//_NMSP_LOG("name: {} --- onBegin()\n", _id);
	}

	virtual void onEnd() override
	{
		NMSP_PROFILE_SCOPED();

		Base::onEnd();

		_jobValid->_endTime = Test_JobFlow::getTime();
		//_NMSP_LOG("name: {} --- onEnd()\n", _id);
	}

	void execute(const JobArgs& args) override 
	{
	}

public:
	Vector_T<i64>	_result;
	const char*		_name = nullptr;
	Test_JobFlow*	_tjf;

	CheckJobValid* _jobValid = nullptr;

	u64 _id = CheckJobValid::s_kInvalid;
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
					JobSystem_T::instance()->setSingleThreadMode(false);

					static constexpr int s_kTestCount = 100000;
					static constexpr int s_kJobCount = 11;

					for (size_t k = 0; k < s_kTestCount; k++)
					{
						#if 1
						auto sa = makeScopedAction(
							[&] () { _log("// --- Test {} Start",	k); }
						,	[&] () { _log("// --- Test {} End",		k); }
						);
						#endif // 0


						Test_JobFlow jf;

						Vector_T<UPtr_T<SolvePrimeParForJob> > parForJobs;
						Vector_T<JobHandle_T> jobHandles;

						for (size_t i = 0; i < s_kJobCount; i++)
						{
							auto& e = parForJobs.emplace_back(makeUPtr<SolvePrimeParForJob>());
							auto& jh = jobHandles.emplace_back(e->prepareDispatch(100, 64));
							jf.emplace(jh);
							e->setup(i, &jf);
						}
						#if 1

						jf.xDependOnY(jobHandles[2],	jobHandles[10]);
						jf.xDependOnY(jobHandles[1],	jobHandles[0]);
						jf.xDependOnY(jobHandles[2],	jobHandles[0]);
						jf.xDependOnY(jobHandles[3],	jobHandles[1]);
						jf.xDependOnY(jobHandles[3],	jobHandles[2]);
						jf.xDependOnY(jobHandles[4],	jobHandles[3]);
						jf.xDependOnY(jobHandles[5],	jobHandles[4]);
						jf.xDependOnY(jobHandles[6],	jobHandles[3]);
						jf.xDependOnY(jobHandles[7],	jobHandles[6]);
						jf.xDependOnY(jobHandles[8],	jobHandles[7]);
						jf.xDependOnY(jobHandles[9],	jobHandles[6]);

						jf.runAndWait();

						#else

						jobHandles[2]->runAfter(jobHandles[10]);
						jobHandles[1]->runAfter(jobHandles[0]);
						jobHandles[2]->runAfter(jobHandles[0]);
						jobHandles[3]->runAfter(jobHandles[1]);
						jobHandles[3]->runAfter(jobHandles[2]);
						jobHandles[4]->runAfter(jobHandles[3]);
						jobHandles[5]->runAfter(jobHandles[4]);
						jobHandles[6]->runAfter(jobHandles[3]);
						jobHandles[7]->runAfter(jobHandles[6]);
						jobHandles[8]->runAfter(jobHandles[7]);
						jobHandles[9]->runAfter(jobHandles[6]);

						JobSystem_T::instance()->submit(jobHandles[0]);
						JobSystem_T::instance()->submit(jobHandles[10]);

						JobSystem_T::instance()->waitForComplete(jobHandles[5]);
						JobSystem_T::instance()->waitForComplete(jobHandles[8]);
						JobSystem_T::instance()->waitForComplete(jobHandles[9]);

						#endif // 0


						JobSystem_T::instance()->_internal_nextFrame();
					}
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



