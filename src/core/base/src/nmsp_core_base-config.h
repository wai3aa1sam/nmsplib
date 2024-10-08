#pragma once

// should set in cmake after development

#ifndef NMSP_CORE_BASE_CUSTOM_TRAITS
	#define NMSP_CORE_BASE_CUSTOM_TRAITS 0
#endif // 0

#ifndef NMSP_ENABLE_EXCEPTION
	#define NMSP_ENABLE_EXCEPTION			1
#endif // 

#ifndef NMSP_ENABLE_ASSERT
	#define NMSP_ENABLE_ASSERT				1
#endif // 

#ifndef NMSP_ENABLE_INTERNAL_PROFILER
	#define NMSP_ENABLE_INTERNAL_PROFILER	0
	#if NMSP_IS_ASAN_ENABLE && NMSP_ENABLE_INTERNAL_PROFILER
		#error "internal should not be on if asan is enabled"
	#endif // 0

#endif // 

#if 0
#ifndef NMSP_OVERRIDE_NEW_OP
	#define NMSP_OVERRIDE_NEW_OP			1
#endif // 

#ifndef NMSP_ENABLE_ALLOC_STATS
	#define NMSP_ENABLE_ALLOC_STATS			1
#endif // 
#endif // 0


