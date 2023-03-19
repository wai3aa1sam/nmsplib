#pragma once

#include "../common/nmsp_core_base_common.h"

#if NMSP_OS_WINDOWS

	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	
	#ifdef _DEBUG
		#define CRT_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
		// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
		// allocations to be of _CLIENT_BLOCK type
	#else
		#define CRT_NEW new
	#endif

	namespace nmsp {

	class MemoryLeakReportScope_Crt
	{
	public:
		MemoryLeakReportScope_Crt()
		{
			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
			_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

			_CrtMemCheckpoint(&begCP);
		}
		~MemoryLeakReportScope_Crt()
		{
			_CrtMemCheckpoint(&endCP);

			_CrtMemState diff; (void)(diff);
			if (_CrtMemDifference(&diff, &begCP, &endCP))
			{
				_CrtMemDumpStatistics(&diff);
			}
		}
	private:
		_CrtMemState begCP{};
		_CrtMemState endCP{};
	};

	using MemoryLeakReportScope_Impl = MemoryLeakReportScope_Crt;
	}

#endif // NMSP_OS_WINDOWS

namespace nmsp {

using MemoryLeakReportScope = MemoryLeakReportScope_Impl;

}
