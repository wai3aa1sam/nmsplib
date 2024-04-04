#pragma once

#include "nmsp_os/common/nmsp_os_common.h"


namespace nmsp {

enum class UiEventModifier 
{
	None,
	Shift	= BitUtil::bit(0),
	Ctrl	= BitUtil::bit(1),
	Atl		= BitUtil::bit(2),
	Cmd		= BitUtil::bit(3),
	Fn		= BitUtil::bit(4),
};
NMSP_ENUM_ALL_OPERATOR(UiEventModifier)


}