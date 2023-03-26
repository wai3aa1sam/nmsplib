#pragma once


#if 0
#pragma mark --- stl_cnofig-Impl ---
#endif // 0
#if 1

#ifdef NMSP_BUILD_STL_NMSP
	#define NMSP_BUILD_STL_NMSP 1
#endif // NMSP_BUILD_STL_NMSP

#ifdef NMSP_BUILD_STL_STD
	#define NMSP_BUILD_STL_STD 1
#endif // NMSP_BUILD_STL_STD

#define NMSP_BUILD_STL_NMSP 1
#define NMSP_BUILD_STL_STD	0

#if NMSP_BUILD_STL_NMSP + NMSP_BUILD_STL_STD != 1
	#error "build stl should be specified"
#endif

#define NMSP_ENABLE_IVECTOR 0
#define NMSP_ENABLE_ISTRING 1

#endif