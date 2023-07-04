#include "nmsp_os-pch.h"

#include "nmspUtil_Win32.h"

namespace nmsp {
#if 0
#pragma mark --- Util_Win32-Impl ---
#endif // 0
#if 1

typename Util_Win32::Rect2f Util_Win32::toRect2f(const ::RECT& rect)
{
	using T = typename Rect2f::ElementType;
	return Rect2f{ sCast<T>(rect.left), sCast<T>(rect.top), sCast<T>(rect.right - rect.left), sCast<T>(rect.bottom - rect.top)};
}


StringT Util_Win32::getLastErrorMsg()
{
	DWORD err = ::GetLastError();
	switch( err ) 
	{
		case ERROR_FILE_NOT_FOUND:		{ NMSP_THROW("file not found");			} break;
		case ERROR_PATH_NOT_FOUND:		{ NMSP_THROW("path not found");			} break;
		case ERROR_FILE_EXISTS:			{ NMSP_THROW("file doesn't exists");	} break;
		case ERROR_ALREADY_EXISTS:		{ NMSP_THROW("file already exists");	} break;
		case ERROR_ACCESS_DENIED:		{ NMSP_THROW("access denied");			} break;
		case ERROR_SHARING_VIOLATION:	{ NMSP_THROW("sharing violation");		} break;

		case ERROR_LOCK_VIOLATION:		{ NMSP_THROW("file lock violation");	} break;

		default:						{ NMSP_THROW("GetLastError(): Code: {}", err); }
	}
}


#endif


}