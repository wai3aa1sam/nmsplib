#pragma once

#include <nmsp_core_base/test/nmspUnitTest_Base.h>

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

}