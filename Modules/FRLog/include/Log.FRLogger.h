#pragma once

#include <map>
#include <string>

#include "Log.FRILogHandler.h"
#include "Log.FRFileHandler.h"
#include "Log.FRConsoleHandler.h"
#include "Log.FRHistoryHandler.h"

#include <Tools.FREvent.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace FR
{
	#define __INFO_HEADER "[INFO] "
	#define __WARN_HEADER "[WARN] "
	#define __TRACE_HEADER "[TRACE] "
	#define __DEBUG_HEADER "[DEBUG] "
	#define __ERROR_HEADER "[ERROR] "
	#define __CRITICAL_HEADER "[CRITICAL] "

	#define FE_LOG_INFO(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::info, __VA_ARGS__)
	#define FE_LOG_WARN(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::warn, __VA_ARGS__)
	#define FE_LOG_ERROR(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::err, __VA_ARGS__)
	#define FE_LOG_TRACE(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::trace, __VA_ARGS__)
	#define FE_LOG_DEBUG(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::debug, __VA_ARGS__)
	#define FE_LOG_CRITICAL(...) SPDLOG_LOGGER_CALL(FRLogger::GetCoreLogger(), spdlog::level::level_enum::critical, __VA_ARGS__)

	class FRLogger
	{
	public:
		FRLogger();

		static FRLogger* Instance();

		static void Log(const std::string& pMessage,
			FRILogHandler::ELogLevel pLogLevel = FRILogHandler::ELogLevel::LOG_DEBUG,
			FRILogHandler::ELogMode pLogMode = FRILogHandler::ELogMode::DEFAULT, std::string pHandlerId = "default");

		static std::shared_ptr<spdlog::logger>& GetCoreLogger();

		void AddSink(const std::shared_ptr<spdlog::sinks::sink>& sink);

	private:
		std::string GetLogHeader(FRILogHandler::ELogLevel pLogLevel);

		template<typename T>
		static void LogToHandlerMap(std::map<std::string, T>& pMap, const FRILogHandler::LogData& pData, std::string pID);

	public:
		~FRLogger();

	public:
		static FREvent<const FRILogHandler::LogData&> LogEvent;

	private:
		static FRLogger* mLogger;

		static std::shared_ptr<spdlog::logger> mCoreLogger;

		static std::map<std::string, FRFileHandler> FILE_HANDLER_MAP;
		static std::map<std::string, FRConsoleHandler> CONSOLE_HANDLER_MAP;
		static std::map<std::string, FRHistoryHandler> HISTORY_HANDLER_MAP;

	};
}

#include "Log.FRLogger.inl"