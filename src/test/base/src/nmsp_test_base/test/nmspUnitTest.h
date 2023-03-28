#pragma once

#include <nmsp_core_base/test/nmspUnitTest_Base.h>
#include <benchmark/benchmark.h>

namespace nmsp {

#if 0
#pragma mark --- UnitTest-Decl ---
#endif // 0
#if 1

class UnitTest : public UnitTest_Base
{
public:
	UnitTest() = default;
	virtual ~UnitTest() = default;

	void setup();
	void test();
	//void benchmark();

	virtual void onBenchmark()  = 0;

protected:
	virtual void onSetup()		= 0;
	virtual void onTest()		= 0;

private:
	const char* name;
};

#endif

#if 0
#pragma mark --- benchmark_marco-Impl ---
#endif // 0
#if 1

#define NMSP_BENCHMARK_WRAPPER(x, ...) \
		BENCHMARK_PRIVATE_DECLARE(_benchmark_) =															\
		(::benchmark::internal::RegisterBenchmarkInternal(													\
			new ::benchmark::internal::FunctionBenchmark( NMSP_STRINGIFY(__ ## x ## __VA_ARGS__ ## __),		\
														&__ ## x ## __)))									\
//------

#define NMSP_REGISTER_UNIT_TEST_T_IMPL(x, ...)																\
	static void __ ## x ## __(benchmark::State& state)														\
	{																										\
		for (auto s : state) 																				\
		{																									\
			/*benchmark::DoNotOptimize(state.iterations());*/												\
			NMSP_CONCAT(x, __VA_ARGS__)();																	\
		}																									\
	}																										\
	NMSP_BENCHMARK_WRAPPER(x, __VA_ARGS__)																	\
//------
#define NMSP_REGISTER_UNIT_TEST(x, ...)	NMSP_REGISTER_UNIT_TEST_T_IMPL(x, __VA_ARGS__)

#define NMSP_REGISTER_UNIT_TEST_CLASS(x, ...)																\
	static void __ ## x ## __(benchmark::State& state)														\
	{																										\
		NMSP_CONCAT(x, __VA_ARGS__) __xx;																	\
		__xx.setup();																						\
		for (auto s : state) 																				\
		{																									\
			/*benchmark::DoNotOptimize(state.iterations());*/												\
			__xx.onBenchmark();																				\
			/*__xx.benchmark();*/																			\
		}																									\
	}																										\
	NMSP_BENCHMARK_WRAPPER(x, __VA_ARGS__)																	\
//------

#endif // 0


}