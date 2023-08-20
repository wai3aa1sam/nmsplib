#pragma once

#include "nmsp_core_base-config.h"
#include "nmsp_core_base_traits.h"


#include "nmspInclude_Common.h"

#if 0
#pragma mark --- nmsp_core_base-common-Incl ---
#endif // 0
#if 1

#include "nmsp_core_base/alloc/nmspAlloc.h"

#include "nmspDataType_Common.h"

#include "nmspFunction_Common.h"
#include "nmspTypeTraits_Common.h"
#include "nmspClass_Common.h"
#include "nmspEnum_Common.h"

#include "nmspError_Common.h"

#include "../fmt/nmspFmt.h"



#endif

namespace nmsp {

#if NMSP_OS_WINDOWS
	using OSRet = HRESULT;
#else

#endif

}
