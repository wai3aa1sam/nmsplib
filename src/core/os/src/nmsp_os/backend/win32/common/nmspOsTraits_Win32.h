#pragma once

#include "nmsp_os/common/base/nmspOsTraits_Base.h"

#if NMSP_OS_WINDOWS
namespace nmsp {

#if 0
#pragma mark --- OsTraits-Impl ---
#endif // 0
#if 1

struct OsUtil_Win32;
struct Util_Win32;

struct OsDefaultTraits_Win32 : public OsDefaultTraits_Base
{
	static constexpr const char* s_cmdExePathEnvVar = "CompSpec";

	static constexpr OsPlatform				platform();
	static constexpr EnumInt<OsPlatform>	platformInt();

	using OsUtil = OsUtil_Win32;
	using Util	 = Util_Win32;

	using Msg		= MSG;
	using WndHnd	= HWND;
	using NativeFd	= ::HANDLE;
};


inline constexpr OsPlatform				OsDefaultTraits_Win32::platform()		{ return OsPlatform::Windows; }
inline constexpr EnumInt<OsPlatform>	OsDefaultTraits_Win32::platformInt()	{ return enumInt(platform()); }


#endif



}
#endif
