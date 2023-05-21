#pragma once

#include <stdint.h>
#include <cstddef>
#include "nmsp_core_base_util_marco.h"

#if NMSP_ENABLE_INTERNAL_PROFILER
	//#define TRACY_ENABLE 1	// set in cmake

	#include <tracy/Tracy.hpp>
	#include <tracy/TracyC.h>
	#include <common/TracySystem.hpp>

	#define _NMSP_PROFILE_SCOPED()				ZoneScoped							
	#define _NMSP_PROFILE_FRAME()				FrameMark							
	#define _NMSP_PROFILE_SECTION(NAME)			ZoneScopedN(NAME)					
	#define _NMSP_PROFILE_TAG(STR)				ZoneText(STR, ::strlen(STR))		
	#define _NMSP_PROFILE_LOG(TEXT)				TracyMessage(TEXT, ::strlen(TEXT))
	#define _NMSP_PROFILE_VALUE(TEXT, VALUE)	TracyPlot(TEXT, VALUE)				

	#define _NMSP_PROFILE_ALLOC(PTR, SIZE)		TracyCAllocS(PTR, SIZE, 20)		    
	#define _NMSP_PROFILE_FREE(PTR, SIZE)		TracyCFreeS(PTR, 20)				    

	#define _NMSP_PROFILE_SET_THREAD_NAME(NAME)	::tracy::SetThreadName(NAME)

#else

	#define _NMSP_PROFILE_SCOPED()					do{ ; } while(false)
	#define _NMSP_PROFILE_FRAME()					do{ ; } while(false)
	#define _NMSP_PROFILE_SECTION(NAME)				do{ ; } while(false)
	#define _NMSP_PROFILE_TAG(STR)					do{ ; } while(false)
	#define _NMSP_PROFILE_LOG(TEXT)					do{ ; } while(false)
	#define _NMSP_PROFILE_VALUE(TEXT, VALUE)		do{ ; } while(false)

	#define _NMSP_PROFILE_ALLOC(PTR, SIZE)			do{ ; } while(false)
	#define _NMSP_PROFILE_FREE(PTR, SIZE)			do{ ; } while(false)

	#define _NMSP_PROFILE_SET_THREAD_NAME(NAME)		do{ ; } while(false)

#endif // NMSP_ENABLE_INTERNAL_PROFILER
