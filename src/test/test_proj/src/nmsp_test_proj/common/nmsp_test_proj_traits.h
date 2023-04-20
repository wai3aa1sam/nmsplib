#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>

namespace nmsp {

struct ModuleTemplateDefaultTraits_T : public NmspTraits
{
	
};


#if !NMSP_MODULE_TEMPLATE_CUSTOM_TRAITS

using ModuleTemplateTraits = ModuleTemplateDefaultTraits_T;

#else

#endif // 

}
