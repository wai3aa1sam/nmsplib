#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_file_io-config.h"

namespace nmsp {

#if 0
#pragma mark --- FileIOTraits-Impl ---
#endif // 0
#if 1
struct FileIODefaultTraits_T : public CoreBaseTraits
{
	
};


#if !NMSP_FILE_IO_CUSTOM_TRAITS

using FileIOTraits = FileIODefaultTraits_T;

#else

#endif // 

#endif

}
