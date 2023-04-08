#pragma once

#include "nmsp_core_base-config.h"

#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "nmsp_core_base/detect_platform/nmsp_detect_platform.h"
#include "nmsp_core_base/marco/nmsp_core_base_marco.h"

#if 0
#pragma mark --- XXXX-Decl/Impl ---
#endif // 0
#if 1



#endif

#if 0
#pragma mark --- nmspCommon-Incl ---
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

#if NMSP_IS_ASAN_ENABLE
	#define _DISABLE_VECTOR_ANNOTATION
#endif // NMSP_IS_ASAN_ENABLE

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
#pragma mark --- nmsp_core_base-common-Incl ---
#endif // 0
#if 1

#include "nmspDataType_Common.h"
#include "nmspFunction_Common.h"
#include "nmspTypeTrait_Common.h"
#include "nmspClass_Common.h"
#include "nmspEnum_Common.h"

#include "nmspError_Common.h"

#include "../fmt/nmspFmt.h"

#endif

#define _NMSP_LOG(...) do{ ::nmsp::_log(__VA_ARGS__); } while(false)

#if 0
#pragma mark --- nmspInternalLog-Impl ---
#endif // 0
#if 1
namespace nmsp {

#if NMSP_OS_WINDOWS
	using OSRet = HRESULT;
#else

#endif

inline void _log()
{
}

template<class... ARGS> inline
void _log(const char* format, ARGS&&... args)
{
	std::cout << fmtAs_T<std::string>(format, nmsp::forward<ARGS>(args)...) << "\n";
}

}
#endif


#if 0
#pragma mark --- nmspStaticVariables-Impl ---
#endif // 0
#if 1
namespace nmsp {

static constexpr size_t s_kCahchLineSize = std::hardware_destructive_interference_size;

}
#endif

