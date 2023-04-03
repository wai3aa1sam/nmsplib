#pragma once

#if 0
#pragma mark --- stl_cnofig-Impl ---
#endif // 0
#if 1

#ifdef NMSP_BUILD_STL_STD
	#define NMSP_BUILD_STL_STD 1
#endif // NMSP_BUILD_STL_STD

#ifdef NMSP_BUILD_STL_NMSP
	#define NMSP_BUILD_STL_NMSP 1
#endif // NMSP_BUILD_STL_NMSP

#ifdef NMSP_BUILD_STL_EASTL
	#define NMSP_BUILD_STL_EASTL 1
#endif // NMSP_BUILD_STL_NMSP

#if NMSP_BUILD_STL_STD
	#define NMSP_BUILD_STL_STD_CONTAINER	1

	#error "NMSP_BUILD_STL_STD no yet supported "
#endif // NMSP_BUILD_STL_STD

#if NMSP_BUILD_STL_NMSP
	#define NMSP_BUILD_STL_NMSP_CONTAINER 1

	#define NMSP_ENABLE_IVECTOR 1
	#define NMSP_ENABLE_ISTRING 1
#endif // 0

#if NMSP_BUILD_STL_EASTL
	#define NMSP_BUILD_STL_EASTL_CONTAINER	1
#endif // NMSP_BUILD_STL_EASTL

#if NMSP_BUILD_STL_STD + NMSP_BUILD_STL_NMSP + NMSP_BUILD_STL_EASTL == 0
	#define NMSP_BUILD_STL_DEFAULT 1
#endif

#if NMSP_BUILD_STL_DEFAULT
	#define NMSP_BUILD_STL_EASTL_CONTAINER 1

#endif // NMSP_BUILD_STL_DEFAULT

#if NMSP_BUILD_STL_STD_CONTAINER + NMSP_BUILD_STL_NMSP_CONTAINER + NMSP_BUILD_STL_EASTL_CONTAINER != 1
	#error "only 1 stl container marco should be defined"
#endif // NMSP_BUILD_STL_EASTL_CONTAINER + NMSP_BUILD_STL_STD_CONTAINER + 

#if NMSP_BUILD_STL_NMSP + NMSP_BUILD_STL_STD + NMSP_BUILD_STL_EASTL > 1
	#error "build stl should be specified"
#endif

#ifdef NMSP_BUILD_STL_CUSTOM_S_PTR
	#define NMSP_STL_INTRUSIVE_S_PTR 0
#else
	#define NMSP_STL_INTRUSIVE_S_PTR 1
#endif // NMSP_BUILD_STL_CUSTOM_S_PTR


#endif