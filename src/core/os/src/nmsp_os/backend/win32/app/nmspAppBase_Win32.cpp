#include "nmsp_os-pch.h"

#include "nmspAppBase_Win32.h"

namespace nmsp {

StringT	AppBase_Win32::getExecutableFilename()
{
	wchar_t temp[MAX_PATH + 1];
	auto ret = ::GetModuleFileName(nullptr, temp, MAX_PATH);
	Util::throwIf(!ret, "{}", NMSP_SRCLOC);

	StringT o = UtfUtil::toString(temp);
	return o;
}


}