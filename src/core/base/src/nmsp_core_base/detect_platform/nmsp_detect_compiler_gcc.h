#pragma once

/*
references:
- sge_detect_compiler_gcc.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

#if ! (NMSP_COMPILER_CLANG | NMSP_COMPILER_GCC)
	#error
#endif

#if __cplusplus >= 199711L
	#define NMSP_CPLUSPLUS_03	1
#endif

#if __cplusplus >= 201103L 
	#define NMSP_CPLUSPLUS_11	1
#endif

#if __cplusplus >= 201402L
	#define NMSP_CPLUSPLUS_14	1
#endif

#if __cplusplus >= 201703L
	#define NMSP_CPLUSPLUS_17	1
#endif

#if __cplusplus >= 202002L
	#define NMSP_CPLUSPLUS_20	1
#endif



#if NMSP_COMPILER_CLANG
	#define NMSP_TYPE_HAS_SIZE_T		0  //linux 
	#define NMSP_TYPE_HAS_SSIZE_T		0  //linux 

	#define NMSP_OPTIMIZE_OFF			_Pragma("clang optimize off")
#else
	#define NMSP_TYPE_HAS_SIZE_T		0  //linux 
	#define NMSP_TYPE_HAS_SSIZE_T		0  //linux 

	#define NMSP_OPTIMIZE_OFF			_Pragma("GCC optimize(\"O0\")")
#endif

#if __GNUC__ >= 4
	#define	NMSP_DLL_EXPORT			__attribute__ ((visibility ("default")))
	#define NMSP_DLL_IMPORT			// __attribute__ ((visibility ("hidden")))
#else
	#define	NMSP_DLL_EXPORT
	#define NMSP_DLL_IMPORT
#endif


// #define nullptr	NULL

#define	NMSP_FUNC_NAME_SZ				__FUNCTION__
#define NMSP_FUNC_FULLNAME_SZ			__PRETTY_FUNCTION__

#define NMSP_DEPRECATED( f )		f __attribute__( (deprecated) )

#define NMSP_COMPILER_VER __cplusplus

#if NMSP_CPLUSPLUS_17
	#define NMSP_FALLTHROUGH		// [[fallthrough]]
	#define NMSP_NODISCARD		[[nodiscard]]
#else
	#define NMSP_FALLTHROUGH
	#define NMSP_NODISCARD
#endif

//#define NMSP_ALIGN(N)				__attribute__((aligned(N)))
//#define NMSP_ALIGN(N)				alignas(N) //c++11

#if NMSP_GEN_CONFIG_Debug
	#define	NMSP_INLINE      inline
#else
	#define	NMSP_INLINE		inline //__attribute__( (always_inline) )
#endif

//#define NMSP_THREAD_LOCAL	__thread
#define NMSP_THREAD_LOCAL thread_local //C++11

// sanitizer support
#if defined(__has_feature)
	#if __has_feature(address_sanitizer)
		#define NMSP_IS_ASAN_ENABLE 1
	#else
		#define NMSP_IS_ASAN_ENABLE 0
	#endif
#else
	#define NMSP_IS_ASAN_ENABLE 0
#endif

#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64) || defined(__amd64__)
	#define NMSP_CPU_X86_64      1

#elif defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
	#define NMSP_CPU_X86         1

#elif defined(__POWERPC__)
	#define NMSP_CPU_POWERPC     1

#elif defined(__aarch64__)
	#define NMSP_CPU_ARM64 1

	#if defined(__ARMEL__) || defined(__AARCH64EL__)
		#define NMSP_CPU_ENDIAN_LITTLE	1
	#elif defined(__ARMEB__) || defined(__AARCH64EB__)
		#define NMSP_CPU_ENDIAN_BIG		1
	#else
		#error unknown ARM CPU endian
	#endif

#elif defined(__arm__)
	#define NMSP_CPU_ARM 1

	#if defined(__ARMEL__) || defined(__AARCH64EL__)
		#define NMSP_CPU_ENDIAN_LITTLE	1
	#elif defined(__ARMEB__) || defined(__AARCH64EB__)
		#define NMSP_CPU_ENDIAN_BIG		1
	#else
		#error unknown ARM CPU endian
	#endif
#endif

#if	defined(__ARM_NEON__) || defined(__ARM_NEON)
	#define NMSP_CPU_FEATURE_ARM_NEON
#endif

#if __SSE__
	#define NMSP_CPU_FEATURE_SSE1			1
#endif

#if __SSE2__
	#define NMSP_CPU_FEATURE_SSE2			1
	#include <xmmintrin.h>
#endif

#if __SSE3__
	#define NMSP_CPU_FEATURE_SSE3			1
#endif

#if __SSSE3__
	#define NMSP_CPU_FEATURE_SSSE3		1
#endif

#if __SSE4_1__
	#define NMSP_CPU_FEATURE_SSE4_1		1
#endif

#if __SSE4_2__
	#define NMSP_CPU_FEATURE_SSE4_2		1
#endif

//os

#if _WIN64
	#define NMSP_OS_WIN64     1
	#define NMSP_OS_WINDOWS	1

#elif _WIN32
	#define NMSP_OS_WIN32     1
	#define NMSP_OS_WINDOWS	1

#elif __ANDROID__
	#define NMSP_OS_ANDROID	1

#elif __linux
	#define NMSP_OS_LINUX        1

#elif __FreeBSD__
	#define NMSP_OS_FREEBSD		1

#elif __APPLE__ && __MACH__
	#include <TargetConditionals.h>
	#if (TARGET_OF_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE)
		#define NMSP_OS_IOS		1
	#else
		#define NMSP_OS_MACOSX	1
	#endif

#elif __sun
	#define NMSP_OS_SOLARIS		1

#elif __CYGWIN__
    #define NMSP_OS_CYGWIN        1

#elif __MINGW32__
	#define NMSP_OS_MINGW			1
#endif

