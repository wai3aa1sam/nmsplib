#include <nmsp_core_base-pch.h>

#include "nmspUnitTest_Common.h"

namespace nmsp {

bool testCheck_Impl(const SrcLoc& loc, bool verbose, bool success, const char* msg)
{
	if (success && !verbose)
		return success;

	auto str = fmt::format("{} {}\n", (success ? "[ OK ]" : "[FAIL]"), msg);
	std::cout << str;
	if (!success)
	{
		assert(false);
	}
	return success;
}

#if 0
#pragma mark --- UnitTestBase-Impl
#endif // 0
#if 1



#endif

}