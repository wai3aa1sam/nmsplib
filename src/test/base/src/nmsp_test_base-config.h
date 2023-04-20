#pragma once

#ifndef NMSP_TEST_BASE_CUSTOM_TRAITS
	#define NMSP_TEST_BASE_CUSTOM_TRAITS 0
#endif // 0

#define NMSP_ENABLE_FUZZ_TESTING 0

#if NMSP_ENABLE_FUZZ_TESTING && !NMSP_IS_ASAN_ENABLE
	#error "should enable asan with enable fuzz testing"
#endif //  NMSP_IS_FUZZ_TESTING && !NMSP_IS_ASAN_ENABLE


#define NMSP_ENABLE_BENCHMARK 1