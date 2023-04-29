#pragma once

#include "nmsp_os/process/nmspProcess.h"

namespace nmsp {

#if 0
#pragma mark --- CommandLine_Base-Decl ---
#endif // 0
#if 1

struct CmdLine_CreateDesc_Base
{
	StrViewA_T	cmd;
	bool		isCloseAfterExecute : 1;
};

class CmdLine_Base : public NonCopyable
{
public:
	using CreateDesc = CmdLine_CreateDesc_Base;

	using Util		= OsTraits::Util;
	using NativeHnd	= OsTraits::NativeFd;
	using FileSize	= OsTraits::FileSize;
	using SizeType	= OsTraits::SizeType;

public:
	CmdLine_Base() = default;
	CmdLine_Base(const CreateDesc& cd);
	CmdLine_Base(StrViewA_T cmd, bool isCloseAfterExecute = true);

	//~CmdLine_Base();

	void execute(const CreateDesc& cd);
	void execute(StrViewA_T cmd, bool isCloseAfterExecute = true);

protected:
	Process_T _proc;
};


#endif

}
