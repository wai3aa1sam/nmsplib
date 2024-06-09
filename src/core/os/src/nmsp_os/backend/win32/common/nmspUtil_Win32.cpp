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

u64 
Util_Win32::toU64(const LARGE_INTEGER& v) 
{
	return sCast<u64>(v.HighPart) << 32 | v.LowPart;
}

void 
Util_Win32::closeHandleAndSetNull(Handle& hnd)
{
	if (hnd)
	{
		CloseHandle(hnd);
		hnd = NULL;
	}
}

DWORD		
Util_Win32::getLastErrorCode()
{
	DWORD err = ::GetLastError();
	return err;
}

StringT Util_Win32::getLastErrorMsg()
{
	StringT o;

	DWORD err = getLastErrorCode();
	/*switch( err ) 
	{
		case ERROR_FILE_NOT_FOUND:		{ NMSP_THROW("file not found");			} break;
		case ERROR_PATH_NOT_FOUND:		{ NMSP_THROW("path not found");			} break;
		case ERROR_FILE_EXISTS:			{ NMSP_THROW("file doesn't exists");	} break;
		case ERROR_ALREADY_EXISTS:		{ NMSP_THROW("file already exists");	} break;
		case ERROR_ACCESS_DENIED:		{ NMSP_THROW("access denied");			} break;
		case ERROR_SHARING_VIOLATION:	{ NMSP_THROW("sharing violation");		} break;

		case ERROR_LOCK_VIOLATION:		{ NMSP_THROW("file lock violation");	} break;

		default:						{ NMSP_THROW("GetLastError(): Code: {}", err); }
	}*/

	StringW_T<512> bufW;
	bufW.resize(512);
	DWORD   dwChars;  // Number of chars returned.
	// Try to get the message from the system errors.
	dwChars = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err,
		0,
		bufW.data(),
		sCast<DWORD>(bufW.size()),
		NULL);
	o.reserve(bufW.size());
	UtfUtil::convert(o, bufW);
	return o;
}


#endif


}