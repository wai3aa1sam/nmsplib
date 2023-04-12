#pragma once

#include <nmsp_core_base.h>

#include "nmsp_test_base-config.h"

#if 0
#pragma mark --- nmsp_test_base_common-Incl ---
#endif // 0
#if 1

#include "nmspTestingType.h"

#endif

#define NMSP_RUN_TEST(fn) \
	std::cout << "\n======" #fn "==================\n" ;\
	void fn(); \
	fn(); \
//-----------