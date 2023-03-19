#include "nmsp_core_base-pch.h"

#include "nmspError_Common.h"

namespace nmsp {

#if 0
#pragma mark --- ErrorBase-Impl
#endif // 0
#if 1

ErrorBase::ErrorBase(const SrcLoc & srcLoc)
	: _srcLoc(srcLoc)
{
	#if !NMSP_ENABLE_EXCEPTION
	NMSP_ASSERT(false, "Error: Expection is not enable, set NMSP_ENABLE_EXCEPTION to 1 for enable exception!");
	#endif // !NMSP_ENABLE_EXCEPTION
}

#endif

#if 0
#pragma mark --- Error-Impl
#endif // 0
#if 1

Error::Error(const SrcLoc& loc, const char* msg)
	: Base(loc)
{

}

#endif

}