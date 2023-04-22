#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

#include "nmspFileUsage.h"

namespace nmsp {


#if 0
#pragma mark --- FileStream_Base-Decl ---
#endif // 0
#if 1

struct FileStream_CreateDesc_Base
{
	StrViewA_T		filename;
	FileMode		mode;
	FileAccess		access;
	FileShareMode	shareMode;
};

// interface only class
class FileStream_Base : public NonCopyable
{
public:
	#if NMSP_OS_WINDOWS
	using NativeFd = ::HANDLE;
	#elif NMSP_OS_LINUX
	using NativeFd = int;
	#endif // NMSP_OS_WINDOWS

	using CreateDesc = FileStream_CreateDesc_Base;

public:
	static NativeFd		kInvalid();
	static CreateDesc	makeCD();

public:
	FileStream_Base() = default;
	FileStream_Base(const CreateDesc& cd);

private:
	StringT		_filename;
};

#endif

}