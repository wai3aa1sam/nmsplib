#pragma once

#include "nmsp_os/atomic/nmspAtomic_Common.h"

namespace nmsp {


#if 0
#pragma mark --- CallOnce-Impl ---
#endif // 0
#if 1

class CallOnce
{
public:
	CallOnce() = default;

	template<class CALLABLE, class... ARGS>
	CallOnce(CALLABLE&& f, ARGS&&... args)
	{
		callOnce(f, std::forward<ARGS>(args)...);
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