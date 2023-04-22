#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_os-config.h"

namespace nmsp {

template<class T> struct WindowRect2_T;;

enum class OSPlatform
{
	Windows = 0,
	Linux,
	kCount,
};

#if 0
#pragma mark --- OSTraits-Impl ---
#endif // 0
#if 1
struct OSDefaultTraits_T : public CoreBaseTraits
{
	template<class T>	using Rect2  = WindowRect2_T<T>;
						using Rect2f = Rect2<f32>;
						using Rect2d = Rect2<f64>;
						using Rect2i = Rect2<i32>;

	static constexpr OSPlatform				platform();
	static constexpr EnumInt<OSPlatform>	platformInt();
};


#if !NMSP_OS_CUSTOM_TRAITS

using OSTraits = OSDefaultTraits_T;

#else

#endif // 

#if NMSP_OS_WINDOWS
	inline constexpr OSPlatform OSDefaultTraits_T::platform() { return OSPlatform::Windows; }
#elif NMSP_OS_LINUX
	inline constexpr OSPlatform OSDefaultTraits_T::platform() { return OSPlatform::Linux; }

#else
#error "--- error nmsp_os not supported platform"
#endif // NMSP_OS_WINDOWS

inline constexpr EnumInt<OSPlatform> OSDefaultTraits_T::platformInt() { return enumInt(platform()); }


#endif

}
