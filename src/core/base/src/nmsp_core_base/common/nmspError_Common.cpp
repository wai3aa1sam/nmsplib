#include "nmsp_core_base-pch.h"

#include "nmspError_Common.h"

namespace nmsp {

#if 0
#pragma mark --- Error_Base-Impl ---
#endif // 0
#if 1

Error_Base::Error_Base(const SrcLoc & srcLoc)
	: _srcLoc(srcLoc)
{
	#if !NMSP_ENABLE_EXCEPTION
	NMSP_ASSERT(false, "Error: Expection is not enable, set NMSP_ENABLE_EXCEPTION to 1 for enable exception!");
	#endif // !NMSP_ENABLE_EXCEPTION
}

#endif

#if 0
#pragma mark --- Error_T-Impl ---
#endif // 0
#if 1

Error_T::Error_T(const SrcLoc& loc, const char* msg)
	: Base(loc)
{
	_NMSP_LOG("Error: {}: {}", loc, msg);
	_flushLog();
}

#endif

}