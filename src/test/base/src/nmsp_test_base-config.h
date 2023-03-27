#pragma once

#define NMSP_ENABLE_FUZZ_TESTING 0

#if NMSP_ENABLE_FUZZ_TESTING && !NMSP_IS_ASAN_ENABLE
	#error "should enable asan with enable fuzz testing"
#endif //  NMSP_IS_FUZZ_TESTING && !NMSP_IS_ASAN_ENABLE


#define NMSP_ENABLE_BENCHMARK 1