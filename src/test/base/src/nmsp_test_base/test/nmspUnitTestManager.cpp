#include "nmsp_test_base-pch.h"
#include "nmspUnitTestManager.h"

namespace nmsp {

UnitTestManager*	UnitTestManager::s_instance = nullptr;
UnitTestManager*	UnitTestManager::instance()
{
	return s_instance;
}

UnitTestManager*	UnitTestManager::create()
{
	NMSP_ASSERT(s_instance == nullptr);
	s_instance = new UnitTestManager();
	return s_instance;
}

void UnitTestManager::destroy()
{
	if (!s_instance) 
		return;
	delete s_instance;
	s_instance = nullptr;
}

UnitTestManager::UnitTestManager()
{
}

void UnitTestManager::registerUnitTest(UnitTest* ut)
{
	NMSP_ASSERT(false, "no use now");
}

void UnitTestManager::benchmark(int argc, char* argv[])
{
	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();
}


}