#pragma once

#include "nmsp_core_base-config.h"

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "nmsp_core_base/detect_platform/nmsp_detect_platform.h"
#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

#include "nmspDataType_Common.h"
#include "nmspFunction_Common.h"

#include <new>

namespace nmsp {

#if 0
#pragma mark --- CoreBaseTraits-Impl ---
#endif // 0
#if 1


struct CoreBaseDefaultTraits_T
{
	using SizeType = size_t;
	using IndexType = size_t;

	static constexpr SizeType s_kCacheLineSize		= std::hardware_destructive_interference_size;
	static constexpr SizeType s_kDefaultAlign			= NMSP_ALIGN_OF(std::max_align_t);
	static constexpr SizeType s_kThresholdToCallDMA	= 128;
};

#if !NMSP_CORE_BASE_CUSTOM_TRAITS

using CoreBaseTraits = CoreBaseDefaultTraits_T;

#else


#endif // 


#endif

}

