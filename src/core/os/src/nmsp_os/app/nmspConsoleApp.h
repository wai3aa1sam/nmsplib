#pragma once

#include "nmsp_os/common/nmsp_os_common.h"
#include "nmspAppBase.h"

/*
references:
- src/core/app/ConsoleApp.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

class ConsoleApp_T : public AppBase_T
{
public:
	int run() { int exitcode = 0;  exitcode = onRun(); return exitcode; }

protected:
	virtual int onRun() = 0;
};

}