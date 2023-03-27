#pragma once

#include "../common/nmsp_test_base_common.h"
#include "nmspUnitTest.h"

#include <benchmark/benchmark.h>

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

#define NMSP_REGISTER_UNIT_TEST_CLASS(unitTestClass)				\
	class __ ## unitTestClass										\
	{																\
	public:															\
		static void onBenchmark__(benchmark::State& state)			\
		{															\
			unitTestClass ut;										\
			ut.setup();												\
			for (auto s : state) 									\
			{														\
				/*benchmark::DoNotOptimize(state.iterations());*/	\
				ut.onBenchmark();									\
				/*ut.benchmark();*/									\
			}														\
		}															\
	};																\
	BENCHMARK(__## unitTestClass::onBenchmark__)

#define NMSP_REGISTER_UNIT_TEST(x)								\
	static void __ ## x ## __(benchmark::State& state)			\
	{															\
		for (auto s : state) 									\
		{														\
			/*benchmark::DoNotOptimize(state.iterations());*/	\
			x();												\
		}														\
	}															\
	BENCHMARK(__ ## x ## __)



}