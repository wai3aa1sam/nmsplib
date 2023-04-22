#include "nmsp_log-pch.h"

#include "nmspLogger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/async.h"

#include "nmsp_stl/atomic/nmspThreadStorage.h"

namespace nmsp {

//Logger_T* g_logger = nullptr;
Logger_T* Logger_T::s_instance = nullptr;

#if 0
#pragma mark --- Logger_T-Impl ---
#endif // 0
#if 1

std::atomic_int Logger_T::s_nLoggers = 0;

Logger_T::CreateDesc	Logger_T::makeCDesc()
{
	return Logger_T::CreateDesc{};
}

#if 1

Logger_T* Logger_T::instance()
{
	return s_instance;
}

#else

Logger_T*				Logger_T::instance()
{
	#if NMSP_ENABLE_THREAD_LOCAL
	thread_local static Logger_T* logger = NMSP_ALLOC_T(logger);
	#else
	static CallOnce co {
		[&]()
	{
		Logger_T* p = NMSP_NEW(p);
		NmspStlTraits::_internal_threadStorage()->setLogger(p);
	}
	};
	auto* logger = NmspStlTraits::_internal_threadStorage()->logger();
	#endif // 0

	return logger;
}

#endif // 0

Logger_T::Logger_T()
{
	NMSP_ASSERT(!s_instance, "Logger_T only can be init once");
	s_instance = this;
	s_nLoggers++;
}

Logger_T::~Logger_T()
{
	NMSP_ASSERT(s_instance == this, "Logger_T only can be init once");
	s_instance = nullptr;
	s_nLoggers--;
	destroy();
}

void Logger_T::create(const CreateDesc& cd)
{
	destroy();
	spdlog::init_thread_pool(8192, 1);
	_create(_coreLogger,	cd.coreName,	cd.coreOutputFilepath);
	_create(_clientLogger,	cd.clientName,	cd.clientOutputFilepath);
}

void Logger_T::destroy()
{
	_coreLogger.reset();
	_clientLogger.reset();

	if (s_nLoggers.load() == 0)
	{
		spdlog::shutdown();
	}
}

TempStringA_T<>& toPattern(TempStringA_T<>& o, StrViewA_T name, StrViewA_T pattern)
{
	o.clear();
	o += "[";  o += name; ; o += "]"; o += " ";
	o += pattern;
	return o;
}

void Logger_T::_create(SharedPtr_T<LoggerType>& o, StrViewA_T name, StrViewA_T outputFilepath)
{
	TempStringA_T<> temp;
	Vector_T<spdlog::sink_ptr, 4> sinks;

	auto console_sink = makeShared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::trace);

	//console_sink->set_pattern(toPattern(temp, name, "%^[%T] %n: %v%$").c_str());
	//console_sink->set_pattern("%^[%T] %n: %v%$");
	console_sink->set_pattern("%n\t: [%^%l%$]\t%v");

	sinks.emplace_back(console_sink);

	SharedPtr_T<spdlog::sinks::basic_file_sink_mt> file_sink;
	if (!outputFilepath.is_empty())
	{
		temp = outputFilepath;
		file_sink = makeShared<spdlog::sinks::basic_file_sink_mt>(temp.c_str(), true);
		file_sink->set_level(spdlog::level::trace);
		sinks.emplace_back(file_sink);
	}

	temp = name;
	o = makeShared<LoggerType>(temp.c_str(), sinks.begin(), sinks.end());
	//o = makeShared<LoggerType>(temp.c_str(), sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
	o->set_level(spdlog::level::trace);
}


#endif


}