#pragma once

#if NMSP_ENABLE_INTERNAL_PROFILER
	#define TRACY_ENABLE 1

	#include <tracy/Tracy.hpp>
	#include <tracy/TracyC.h>
	#include <common/TracySystem.hpp>

	#define _NMSP_PROFILE_SCOPED()				ZoneScoped							
	#define _NMSP_PROFILE_FRAME()				FrameMark							
	#define _NMSP_PROFILE_SECTION(name)			ZoneScopedN(name)					
	#define _NMSP_PROFILE_TAG(str)				ZoneText(str, ::strlen(str))		
	#define _NMSP_PROFILE_LOG(text)				TracyMessage(text, ::strlen(text)	
	#define _NMSP_PROFILE_VALUE(text, value)	TracyPlot(text, value)				

	#define _NMSP_PROFILE_ALLOC(p, size)		TracyCAllocS(p, size, 12)		    
	#define _NMSP_PROFILE_FREE(p, size)			TracyCFreeS(p, 12)				    

	#define _NMSP_PROFILE_SET_THREAD_NAME(name)	::tracy::SetThreadName(name)

#else

	#define _NMSP_PROFILE_SCOPED()						
	#define _NMSP_PROFILE_FRAME()					
	#define _NMSP_PROFILE_SECTION(name)			
	#define _NMSP_PROFILE_TAG(str)				
	#define _NMSP_PROFILE_LOG(text)				
	#define _NMSP_PROFILE_VALUE(text, value)		

	#define _NMSP_PROFILE_ALLOC(p, size)			
	#define _NMSP_PROFILE_FREE(p, size)			

	#define _NMSP_PROFILE_SET_THREAD_NAME(name)

#endif // NMSP_ENABLE_INTERNAL_PROFILER

#if 0
#pragma mark --- memory_marco-Impl ---
#endif // 0
#if 1

#if !NMSP_CUSTOM_ALLOC
	//#define NMSP_ALLOC(ptr, size, ...)	::new char[](size)
	//#define NMSP_FREE(ptr, size)		::delete[] ptr

	//inline void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
	//{ 
	//	return malloc(size);
	//}
	//
	//inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
	//{
	//	#if NMSP_OS_WINDOWS
	//	return _aligned_malloc(size, alignment);
	//	#else
	//	return std::aligned_alloc(alignment, size);
	//	#endif
	//}

	//void operator delete[](void* ptr) noexcept
	//{
	//	free(ptr);
	//}

#endif // !1

#endif