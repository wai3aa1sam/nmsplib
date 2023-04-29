#pragma once

#ifndef NMSP_OS_CUSTOM_TRAITS
	#define NMSP_OS_CUSTOM_TRAITS 0
#endif // NMSP_OS_CUSTOM_TRAITS

#ifndef NMSP_OS_CUSTOM_TRAITS
	#define NMSP_OS_CUSTOM_TRAITS 0
#endif // NMSP_OS_CUSTOM_TRAITS

#if 0

#endif // 0
#if 1


#ifndef NMSP_OS_BUILD_CUSTOM
	#define NMSP_OS_BUILD_CUSTOM			0
#endif // NMSP_OS_BUILD_CUSTOM

#if !NMSP_OS_BUILD_CUSTOM
	#define NMSP_OS_BUILD_ATM_STD		1
	#define NMSP_OS_BUILD_THREAD_NMSP	1
	#define NMSP_OS_BUILD_THREAD_LS_STD	1
	#define NMSP_OS_BUILD_MUTEX_STD		1
	#define NMSP_OS_BUILD_CONDVAR_STD	1
	#define NMSP_OS_BUILD_SYNC_STD		1		// for promise, furture, ...

#endif // NMSP_OS_BUILD_DEFAULT

#if NMSP_OS_BUILD_THREAD_STD + NMSP_OS_BUILD_THREAD_NMSP + NMSP_OS_BUILD_THREAD_EASTL != 1
	#error "only 1 stl container marco should be defined"
#endif // NMSP_OS_BUILD_THREAD_STD + NMSP_OS_BUILD_THREAD_NMSP + NMSP_OS_BUILD_THREAD_EASTL


#endif // 1
