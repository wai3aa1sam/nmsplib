#include "nmsp_os-pch.h"

#include "nmspProjectSetting.h"

#include "nmsp_os/file/nmspPath.h"

namespace nmsp {

#if 0
#pragma mark --- ProjectSetting-Impl ---
#endif // 0
#if 1

//ProjectSetting_T* ProjectSetting_T::s_instance = nullptr;

//ProjectSetting_T* ProjectSetting_T::s_instance = nullptr;

ProjectSetting_T::ProjectSetting_T()
{
	
}

ProjectSetting_T::~ProjectSetting_T()
{
	
}

void ProjectSetting_T::setProjectRoot(StrViewA_T path)
{
	if (path.is_empty())
		return;

	_projectRoot = Path::realpath(path);
	Path::setCurrentDir(path);
}

#endif

}