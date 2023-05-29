#pragma once

#if 0
#pragma mark --- stl_cnofig-Impl ---
#endif // 0
#if 1

#ifndef NMSP_STL_ENABLE_ALLOC_NAME
	#define NMSP_STL_ENABLE_ALLOC_NAME 1
#endif

#ifndef NMSP_STL_CUSTOM_TRAITS
	#define NMSP_STL_CUSTOM_TRAITS				0
#endif // 

#ifndef NMSP_STL_BUILD_STD
	#define NMSP_STL_BUILD_STD 0
#endif // NMSP_STL_BUILD_STD

#ifndef NMSP_STL_BUILD_NMSP
	#define NMSP_STL_BUILD_NMSP 0
#endif // NMSP_STL_BUILD_NMSP

#ifndef NMSP_STL_BUILD_EASTL
	#define NMSP_STL_BUILD_EASTL 0
#endif // NMSP_STL_BUILD_NMSP

#if NMSP_STL_BUILD_STD
	#define NMSP_STL_BUILD_CONTAINER_STD	1
	//#define NMSP_STL_BUILD_SYNC_STD			1
	//#define NMSP_STL_BUILD_STD_THREAD		1

	#error "NMSP_STL_BUILD_STD no yet supported "
#endif // NMSP_STL_BUILD_STD

#if NMSP_STL_BUILD_NMSP
	#define NMSP_STL_BUILD_CONTAINER_NMSP	1
	//#define NMSP_STL_BUILD_SYNC_NMSP		1
	//#define NMSP_STL_BUILD_NMSP_THREAD		1

	#define NMSP_STL_ENABLE_IVECTOR 1
	#define NMSP_STL_ENABLE_ISTRING 1
#endif // 0

#if NMSP_STL_BUILD_EASTL
	#define NMSP_STL_BUILD_CONTAINER_EASTL	1
	//#define NMSP_STL_BUILD_SYNC_EASTL		1
	//#define NMSP_STL_BUILD_THREAD_EASTL		1
#endif // NMSP_STL_BUILD_EASTL

#if NMSP_STL_BUILD_STD + NMSP_STL_BUILD_NMSP + NMSP_STL_BUILD_EASTL == 0
	#define NMSP_STL_BUILD_CUSTOM 0
#endif

#if !NMSP_STL_BUILD_CUSTOM
	#define NMSP_STL_BUILD_CONTAINER_EASTL	1
	//#define NMSP_STL_BUILD_SYNC_STD			1
	//#define NMSP_STL_BUILD_NMSP_THREAD		1

#endif // !NMSP_STL_BUILD_CUSTOM

#ifndef NMSP_STL_BUILD_CUSTOM_S_PTR
	#define NMSP_STL_BUILD_CUSTOM_S_PTR 0
#endif // 

#if NMSP_STL_BUILD_CUSTOM_S_PTR
	#define NMSP_STL_INTRUSIVE_S_PTR 0
#else
	#define NMSP_STL_INTRUSIVE_S_PTR 1
#endif // NMSP_STL_BUILD_CUSTOM_S_PTR

#if 0
#pragma mark --- stl_cnofig_checl-Impl ---
#endif // 0
#if 1

#if NMSP_STL_BUILD_CONTAINER_STD + NMSP_STL_BUILD_CONTAINER_NMSP + NMSP_STL_BUILD_CONTAINER_EASTL != 1
	#error "only 1 stl container marco should be defined"
#endif // NMSP_STL_BUILD_CONTAINER_STD + NMSP_STL_BUILD_CONTAINER_STD + NMSP_STL_BUILD_CONTAINER_EASTL

//#if NMSP_STL_BUILD_SYNC_STD + NMSP_STL_BUILD_SYNC_NMSP + NMSP_STL_BUILD_SYNC_EASTL != 1
//	#error "only 1 stl sync marco should be defined"
//#endif // NMSP_STL_BUILD_SYNC_STD + NMSP_STL_BUILD_SYNC_NMSP + NMSP_STL_BUILD_SYNC_EASTL

#if NMSP_STL_BUILD_NMSP + NMSP_STL_BUILD_STD + NMSP_STL_BUILD_EASTL > 1
	#error "nmsp_stl build should be only one"
#endif

#endif // 1



#endif