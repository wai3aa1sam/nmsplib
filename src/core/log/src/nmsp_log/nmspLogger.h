#pragma once

#include "common/nmsp_log_common.h"

#include "nmsp_stl/extra/nmspSingleton.h"

#include <spdlog/spdlog.h>
#include <spdlog/async_logger.h>
//namespace spdlog {
//class logger;
//}

#if NMSP_DEBUG
	#define NMSP_CORE_LOG(...)			do{ ::nmsp::Logger_T::instance()->coreLog(::nmsp::LogLevel::Info,		__VA_ARGS__); } while(false)
	#define NMSP_CORE_LOG_DEBUG(...)	do{ ::nmsp::Logger_T::instance()->coreLog(::nmsp::LogLevel::Debug,		__VA_ARGS__); } while(false)
	#define NMSP_CORE_LOG_WARN(...)		do{ ::nmsp::Logger_T::instance()->coreLog(::nmsp::LogLevel::Warning,	__VA_ARGS__); } while(false)
	#define NMSP_CORE_LOG_ERROR(...)	do{ ::nmsp::Logger_T::instance()->coreLog(::nmsp::LogLevel::Error,		__VA_ARGS__); } while(false)

	#define NMSP_LOG(...)				do{ ::nmsp::Logger_T::instance()->clientLog(::nmsp::LogLevel::Info,		__VA_ARGS__); } while(false)
	#define NMSP_LOG_DEBUG(...)			do{ ::nmsp::Logger_T::instance()->clientLog(::nmsp::LogLevel::Debug,	__VA_ARGS__); } while(false)
	#define NMSP_LOG_WARN(...)			do{ ::nmsp::Logger_T::instance()->clientLog(::nmsp::LogLevel::Warning,	__VA_ARGS__); } while(false)
	#define NMSP_LOG_ERROR(...)			do{ ::nmsp::Logger_T::instance()->clientLog(::nmsp::LogLevel::Error,	__VA_ARGS__); } while(false)
#else
	#define NMSP_CORE_LOG(...)			
	#define NMSP_CORE_LOG_DEBUG(...)	
	#define NMSP_CORE_LOG_WARN(...)		
	#define NMSP_CORE_LOG_ERROR(...)	

	#define NMSP_LOG(...)				
	#define NMSP_LOG_DEBUG(...)			
	#define NMSP_LOG_WARN(...)			
	#define NMSP_LOG_ERROR(...)			
#endif // NMSP_DEBUG

namespace nmsp {

#if 0
#pragma mark --- Logger_T-Decl ---
#endif // 0
#if 1

struct Logger_CreateDesc
{
	StrViewA_T coreName = "Core";
	StrViewA_T coreOutputFilepath;

	StrViewA_T clientName = "Client";
	StrViewA_T clientOutputFilepath;
};

enum class LogLevel
{
	Unknown,
	Debug,
	Info,
	Warning,
	Error,
};

class Logger_T //: public TLSSingleton_T<Logger_T>
{
public:
	using CreateDesc	= Logger_CreateDesc;
	using Level			= LogLevel;

	using LoggerType = spdlog::logger;
	//using LoggerType = spdlog::async_logger;
public:
	static CreateDesc	makeCD	();
	static Logger_T*	instance();
	//static void			init	(const CreateDesc& cd) { instance()->create(cd); }

	Logger_T();
	~Logger_T();

	void create(const CreateDesc& cd);
	void destroy();

	template<class... ARGS>
	void coreLog(Level lv, const char* fmt, ARGS&&... args);

	template<class... ARGS>
	void clientLog(Level lv, const char* fmt, ARGS&&... args);

private:
	template<class... ARGS>
	void log(SharedPtr_T<LoggerType> logger, Level lv, const char* fmt, ARGS&&... args);

private:
	void _create(SharedPtr_T<LoggerType>& o, StrViewA_T name, StrViewA_T outputFilepath);

private:
	static std::atomic_int s_nLoggers;
	static Logger_T* s_instance;

	SharedPtr_T<LoggerType> _coreLogger;
	SharedPtr_T<LoggerType> _clientLogger;
};
//extern Logger_T* g_logger;

template<class... ARGS> inline
void Logger_T::coreLog(Level lv, const char* fmt, ARGS&&... args) 
{
	log(_coreLogger, lv, fmt, nmsp::forward<ARGS>(args)...);
}

template<class... ARGS> inline
void Logger_T::clientLog(Level lv, const char* fmt, ARGS&&... args) 
{
	log(_clientLogger, lv, fmt, nmsp::forward<ARGS>(args)...);
}

template<class... ARGS> inline
void Logger_T::log(SharedPtr_T<LoggerType> logger, Level lv, const char* fmt, ARGS&&... args) 
{
	NMSP_ASSERT(logger, "logger is nullptr");
	using EM = Level;
	switch (lv)
	{
		case EM::Debug:		{ logger->debug	(fmt, nmsp::forward<ARGS>(args)...); }	break;
		case EM::Info:		{ logger->info	(fmt, nmsp::forward<ARGS>(args)...); }	break;
		case EM::Warning:	{ logger->warn	(fmt, nmsp::forward<ARGS>(args)...); }	break;
		case EM::Error:		{ logger->error	(fmt, nmsp::forward<ARGS>(args)...); }	break;

		default:
		{
			NMSP_ASSERT(false, "Logger_T::log()");
		} break;
	}
}

#endif

}