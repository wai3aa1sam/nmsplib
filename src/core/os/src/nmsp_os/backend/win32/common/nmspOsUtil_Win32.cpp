#include "nmsp_os-pch.h"

#include "nmspOsUtil_Win32.h"

namespace nmsp {
#if 0
#pragma mark --- OsUtil_Win32-Impl ---
#endif // 0
#if 1

typename OsUtil_Win32::Rect2f OsUtil_Win32::toRect2f(const ::RECT& rect)
{
	using T = typename Rect2f::ElementType;
	return Rect2f{ sCast<T>(rect.left), sCast<T>(rect.top), sCast<T>(rect.right - rect.left), sCast<T>(rect.top - rect.bottom)};
}


#endif


}