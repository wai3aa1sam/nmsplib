#pragma once

#include <nmsp_core_base/common/nmsp_core_base_traits.h>
#include "nmsp_file_io-config.h"

namespace nmsp {

#if 0
#pragma mark --- FileIoTraits-Impl ---
#endif // 0
#if 1
struct FileIoDefaultTraits_T : public CoreBaseTraits
{
public:
	using Base = CoreBaseTraits;

	using SizeType	= size_t;
	using IndexType = i32;

public:

};


#if !NMSP_FILE_IO_CUSTOM_TRAITS

using FileIoTraits = FileIoDefaultTraits_T;

#else

#endif // 

#endif

}
