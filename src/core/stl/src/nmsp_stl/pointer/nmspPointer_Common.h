#pragma once

#include "nmsp_stl/common/nmsp_stl_common.h"

namespace nmsp
{

template<class T>
struct DefaultDeleter : public NonCopyable
{
	void operator() (T* p)
	{
		if (p)
		{
			NMSP_DELETE(p);
		}
	}
};

}