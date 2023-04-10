#pragma once

//#define NMS_CUSTOM_TRAITS 1

#include <nmsp_core_base/common/nmspNmspTraits.h>
namespace nmsp {

struct MyNmspTraits : public NmspDefaultTraits_T
{
	static constexpr size_t s_kDefaultAlign			= 100;
};

using NmspTraits = MyNmspTraits;

}

#include <nmsp_core_base.h>

#include "nmsp_test_proj-config.h"

