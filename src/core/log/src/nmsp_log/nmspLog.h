#pragma once

#include "common/nmsp_log_common.h"

namespace nmsp {

inline void log(const char* msg)
{
	std::cout << msg << "\n";
}

}