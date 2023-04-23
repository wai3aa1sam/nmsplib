#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_os-config.h"

namespace nmsp {

template<class T> struct WindowRect2_T;;

enum class OsPlatform
{
	Windows = 0,
	Linux,
	_kCount,
};

#if 0
#pragma mark --- OsTraits-Impl ---
#endif // 0
#if 1

struct OsDefaultTraits_Base : public CoreBaseTraits
{
	static constexpr OsPlatform				platform();
	static constexpr EnumInt<OsPlatform>	platformInt();

	template<class T>	using Rect2  = WindowRect2_T<T>;
						using Rect2f = Rect2<f32>;
						using Rect2d = Rect2<f64>;
						using Rect2i = Rect2<i32>;

	using SizeType	= size_t;
	using IndexType	= i32;
	using FileSize  = size_t;
};

#endif

}
