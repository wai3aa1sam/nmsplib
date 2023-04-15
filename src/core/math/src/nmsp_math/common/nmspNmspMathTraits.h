#pragma once

#include <nmsp_core_base/common/nmspNmspTraits.h>

namespace nmsp {

struct NmspMathDefaultTraits_T : public NmspTraits
{

};


#if !NMSP_CUSTOM_STL_TRAITS

using NmspMathTraits = NmspMathDefaultTraits_T;

#else

#endif // 

}