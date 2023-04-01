#pragma once

#include <nmsp_core_base.h>

#include "nmsp_stl-config.h"

#if 0

	#if !EASTL_DLL // If building a regular library and not building EASTL as a DLL...
	// It is expected that the application define the following
	// versions of operator new for the application. Either that or the
	// user needs to override the implementation of the allocator class.
	inline void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) { return malloc(size); }
	inline void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) 
	{
		#if NMSP_OS_WINDOWS
		return _aligned_malloc(size, alignment);
		#else
		return std::aligned_alloc(alignment, size);
		#endif
	}
	#endif

#endif // 0
