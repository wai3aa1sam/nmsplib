#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_JOB_SYSTEM || NMSP_TEST_ALL_MODULE || 1

#include <nmsp_job_system.h>

#include <nmsp_stl/extra/nmspFunction.h>

#include <conio.h>

namespace nmsp {

static constexpr int s_kTestCount = 100000;


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
		(_jobValids.emplace_back(makeUPtr_T<CheckJobValid>(nmsp::forward<JOB>(job), _jobValids.size())), ...);
		return tuple;
	}

	template<class... JOB> 
	auto bypassSubmitEmplace(JOB&&... job)
	{
		(_jobValids.emplace_back(makeUPtr_T<CheckJobValid>(nmsp::forward<JOB>(job), _jobValids.size())), ...);
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
			if (!e.jobHandle()->dispatchJob())
			{
				continue;
			}

			for (auto& jh : e._runAfter)
			{
				auto* jobValid = getJobValid(jh);
				if (!jobValid->jobHandle()->dispatchJob())
				{
					continue;
				}
				
				bool isValid = e._startTime > jobValid->_startTime && e._endTime > jobValid->_endTime;
				bool isValidTime = !math::equals(e._startTime, -1.0) && !math::equals(e._endTime, -1.0)
									&& !math::equals(jobValid->_startTime, -1.0) && !math::equals(jobValid->_endTime, -1.0);

				throwIf(!isValid || !isValidTime, "runAfter failed: x_id: {}, y_id: {}, isValid: {}, isValidTime: {}", e._id, jobValid->_id, isValid, isValidTime);
				throwIf(!isValid || !isValidTime, "");
			}

			for (auto& jh : e._runBefore)
			{
				auto* jobValid = getJobValid(jh);
				if (!jobValid->jobHandle()->dispatchJob())
				{
					continue;
				}

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

template<class T>
class TestJob_Base : public T
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

public:
	Vector_T<i64>	_result;
	const char*		_name = nullptr;
	Test_JobFlow*	_tjf;

	CheckJobValid* _jobValid = nullptr;

	u64 _id = CheckJobValid::s_kInvalid;
};

class TestJobParFor : public TestJob_Base<JobParFor_Base>
{
public:

	virtual void execute(const JobArgs& args) override 
	{

	}
};

class TestJobFor : public TestJob_Base<JobFor_Base>
{
public:

	virtual void execute(const JobArgs& args) override 
	{

	}
};

class TestJob : public TestJob_Base<Job_Base>
{
public:

	virtual void execute() override 
	{

	}
};

template<class T, class ENABLE = EnableIf<IsSame<T, JobParFor_Base> > >
struct SelectJobType
{
	using Type = TestJobParFor;
};

template<class T>
struct SelectJobType<T, EnableIf<IsSame<T, JobFor_Base> > >
{
	using Type = TestJobFor;
};

template<class T>
struct SelectJobType<T, EnableIf<IsSame<T, Job_Base> > >
{
	using Type = TestJob;
};

template<class T, class ENABLE = void >
class TestJobCluster_Base;

template<class T>
class TestJobCluster_Base<T, EnableIf<IsSame<T, JobParFor_Base> || IsSame<T, JobFor_Base> > > : public TestJob_Base<JobCluster_Base<T> >
{
public:
	TestJobCluster_Base(u64 id, Test_JobFlow* tjf)
	{
		_id = id;
		_tjf = tjf;
	}

	virtual void onSetup(JobHandle_T hnd) override
	{
		_id += clusterArgs().clusterId;
		_tjf->bypassSubmitEmplace(hnd);
		_jobValid = _tjf->getJobValid(hnd);
	}

	virtual void execute(const JobArgs& args) override 
	{
		OsUtil::sleep_ms(1);
	}
};

template<class T>
class TestJobCluster_Base<T, EnableIf<IsSame<T, Job_Base> > > : public TestJob_Base<JobCluster_Base<T> >
{
public:
	TestJobCluster_Base(u64 id, Test_JobFlow* tjf)
	{
		_id = id;
		_tjf = tjf;
	}

	virtual void onSetup(JobHandle_T hnd) override
	{
		_id += info().batchId;
		_tjf->bypassSubmitEmplace(hnd);
		_jobValid = _tjf->getJobValid(hnd);
	}

	virtual void execute() override
	{
		OsUtil::sleep_ms(1);
	}
};

void testOnBeginEnd(size_t testCount = s_kTestCount)
{

	{
		JobSystem_T::instance()->setSingleThreadMode(true);

		auto h1 = JobSystem_T::instance()->createEmptyJob();
		auto h2 = JobSystem_T::instance()->createEmptyJob();
		auto h3 = JobSystem_T::instance()->createEmptyJob();

		auto h3_0 = JobSystem_T::instance()->createEmptyJob();
		auto h3_1 = JobSystem_T::instance()->createEmptyJob();
		auto h3_2 = JobSystem_T::instance()->createEmptyJob();

		h3_0->setParent(h3);
		h3_1->setParent(h3);
		h3_2->setParent(h3);

		h3->setParent(h2);
		h2->setParent(h1);

		JobSystem_T::instance()->submit(h3_0);
		JobSystem_T::instance()->submit(h3_1);
		JobSystem_T::instance()->submit(h3_2);

		JobSystem_T::instance()->submit(h3);
		JobSystem_T::instance()->submit(h2);
		JobSystem_T::instance()->submit(h1);

		JobSystem_T::instance()->waitForComplete(h1);

	}

	{
		using JobType = TestJobParFor;

		JobSystem_T::instance()->setSingleThreadMode(false);

		static constexpr int s_kJobCount = 11;

		for (size_t k = 0; k < testCount; k++)
		{
			#if 1
			auto sa = makeScopedAction(
				[&] () { _log("// --- Test {} Start",	k); }
			,	[&] () { _log("// --- Test {} End",		k); }
			);
			#endif // 0


			Test_JobFlow jf;

			Vector_T<UPtr_T<JobType> > parForJobs;
			Vector_T<JobHandle_T> jobHandles;

			for (size_t i = 0; i < s_kJobCount; i++)
			{
				auto& e = parForJobs.emplace_back(makeUPtr_T<JobType>());
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
}

void testJobCluster(size_t testCount = s_kTestCount)
{
	HiResTimer_T timer;
	static constexpr double frameTime = 1 / 60.0;

	auto loopCount = 10000;
	auto minBatchSize = 200;

	{
		//using JobType = TestJobCluster_Base<Job_Base>;
		using JobType = TestJobParFor;
		//using JobClusterType = TestJobCluster_Base<Job_Base>;
		using JobClusterType = TestJobCluster_Base<JobParFor_Base>;

		//using JobClusterType = TestJobCluster2;
		

		JobSystem_T::instance()->setSingleThreadMode(false);

		static constexpr int s_kJobCount = 11;

		for (size_t k = 0; k < testCount; k++)
		{
			#if 1
			auto sa = makeScopedAction(
				[&] () { _log("// --- Test {} Start",	k); }
			,	[&] () { _log("// --- Test {} End",		k); }
			);
			#endif // 0


			Test_JobFlow jf;

			Vector_T<UPtr_T<JobType> > parForJobs;
			Vector_T<JobHandle_T> jobHandles;

			for (size_t i = 0; i < s_kJobCount; i++)
			{
				auto& e = parForJobs.emplace_back(makeUPtr_T<JobType>());
				auto& jh = jobHandles.emplace_back(e->prepareDispatch(100, 32));
				jf.emplace(jh);
				e->setup(i, &jf);
			}

			Vector_T<UPtr_T<JobClusterType>, JobSystemTraits::s_kEstLogicalThreadCount> jobClusters;
			auto jobClusterHnd = JobCluster::dispatch(jobClusters, loopCount, minBatchSize, s_kJobCount, &jf);

			//jf.xDependOnY(jobHandles[2],	jobHandles[10]);
			//jf.xDependOnY(jobHandles[1],	jobHandles[0]);
			//jf.xDependOnY(jobHandles[2],	jobHandles[0]);
			//jf.xDependOnY(jobHandles[3],	jobHandles[1]);
			//jf.xDependOnY(jobHandles[3],	jobHandles[2]);
			//jf.xDependOnY(jobHandles[4],	jobHandles[3]);
			//jf.xDependOnY(jobHandles[5],	jobHandles[4]);
			//jf.xDependOnY(jobHandles[6],	jobHandles[3]);
			//jf.xDependOnY(jobHandles[7],	jobHandles[6]);
			//jf.xDependOnY(jobHandles[8],	jobHandles[7]);
			//jf.xDependOnY(jobHandles[9],	jobHandles[6]);

			jf.emplace(jobClusterHnd);
			//jf.xDependOnY(jobHandles[5],	jobClusterHnd);
			
			jf.runAndWait();

			JobSystem_T::instance()->_internal_nextFrame();

			/*auto time = timer.get();
			if (time < frameTime)
			{
				OsUtil::sleep_ms(sCast<int>(frameTime * 1000));
				timer.reset();
			}*/
		}
	}

	
}

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
					//testOnBeginEnd();
					testJobCluster();
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



