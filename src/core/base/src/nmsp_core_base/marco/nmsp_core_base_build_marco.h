#pragma once

#if 0
#pragma mark --- build_marco-Impl ---
#endif // 0
#if 1

#if _DEBUG
	#define NMSP_DEBUG 1
#else
	#define NMSP_DEBUG 0
#endif // _DEBUG

#define NMSP_DEVELOPMENT 1

#if NMSP_OS_WINDOWS
	#ifdef NMSP_DYNAMIC_LINK
		#ifdef NMSP_BUILD_DLL
			#define NMSP_API NMSP_DLL_EXPORT
		#else
			#define NMSP_API NMSP_DLL_IMPORT
		#endif // NMSP_BUILD_DLL
	#else
		#define NMSP_API
	#endif
#else
	#error nmsp only support Windows!
#endif // NMSP_OS_WINDOWS

#endif // 1

