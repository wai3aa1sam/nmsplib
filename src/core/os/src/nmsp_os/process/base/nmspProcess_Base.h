#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

namespace nmsp {

#if 0
#pragma mark --- Process_Base-Impl ---
#endif // 0
#if 1

struct Process_CreateDesc_Base
{
	bool isCreateStdout = false;
	bool isCreateStdin	= false;
};

class Process_Base : public NonCopyable
{
public:
	using CreateDesc = Process_CreateDesc_Base;

	using Util		= OsTraits::Util;
	using NativeHnd	= OsTraits::NativeFd;
	using FileSize	= OsTraits::FileSize;
	using SizeType	= OsTraits::SizeType;

public:
	Process_Base() = default;
	Process_Base(const CreateDesc& cd);
	Process_Base(StrViewA_T filename);
	Process_Base(StrViewA_T filename, StrViewA_T args);

	//~Process_Base();

	//template<size_t N_CLI_ARGS>
	//Process(StrViewA_T filename, StrViewA_T(&args)[N_CLI_ARGS]);

	void execute(StrViewA_T filename, StrViewA_T args);
	void wait(u64 timeoutMs);
	void kill();

private:
	void _init(StrViewA_T filename, StrViewA_T args);

};

#endif


}