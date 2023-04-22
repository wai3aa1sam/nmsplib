#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_module_template-config.h"

namespace nmsp {

#if 0
#pragma mark --- ModuleTemplateTraits-Impl ---
#endif // 0
#if 1
struct ModuleTemplateDefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_MODULE_TEMPLATE_CUSTOM_TRAITS

using ModuleTemplateTraits = ModuleTemplateDefaultTraits_T;

#else

#endif // 

#endif

}
