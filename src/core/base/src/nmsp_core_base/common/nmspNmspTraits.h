#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "nmsp_core_base/detect_platform/nmsp_detect_platform.h"
#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

#include "nmsp_core_base/marco/nmsp_core_base_internal_marco.h"

#include "nmspDataType_Common.h"
#include "nmspFunction_Common.h"

#include <new>

namespace nmsp {

#if 0
#pragma mark --- nmspNmspTraits-Impl ---
#endif // 0
#if 1


struct NmspDefaultTraits_T
{
	static constexpr size_t s_kCahchLineSize		= std::hardware_destructive_interference_size;
	static constexpr size_t s_kDefaultAlign			= NMSP_ALIGN_OF(std::max_align_t);
	static constexpr size_t s_kThresholdToCallDMA	= 128;
};

#if !NMSP_CUSTOM_TRAITS

using NmspTraits = NmspDefaultTraits_T;

#else


#endif // 


#endif

}

