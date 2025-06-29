#pragma once

#include <stdint.h>
#include <cstddef>

#include "nmsp_profiler/common/nmsp_profiler_common.h"

#if NMSP_ENABLE_PROFILER

	#include <tracy/Tracy.hpp>
	#include <tracy/TracyC.h>
	#include <common/TracySystem.hpp>

	#define NMSP_PROFILE_CALLSTACK_DEPTH						32

	#define NMSP_PROFILE_FRAME()								FrameMark			

	#define NMSP_PROFILE_SECTION_IMPL(MSrcLocData, ...)			tracy::ScopedZone NMSP_VAR_NAME(_scoped)((MSrcLocData), NMSP_PROFILE_CALLSTACK_DEPTH, true)

	#define NMSP_PROFILE_SCOPED()								ZoneScopedS(NMSP_PROFILE_CALLSTACK_DEPTH)			
	#define NMSP_PROFILE_SECTION(NAME)							ZoneScopedNS(NAME, NMSP_PROFILE_CALLSTACK_DEPTH)
	#define NMSP_PROFILE_DYNAMIC_SCOPED()						ZoneTransientS( ___tracy_scoped_zone, NMSP_PROFILE_CALLSTACK_DEPTH, true)			
	#define NMSP_PROFILE_DYNAMIC_SECTION(NAME)					ZoneTransientNS(___tracy_scoped_zone, NAME, NMSP_PROFILE_CALLSTACK_DEPTH, true)

	#define NMSP_PROFILE_TAG(STR)								ZoneText(STR, ::strlen(STR))
	#define NMSP_PROFILE_LOG(TEXT)								TracyMessage(TEXT, ::strlen(TEXT))
	#define NMSP_PROFILE_VALUE(TEXT, VALUE)						TracyPlot(TEXT, VALUE)	

	#define NMSP_PROFILE_ALLOC(PTR, SIZE)						TracyCAllocS(PTR, SIZE, NMSP_PROFILE_CALLSTACK_DEPTH)    
	#define NMSP_PROFILE_FREE(PTR, SIZE)						TracyCFreeS(PTR, NMSP_PROFILE_CALLSTACK_DEPTH)		    

	#define NMSP_PROFILE_SET_THREAD_NAME(NAME)					::tracy::SetThreadName(NAME)

#else

	#define NMSP_PROFILE_CALLSTACK_DEPTH						0

	#define NMSP_PROFILE_FRAME()								_NMSP_PROFILE_FRAME()

	#define NMSP_PROFILE_SECTION_IMPL(MSrcLocData, ...)			_NMSP_PROFILE_SECTION_IMPL(MSrcLocData, __VA_ARGS__)

	#define NMSP_PROFILE_SCOPED()								_NMSP_PROFILE_SCOPED()
	#define NMSP_PROFILE_SECTION(NAME)							_NMSP_PROFILE_SECTION(NAME)
	#define NMSP_PROFILE_DYNAMIC_SCOPED()		
	#define NMSP_PROFILE_DYNAMIC_SECTION(NAME)

	#define NMSP_PROFILE_TAG(STR)								_NMSP_PROFILE_TAG(STR)
	#define NMSP_PROFILE_LOG(TEXT)								_NMSP_PROFILE_LOG(TEXT)
	#define NMSP_PROFILE_VALUE(TEXT, VALUE)						_NMSP_PROFILE_VALUE(TEXT, VALUE)

	#define NMSP_PROFILE_ALLOC(PTR, SIZE)						_NMSP_PROFILE_ALLOC(PTR, SIZE)
	#define NMSP_PROFILE_FREE(PTR, SIZE)						_NMSP_PROFILE_FREE(PTR, SIZE)

	#define NMSP_PROFILE_SET_THREAD_NAME(NAME)					_NMSP_PROFILE_SET_THREAD_NAME(NAME)

#endif // NMSP_ENABLE_INTERNAL_PROFILER

namespace nmsp
{

}