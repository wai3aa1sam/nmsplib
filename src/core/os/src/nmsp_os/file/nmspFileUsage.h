#pragma once

#include "nmsp_os/common/nmsp_os_common.h"


namespace nmsp {

enum class FileMode
{
	CreateNew,
	OpenExists,
	OpenOrCreate,
};

enum class FileAccess
{
	Read,
	ReadWrite,
	WriteOnly,
};

enum class FileShareMode
{
	None,
	Read,
	Write,
	ReadWrite,
};

}