#pragma once

#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

/*
references:
- UniTest.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#define	NMSP_TEST_CASE(TestClass, TestFunc) \
	do{ \
		::nmsp::_log("\n[--TEST_CASE--] " #TestClass "." #TestFunc "\n"); \
		TestClass testObj; \
		testObj.TestFunc; \
	}while(false)
//----

#define NMSP_TEST_CHECK(a)			nmsp::testCheck_Impl(NMSP_SRCLOC, true,  bool(a), #a)
#define NMSP_TEST_CHECK_SLIENT(a)	nmsp::testCheck_Impl(NMSP_SRCLOC, false, bool(a), #a)

namespace nmsp {

bool testCheck_Impl(const SrcLoc& loc, bool verbose, bool success, const char* msg);

#if 0
#pragma mark --- UnitTest_Base-Impl ---
#endif // 0
#if 1

class UnitTest_Base : public NonCopyable
{
public:


private:

};

#endif

}