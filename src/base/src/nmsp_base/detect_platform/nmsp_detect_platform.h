#pragma once

/*
reference:
https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

/*
NMSP_DetectPlatform:
	- headers only
	- detect compiler / OS / CPU
	- may be used by external lib, so please keep it simple
*/

#ifdef __OBJC__ // Objective C
	#define NMSP_OBJC		1
#else
	#define NMSP_OBJC		0
#endif

//=========== Detect COMPILER ===============
#if defined(__clang__) 
	#define NMSP_COMPILER_CLANG	1
	#include "nmsp_detect_compiler_gcc.h"

#elif defined(__GNUC__)
	#define NMSP_COMPILER_GCC		1
	#include "nmsp_detect_compiler_gcc.h"

#elif defined(_MSC_VER)
	#define NMSP_COMPILER_VC		1
	#include "nmsp_detect_compiler_vc.h"

#endif

#if NMSP_COMPILER_VC + NMSP_COMPILER_GCC + NMSP_COMPILER_CLANG != 1
    #error "Compiler should be specified"
#endif

//======== Detect CPU =============

// check CPU define
#if NMSP_CPU_X86_64 + NMSP_CPU_X86 + NMSP_CPU_POWERPC + NMSP_CPU_ARM + NMSP_CPU_ARM64 != 1
	#error "CPU should be specified"
#endif

#if NMSP_CPU_X86_64
	#define NMSP_CPU_LP64				1
	#define NMSP_CPU_ENDIAN_LITTLE	1
	#define NMSP_CPU_MISALIGNED_MEMORY_ACCESSES	8
#endif

#if NMSP_CPU_X86
	#define NMSP_CPU_LP32				1
	#define NMSP_CPU_ENDIAN_LITTLE	1
	#define NMSP_CPU_MISALIGNED_MEMORY_ACCESSES	8
#endif

#if NMSP_CPU_POWERPC
	#define NMSP_CPU_LP32				1
	#define NMSP_CPU_ENDIAN_BIG		1
	#define NMSP_CPU_MISALIGNED_MEMORY_ACCESSES	8
#endif

#if NMSP_CPU_ARM64
	#define NMSP_CPU_LP64				1
	#define NMSP_CPU_MISALIGNED_MEMORY_ACCESSES	8
#endif

#if NMSP_CPU_ARM
	#define NMSP_CPU_LP32				1
	#define NMSP_CPU_MISALIGNED_MEMORY_ACCESSES	1
#endif

#if NMSP_CPU_LP32 + NMSP_CPU_LP64 != 1
	#error "CPU bits should be specified"
#endif

#if NMSP_CPU_LP32
	#define NMSP_SIZEOF_POINTER		4
#endif

#if NMSP_CPU_LP64
	#define NMSP_SIZEOF_POINTER		8
#endif

#ifndef NMSP_SIZEOF_POINTER
	#error "Unknown NMSP_SIZEOF_POINTER"
#endif

#if NMSP_CPU_ENDIAN_BIG + NMSP_CPU_ENDIAN_LITTLE != 1
	#error "CPU endian should be specified"
#endif

//======== Detect OS ===============

#if NMSP_OS_WIN32 + NMSP_OS_WIN64 + NMSP_OS_WINCE \
	+ NMSP_OS_FREEBSD + NMSP_OS_LINUX \
	+ NMSP_OS_ANDROID \
	+ NMSP_OS_MACOSX  + NMSP_OS_IOS \
	+ NMSP_OS_CYGWIN  + NMSP_OS_MINGW != 1
	#error "OS should be specified"
#endif



//====================================

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef _UNICODE
	#define _UNICODE
#endif
