#include "nmsp_core_test/common/nmsp_core_test_common.h"

#if NMSP_TEST_MODULE_JOB_SYSTEM || NMSP_TEST_ALL_MODULE

#include <nmsp_job_system.h>

#include <nmsp_stl/extra/nmspFunction.h>

#include <conio.h>

namespace nmsp {

#if 1

class PrimeNumberSolver
{
public:
	static constexpr size_t s_kBatchSize = 4;

	static constexpr size_t	s_kPrimeStart = 1000000000LL;
	//static constexpr size_t	s_kPrimeStart	= 2;

	static constexpr size_t	s_kLoopCount = 16;

private:
	static bool s_isPrimeNumber(i64 v)
	{
		for (i64 i = 2; i < v; i++)
		{
			if (v % i == 0)
				return false;
		}
		return true;
	}

public:

	template<class... ARGS>
	class SolverJobT
	{
	public:
		SolverJobT(size_t primeStart_)
		{
			auto primeStart = primeStart_;

			_result.resize(s_kLoopCount);

			_numbers.resize(s_kLoopCount);
			for (size_t i = primeStart; i < primeStart + s_kLoopCount; i++)
			{
				_numbers[i - primeStart] = i;
			}
		}

		void execute()
		{
			NMSP_PROFILE_SCOPED();

			//_NMSP_LOG("=== i: {}", i);

			for (size_t i = 0; i < s_kLoopCount; i++)
			{
				bool isPrime = s_isPrimeNumber(_numbers[i]);
				_result[i] = isPrime;
			}
		}

		void execute(const JobArgs& args)
		{
			NMSP_PROFILE_SCOPED();

			auto i = args.loopIndex;
			//_NMSP_LOG("=== i: {}", i);

			bool isPrime = s_isPrimeNumber(_numbers[i]);
			_result[i] = isPrime;

			auto buf = fmtAs_T<TempStringA_T<> >("execute: {}", i);
			NMSP_PROFILE_LOG(buf.c_str());
		}

		void execute_submit()
		{
			NMSP_PROFILE_SCOPED();

			bool isPrime = s_isPrimeNumber(_numbers[i]);
			_result[i] = isPrime;
		}

		void print() const
		{
			_NMSP_LOG("=== result");
			size_t resultCount = 0;
			for (size_t i = 0; i < _result.size(); i++)
			{
				if (_result[i] == 1)
				{
					_NMSP_LOG("prime: {}", _numbers[i]);
					resultCount++;
				}
			}
			_NMSP_LOG("=== result count: {}", resultCount);
		}

	private:
		Vector_T<size_t> _numbers;
		Vector_T<int>   _result;
	};

	template<class... ARGS>
	class SolverJobT_testParFor : public JobParFor_Base<SolverJobT_testParFor<ARGS...>>, public SolverJobT<ARGS...>
	{
		using Base = SolverJobT<ARGS...>;
	public:
		SolverJobT_testParFor(size_t primeStart_)
			: Base(primeStart_)
		{
		}
	};

	template<class... ARGS>
	class SolverJobT_testFor : public JobFor_Base<SolverJobT_testFor<ARGS...>>, public SolverJobT<ARGS...>
	{
		using Base = SolverJobT<ARGS...>;
	public:
		SolverJobT_testFor(size_t primeStart_)
			: Base(primeStart_)
		{
		}
	};

	template<class... ARGS>
	class SolverJobT_test : public Job_Base<SolverJobT_test<ARGS...>>, public SolverJobT<ARGS...>
	{
		using Base = SolverJobT<ARGS...>;
	public:
		SolverJobT_test(size_t primeStart_)
			: Base(primeStart_)
		{
		}
	};

	using SolverJob_ParFor	= SolverJobT_testParFor<void>;
	using SolverJob_ParFor2 = SolverJobT_testParFor<void, void>;

	using SolverJob_For		= SolverJobT_testFor<void>;
	using SolverJob_For2	= SolverJobT_testFor<void, void>;

	using SolverJob			= SolverJobT_test<void>;
	using SolverJob2		= SolverJobT_test<void, void>;

	class Test_Dispatch
	{
	public:

		void test()
		{
			JobSystem_T _jsys;
			auto jsysCDesc = _jsys.makeCDesc();
			jsysCDesc.workerCount = OsTraits::logicalThreadCount();
			_jsys.create(jsysCDesc);
			{
				auto handle = solverJob_ParFor.dispatch(s_kLoopCount, s_kBatchSize);
				//auto handle = solverJob_For.dispatch(s_kLoopCount);
				//auto handle = solverJob.dispatch();
				handle->waitForComplete();
			}
				
			solverJob_ParFor.print();
			solverJob_For.print();
			solverJob.print();
		}

	private:
		PrimeNumberSolver::SolverJob_ParFor	solverJob_ParFor{PrimeNumberSolver::s_kPrimeStart};
		PrimeNumberSolver::SolverJob_For	solverJob_For	{PrimeNumberSolver::s_kPrimeStart};
		PrimeNumberSolver::SolverJob		solverJob		{PrimeNumberSolver::s_kPrimeStart};
	};


};


#endif // 1

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
		{

			for (;;)
			{
				poll();


				NMSP_PROFILE_FRAME();
				if (_isQuit || true)
				{
					NMSP_PROFILE_SECTION("Test_Dispatch");
					break;
				}

			}
			
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

		//NMSP_TEST_CASE(PrimeNumberSolver::Test_Dispatch, test());
		//NMSP_TEST_CASE(PrimeNumberSolver::Test_Dispatch, test());
		NMSP_TEST_CASE(PrimeNumberSolver::Test_Dispatch, test());


		{
			JobSystem_T _jsys;
			auto jsysCDesc = _jsys.makeCDesc();
			jsysCDesc.workerCount = OsTraits::logicalThreadCount();
			_jsys.create(jsysCDesc);

			auto* jsys = JobSystem_T::instance();

			JobHandle_T handle0 = nullptr;
			JobHandle_T handle1 = nullptr;

			PrimeNumberSolver::SolverJob_ParFor		solverJob_ParFor0(PrimeNumberSolver::s_kPrimeStart);
			PrimeNumberSolver::SolverJob_ParFor2	solverJob_ParFor1(PrimeNumberSolver::s_kPrimeStart + PrimeNumberSolver::s_kLoopCount * 1);

			PrimeNumberSolver::SolverJob_For		solverJob_For0(PrimeNumberSolver::s_kPrimeStart);
			PrimeNumberSolver::SolverJob_For2		solverJob_For1(PrimeNumberSolver::s_kPrimeStart + PrimeNumberSolver::s_kLoopCount * 1);

			PrimeNumberSolver::SolverJob			solverJob0(PrimeNumberSolver::s_kPrimeStart);
			PrimeNumberSolver::SolverJob2			solverJob1(PrimeNumberSolver::s_kPrimeStart + PrimeNumberSolver::s_kLoopCount * 1);


			handle0 = solverJob_ParFor0.delayDispatch(PrimeNumberSolver::s_kLoopCount, PrimeNumberSolver::s_kBatchSize);
			handle1 = solverJob_ParFor1.delayDispatch(PrimeNumberSolver::s_kLoopCount, PrimeNumberSolver::s_kBatchSize, handle0, handle0, handle0);
			jsys->submit(handle0);
			jsys->waitForComplete(handle1);
			solverJob_ParFor0.print();
			solverJob_ParFor1.print();

			handle0 = solverJob_For0.delayDispatch(PrimeNumberSolver::s_kLoopCount);
			handle1 = solverJob_For1.delayDispatch(PrimeNumberSolver::s_kLoopCount, handle0, handle0, handle0);
			jsys->submit(handle0);
			jsys->waitForComplete(handle1);
			solverJob_For0.print();
			solverJob_For1.print();

			handle0 = solverJob0.delayDispatch();
			handle1 = solverJob1.delayDispatch(handle0, handle0, handle0);
			jsys->submit(handle0);
			jsys->waitForComplete(handle1);
			solverJob0.print();
			solverJob1.print();
		}
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
	bool _isQuit = false;
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



