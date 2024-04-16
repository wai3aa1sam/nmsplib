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
	void run() { onRun(); }

protected:
	virtual void onRun() = 0;
};

}