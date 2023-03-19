#pragma once

#include "nmsp_core_base-config.h"

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "nmsp_core_base/detect_platform/nmsp_detect_platform.h"
#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

#if 0
#pragma mark --- XXXX-Decl
#endif // 0
#if 1

#endif

#if 0
#pragma mark --- XXXX-Impl
#endif // 0
#if 1


#endif

#if 0
#pragma mark --- nmspCommon-Incl
#endif // 0
#if 1

#if NMSP_OS_WINDOWS
	#define NOMINMAX 1
	#include <WinSock2.h> // WinSock2.h must include before windows.h to avoid winsock1 define
	#include <ws2tcpip.h> // struct sockaddr_in6
	#pragma comment(lib, "Ws2_32.lib")
	#include <Windows.h>
	#include <intsafe.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <netinet/in.h> // struct sockaddr_in
#endif

#include <cassert>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <atomic>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <functional>

#include <limits>
#include <stdint.h>
#include <exception>
#include <stdio.h>
#include <signal.h>
#include <codecvt>
#include <limits>

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <fmt/format.h>

#endif

#if 0
#pragma mark --- nmsp_core_base_common-Incl
#endif // 0
#if 1

#include "nmspDataType_Common.h"
#include "nmspFunction_Common.h"
#include "nmspTypeTrait_Common.h"
#include "nmspClass_Common.h"
#include "nmspEnum_Common.h"

#endif

#define _NMSP_LOG(...) do{ ::nmsp::_log(__VA_ARGS__); } while(false)

namespace nmsp {

template<class... ARGS> inline
void _log(const char* format, ARGS&&... args)
{
	std::cout << fmtAs<std::string>(format, forward<ARGS>(args)...) << "\n";
}

}