#include <nmsp_os-pch.h>
#include "nmspOsUtil_Win32.h"

namespace nmsp
{

const char* 
OsUtil_Win32::getEnvironmentVariable(const char* name)
{
	// later should use GetEnvironmentVariable
	// and set env please reference to it https://stackoverflow.com/questions/5246046/how-to-add-environment-variable-in-c

	return ::getenv(name);
}


}