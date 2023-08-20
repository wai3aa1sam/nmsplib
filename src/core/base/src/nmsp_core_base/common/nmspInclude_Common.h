#pragma once

#include "nmsp_core_base-config.h"
#include "nmsp_core_base_traits.h"

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
#include <stdlib.h>

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
#include <random>

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

NMSP_DISABLE_ALL_WARNINGS()
#include <fmt/format.h>
NMSP_RESTORE_ALL_WARNINGS()