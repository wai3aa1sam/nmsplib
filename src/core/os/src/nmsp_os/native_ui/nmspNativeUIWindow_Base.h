#pragma once

#include "nmsp_os/common/nmsp_os_common.h"

namespace nmsp {


#if 0
#pragma mark --- NativeUIWindow_Base-Decl ---
#endif // 0
#if 1

struct NativeUIWindow_CreateDesc_Base
{
	
};

// interface only class
class NativeUIWindow_Base : public NonCopyable
{
public:
	using CreateDesc = NativeUIWindow_CreateDesc_Base;

public:
	static CreateDesc	makeCD();

public:
	NativeUIWindow_Base() = default;
	NativeUIWindow_Base(const CreateDesc& cd);

	virtual ~NativeUIWindow_Base();

	void create(const CreateDesc& cd);

protected:
	virtual void onCreate(const CreateDesc& cd);

private:
};

#endif

}