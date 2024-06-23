#pragma once

#include "nmsp_core_base_build_marco.h"

#include "nmsp_core_base_util_marco.h"

#include "nmsp_core_base_internal_marco.h"

#define NMSP_NAMED_FIXED_IO(SE, MEMBER) SE.named_fixed_io(this->MEMBER, #MEMBER)