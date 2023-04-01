#pragma once

#include "nmspAllocator_Common.h"

#include "nmspMallocAllocator.h"

#include "nmspAlloctorType.h"

#if !NMSP_ENABLE_CUSTOM_ALLOC

	#if	!NMSP_BUILD_STL_EASTL_CONTAINER
		namespace nmsp {
		using DefaultAllocator = MallocAllocator;
		}
	#else
		#include "eastl/nmspAllocator_Eastl.h"
		namespace nmsp {
		using DefaultAllocator = Allocator_Eastl<MallocAllocator>;
		}
	#endif
#endif // NMSP_ENABLE_CUSTOM_ALLOC

