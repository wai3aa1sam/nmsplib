#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

namespace nmsp {

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif


#if 0
#pragma mark --- CallOnce-Impl ---
#endif // 0
#if 1

class CallOnce_T
{
public:
	CallOnce_T() = default;

	template<class CALLABLE, class... ARGS>
	CallOnce_T(CALLABLE&& f, ARGS&&... args)
	{
		CallOnce_T(f, std::forward<ARGS>(args)...);
	}

	template<class CALLABLE, class... ARGS>
	void callOnce(CALLABLE&& f, ARGS&&... args)
	{
		std::call_once(_flag, f, std::forward<ARGS>(args)...);
	}

private:
	std::once_flag _flag;
};

#endif

}
