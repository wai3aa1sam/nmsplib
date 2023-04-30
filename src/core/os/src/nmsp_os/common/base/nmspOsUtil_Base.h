#pragma once

//#include "nmsp_os/common/base/nmspOsTraits_Base.h"
#include "nmsp_os/common/nmsp_os_traits.h"


namespace nmsp {
#if 0
#pragma mark --- OsUtil_Base-Decl ---
#endif // 0
#if 1

struct OsUtil_Base
{
public:
	template<class T> using Vec2_T	= OsTraits::Vec2<T>;
	template<class T> using Rect2_T	= OsTraits::Rect2<T>;

	using Vec2f		= OsTraits::Vec2f;
	using Rect2f	= OsTraits::Rect2f;

public:
	OsUtil_Base() = delete;

public:


};


#endif

}
