#pragma once

#if 0
#pragma mark --- stl_cnofig-Impl ---
#endif // 0
#if 1

#ifndef NMSP_STL_CUSTOM_TRAITS
	#define NMSP_STL_CUSTOM_TRAITS				0
#endif // 

#ifndef NMSP_ENABLE_THREAD_LOCAL
	#define NMSP_ENABLE_THREAD_LOCAL 0
#endif // 


#ifndef NMSP_BUILD_STL_STD
	#define NMSP_BUILD_STL_STD 0
#endif // NMSP_BUILD_STL_STD

#ifndef NMSP_BUILD_STL_NMSP
	#define NMSP_BUILD_STL_NMSP 0
#endif // NMSP_BUILD_STL_NMSP

#ifndef NMSP_BUILD_STL_EASTL
	#define NMSP_BUILD_STL_EASTL 0
#endif // NMSP_BUILD_STL_NMSP

#if NMSP_BUILD_STL_STD
	#define NMSP_BUILD_STL_STD_CONTAINER	1
	#define NMSP_BUILD_STL_STD_SYNC			1
	#define NMSP_BUILD_STL_STD_THREAD		1

	#error "NMSP_BUILD_STL_STD no yet supported "
#endif // NMSP_BUILD_STL_STD

#if NMSP_BUILD_STL_NMSP
	#define NMSP_BUILD_STL_NMSP_CONTAINER	1
	#define NMSP_BUILD_STL_NMSP_SYNC		1
	#define NMSP_BUILD_STL_NMSP_THREAD		1

	#define NMSP_ENABLE_IVECTOR 1
	#define NMSP_ENABLE_ISTRING 1
#endif // 0

#if NMSP_BUILD_STL_EASTL
	#define NMSP_BUILD_STL_EASTL_CONTAINER	1
	//#define NMSP_BUILD_STL_EASTL_SYNC		1
	//#define NMSP_BUILD_STL_EASTL_THREAD		1
#endif // NMSP_BUILD_STL_EASTL

#if NMSP_BUILD_STL_STD + NMSP_BUILD_STL_NMSP + NMSP_BUILD_STL_EASTL == 0
	#define NMSP_BUILD_STL_DEFAULT 1
#endif

#if NMSP_BUILD_STL_DEFAULT
	#define NMSP_BUILD_STL_EASTL_CONTAINER	1
	#define NMSP_BUILD_STL_STD_SYNC			1
	#define NMSP_BUILD_STL_NMSP_THREAD		1

#endif // NMSP_BUILD_STL_DEFAULT

#ifndef NMSP_BUILD_STL_CUSTOM_S_PTR
	#define NMSP_BUILD_STL_CUSTOM_S_PTR 0
#endif // 


#if NMSP_BUILD_STL_CUSTOM_S_PTR
	#define NMSP_STL_INTRUSIVE_S_PTR 0
#else
	#define NMSP_STL_INTRUSIVE_S_PTR 1
#endif // NMSP_BUILD_STL_CUSTOM_S_PTR

#if 0
#pragma mark --- stl_cnofig_checl-Impl ---
#endif // 0
#if 1

#if NMSP_BUILD_STL_STD_CONTAINER + NMSP_BUILD_STL_NMSP_CONTAINER + NMSP_BUILD_STL_EASTL_CONTAINER != 1
	#error "only 1 stl container marco should be defined"
#endif // NMSP_BUILD_STL_STD_CONTAINER + NMSP_BUILD_STL_STD_CONTAINER + NMSP_BUILD_STL_EASTL_CONTAINER

#if NMSP_BUILD_STL_STD_SYNC + NMSP_BUILD_STL_NMSP_SYNC + NMSP_BUILD_STL_EASTL_SYNC != 1
	#error "only 1 stl sync marco should be defined"
#endif // NMSP_BUILD_STL_STD_SYNC + NMSP_BUILD_STL_NMSP_SYNC + NMSP_BUILD_STL_EASTL_SYNC

#if NMSP_BUILD_STL_STD_THREAD + NMSP_BUILD_STL_NMSP_THREAD + NMSP_BUILD_STL_EASTL_THREAD != 1
	#error "only 1 stl container marco should be defined"
#endif // NMSP_BUILD_STL_STD_THREAD + NMSP_BUILD_STL_NMSP_THREAD + NMSP_BUILD_STL_EASTL_THREAD

#if NMSP_BUILD_STL_NMSP + NMSP_BUILD_STL_STD + NMSP_BUILD_STL_EASTL > 1
	#error "build stl should be only one"
#endif

#endif // 1



#endif