#pragma once

#include <stdint.h>
#include <cstddef>
#include "nmsp_core_base_util_marco.h"

#if NMSP_ENABLE_INTERNAL_PROFILER

	#include <tracy/Tracy.hpp>
	#include <tracy/TracyC.h>
	#include <common/TracySystem.hpp>

	#define _NMSP_PROFILE_CALLSTACK_DEPTH							32

	#define _NMSP_PROFILE_FRAME()									FrameMark			

	#define _NMSP_PROFILE_SECTION_IMPL(MSrcLocData, ...)			tracy::ScopedZone NMSP_VAR_NAME(_scoped)((MSrcLocData), NMSP_PROFILE_CALLSTACK_DEPTH, true)

	#define _NMSP_PROFILE_SCOPED()									ZoneScopedS(NMSP_PROFILE_CALLSTACK_DEPTH)			
	#define _NMSP_PROFILE_SECTION(NAME)								ZoneScopedNS(NAME, NMSP_PROFILE_CALLSTACK_DEPTH)
	#define _NMSP_PROFILE_DYNAMIC_SCOPED()							ZoneTransientS( ___tracy_scoped_zone, NMSP_PROFILE_CALLSTACK_DEPTH, true)			
	#define _NMSP_PROFILE_DYNAMIC_SECTION(NAME)						ZoneTransientNS(___tracy_scoped_zone, NAME, NMSP_PROFILE_CALLSTACK_DEPTH, true)

	#define _NMSP_PROFILE_TAG(STR)									ZoneText(STR, ::strlen(STR))
	#define _NMSP_PROFILE_LOG(TEXT)									TracyMessage(TEXT, ::strlen(TEXT))
	#define _NMSP_PROFILE_VALUE(TEXT, VALUE)						TracyPlot(TEXT, VALUE)	

	#define _NMSP_PROFILE_ALLOC(PTR, SIZE)							TracyCAllocS(PTR, SIZE, NMSP_PROFILE_CALLSTACK_DEPTH)    
	#define _NMSP_PROFILE_FREE(PTR, SIZE)							TracyCFreeS(PTR, NMSP_PROFILE_CALLSTACK_DEPTH)		    

	#define _NMSP_PROFILE_SET_THREAD_NAME(NAME)						::tracy::SetThreadName(NAME)

#else

	#define _NMSP_PROFILE_CALLSTACK_DEPTH			0
	
	#define _NMSP_PROFILE_FRAME()									do{ ; } while(false)	
	
	#define NMSP_PROFILE_SECTION_IMPL(MSrcLocData, ...)				do{ ; } while(false)	

	#define _NMSP_PROFILE_SCOPED()									do{ ; } while(false)
	#define _NMSP_PROFILE_SECTION(NAME)								do{ ; } while(false)
	#define _NMSP_PROFILE_DYNAMIC_SCOPED()							do{ ; } while(false)
	#define _NMSP_PROFILE_DYNAMIC_SECTION(NAME)						do{ ; } while(false)
	
	#define _NMSP_PROFILE_TAG(STR)									do{ ; } while(false)
	#define _NMSP_PROFILE_LOG(TEXT)									do{ ; } while(false)
	#define _NMSP_PROFILE_VALUE(TEXT, VALUE)						do{ ; } while(false)
	
	#define _NMSP_PROFILE_ALLOC(PTR, SIZE)							do{ ; } while(false)
	#define _NMSP_PROFILE_FREE(PTR, SIZE)							do{ ; } while(false)
	
	#define _NMSP_PROFILE_SET_THREAD_NAME(NAME)						do{ ; } while(false)

#endif // NMSP_ENABLE_INTERNAL_PROFILER
