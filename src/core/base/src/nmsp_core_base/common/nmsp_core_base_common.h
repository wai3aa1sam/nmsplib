#pragma once

#include "nmsp_core_base-config.h"
#include "nmsp_core_base_traits.h"

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

#include "nmspAlloc_Common.h"

#include "nmspDataType_Common.h"
#include "nmspBitUtil.h"

#include "nmspFunction_Common.h"
#include "nmspTypeTraits_Common.h"
#include "nmspClass_Common.h"
#include "nmspEnum_Common.h"

#include "nmspError_Common.h"

#include "../fmt/nmspFmt.h"



#endif

namespace nmsp {

#if NMSP_OS_WINDOWS
	using OSRet = HRESULT;
#else

#endif

}
