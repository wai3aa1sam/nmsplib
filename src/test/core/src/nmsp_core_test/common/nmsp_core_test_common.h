#pragma once

#include <nmsp_test_base.h>

#if NMSP_TEST_ALL_MODULE
	#include <nmsp_core.h>
#endif

#if NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE
	#include <nmsp_stl.h>
#endif // NMSP_TEST_MODULE_STL || NMSP_TEST_ALL_MODULE

#if NMSP_TEST_MODULE_LOG || NMSP_TEST_ALL_MODULE
	#include <nmsp_log.h>
#endif // NMSP_TEST_MODULE_LOG || NMSP_TEST_ALL_MODULE

#if NMSP_TEST_MODULE_PROFILER || NMSP_TEST_ALL_MODULE
	#include <nmsp_profiler.h>
#endif // NMSP_TEST_MODULE_PROFILER || NMSP_TEST_ALL_MODULE

#include "nmsp_core_test-config.h"

#define NMSP_RUN_TEST(fn) \
	std::cout << "\n======" #fn "==================\n" ;\
	void fn(); \
	fn(); \
//-----------
