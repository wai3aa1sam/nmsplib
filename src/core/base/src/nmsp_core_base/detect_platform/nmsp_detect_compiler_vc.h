#pragma once

/*
reference:
https://github.com/SimpleTalkCpp/SimpleGameEngine
*/


#pragma warning(disable: 4668) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'

#if !NMSP_COMPILER_VC	
	#error
#endif

#if _MSVC_LANG >= 199711L
	#define NMSP_CPLUSPLUS_03	1
#endif

#if _MSVC_LANG >= 201103L
	#define NMSP_CPLUSPLUS_11	1
#endif

#if _MSVC_LANG >= 201402L
	#define NMSP_CPLUSPLUS_14	1
#endif

#if _MSVC_LANG >= 201703L
	#define NMSP_CPLUSPLUS_17	1
#endif

#if _MSVC_LANG >= 202002L
	#define NMSP_CPLUSPLUS_20	1
#endif

#define NMSP_TYPE_HAS_SIZE_T	0
#define NMSP_TYPE_HAS_SSIZE_T	0
#define NMSP_TYPE_HAS_LONGLONG	0

#define NMSP_DLL_EXPORT			_declspec(dllexport)
#define NMSP_DLL_IMPORT			_declspec(dllimport)

#define	NMSP_FUNC_NAME_SZ			__FUNCTION__
#define NMSP_FUNC_FULLNAME_SZ		__FUNCSIG__

#define NMSP_DEPRECATED			__declspec(deprecated)

#define NMSP_COMPILER_VER _MSVC_LANG

#if NMSP_CPLUSPLUS_17
	#define NMSP_FALLTHROUGH	//	[[fallthrough]]
	#define NMSP_NODISCARD		[[nodiscard]]
#else
	#define NMSP_FALLTHROUGH
	#define NMSP_NODISCARD
#endif

//#define NMSP_ALIGN(N)				__declspec(align(N)) 
//#define NMSP_ALIGN(N)				alignas(N) //c++11

#define NMSP_OPTIMIZE_OFF			__pragma(optimize("", off))

#if 0 // NMSP_GEN_CONFIG_Debug
	#define	NMSP_INLINE		inline
#else
	#define	NMSP_INLINE		__forceinline
#endif

#define NMSP_THREAD_LOCAL			__declspec( thread )
//#define NMSP_THREAD_LOCAL thread_local //C++11

#if _MSC_VER < 1600
	#define	nullptr	NULL
#endif

//cpu
#if _M_X64
	#define NMSP_CPU_X86_64	1
	#define NMSP_CPU_FEATURE_SSE1		1
	#define NMSP_CPU_FEATURE_SSE2		1
	#define NMSP_CPU_FEATURE_SSE3		1

#elif _M_PPC
	#define NMSP_CPU_PowerPC     1
#else
	#define NMSP_CPU_x86         1
#endif

//os

#if _WIN64
	#define NMSP_OS_WIN64     1
	#define NMSP_OS_WINDOWS	1
#elif _WIN32
	#define NMSP_OS_WIN32     1
	#define NMSP_OS_WINDOWS	1
#elif _WINCE
	#define NMSP_OS_WinCE     1
	#define NMSP_OS_WINDOWS	1
#endif
