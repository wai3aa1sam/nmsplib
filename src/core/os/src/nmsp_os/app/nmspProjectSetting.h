#pragma once

#include "nmsp_os/common/nmsp_os_common.h"
#include "nmspAppBase.h"

#include <nmsp_stl/extra/nmspSingleton.h>

/*
references:
- src/core/app/ConsoleApp.h in https://github.com/SimpleTalkCpp/SimpleGameEngine
*/

namespace nmsp {

#if 0
#pragma mark --- ProjectSetting-Decl ---
#endif // 0
#if 1

class ProjectSetting_T : public NonCopyable
{
public:
	ProjectSetting_T();
	~ProjectSetting_T();
	
	void setProjectRoot(StrViewA_T path);

public:
	const StringT& projectRoot() const;

private:
	StringT _projectRoot;
};

#endif

#if 0
#pragma mark --- ProjectSetting-Impl ---
#endif // 0
#if 1

inline const StringT& ProjectSetting_T::projectRoot()	const { return _projectRoot; }

#endif

}