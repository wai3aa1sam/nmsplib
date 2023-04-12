#pragma once

#include <stdint.h>
#include <cstddef>

#if NMSP_ENABLE_PROFILER
	//#define TRACY_ENABLE 1	// set in cli

	#include <tracy/Tracy.hpp>
	#include <tracy/TracyC.h>
	#include <common/TracySystem.hpp>

	#define NMSP_PROFILE_SCOPED()				ZoneScoped							
	#define NMSP_PROFILE_FRAME()				FrameMark							
	#define NMSP_PROFILE_SECTION(name)			ZoneScopedN(name)					
	#define NMSP_PROFILE_TAG(str)				ZoneText(str, ::strlen(str))		
	#define NMSP_PROFILE_LOG(text)				TracyMessage(text, ::strlen(text)	
	#define NMSP_PROFILE_VALUE(text, value)		TracyPlot(text, value)				

	#define NMSP_PROFILE_ALLOC(p, size)			TracyCAllocS(p, size, 12)		    
	#define NMSP_PROFILE_FREE(p, size)			TracyCFreeS(p, 12)				    

	#define NMSP_PROFILE_SET_THREAD_NAME(name)	::tracy::SetThreadName(name)

#else

	#define NMSP_PROFILE_SCOPED()					do{ ; } while(false)
	#define NMSP_PROFILE_FRAME()					do{ ; } while(false)
	#define NMSP_PROFILE_SECTION(name)				do{ ; } while(false)
	#define NMSP_PROFILE_TAG(str)					do{ ; } while(false)
	#define NMSP_PROFILE_LOG(text)					do{ ; } while(false)
	#define NMSP_PROFILE_VALUE(text, value)			do{ ; } while(false)

	#define NMSP_PROFILE_ALLOC(p, size)				do{ ; } while(false)
	#define NMSP_PROFILE_FREE(p, size)				do{ ; } while(false)

	#define NMSP_PROFILE_SET_THREAD_NAME(name)		do{ ; } while(false)

#endif // NMSP_ENABLE_INTERNAL_PROFILER
