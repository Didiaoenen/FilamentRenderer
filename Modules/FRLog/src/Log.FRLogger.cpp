#include "Log.FRLogger.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace FR
{
	std::vector<spdlog::sink_ptr> sinks;
}

FR::FRLogger::FRLogger()
{
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

	// create the loggers
	mCoreLogger = std::make_shared<spdlog::logger>("App", begin(sinks), end(sinks));
	spdlog::register_logger(mCoreLogger);

	// configure the loggers
	spdlog::set_pattern("%^[%T] %v%$");
	mCoreLogger->set_level(spdlog::level::trace);
}

FR::FRLogger* FR::FRLogger::Instance()
{
	if (!mLogger)
	{
		mLogger = new FRLogger();
	}
	return mLogger;
}

void FR::FRLogger::Log(const std::string& pMessage, FRILogHandler::ELogLevel pLogLevel, FRILogHandler::ELogMode pLogMode, std::string pHandlerId)
{
	FRILogHandler::LogData logData{ "", pMessage, pLogLevel };

	switch (pLogMode)
	{
	case FRILogHandler::ELogMode::FILE:
		LogToHandlerMap<FRFileHandler>(FILE_HANDLER_MAP, logData, pHandlerId);
		break;
	case FRILogHandler::ELogMode::DEFAULT:
	case FRILogHandler::ELogMode::CONSOLE:
		LogToHandlerMap<FRConsoleHandler>(CONSOLE_HANDLER_MAP, logData, pHandlerId);
		break;
	case FRILogHandler::ELogMode::HISTORY:
		LogToHandlerMap<FRHistoryHandler>(HISTORY_HANDLER_MAP, logData, pHandlerId);
		break;
	case FRILogHandler::ELogMode::ALL:
		LogToHandlerMap<FRFileHandler>(FILE_HANDLER_MAP, logData, pHandlerId);
		LogToHandlerMap<FRConsoleHandler>(CONSOLE_HANDLER_MAP, logData, pHandlerId);
		LogToHandlerMap<FRHistoryHandler>(HISTORY_HANDLER_MAP, logData, pHandlerId);
		break;
	}

	LogEvent.Invoke(logData);
}

std::shared_ptr<spdlog::logger>& FR::FRLogger::GetCoreLogger()
{
	return Instance()->mCoreLogger;
}

void FR::FRLogger::AddSink(const std::shared_ptr<spdlog::sinks::sink>& sink)
{
	mCoreLogger->sinks().push_back(sink);
	mCoreLogger->set_pattern("%v%$");
}

std::string FR::FRLogger::GetLogHeader(FRILogHandler::ELogLevel pLogLevel)
{
	switch (pLogLevel)
	{
	case FRILogHandler::ELogLevel::LOG_INFO:
		return __INFO_HEADER;
	case FRILogHandler::ELogLevel::LOG_WARN:
		return __WARN_HEADER;
	case FRILogHandler::ELogLevel::LOG_DEBUG:
		return __DEBUG_HEADER;
	case FRILogHandler::ELogLevel::LOG_ERROR:
		return __ERROR_HEADER;
	default:
		return __INFO_HEADER;
	}
}

FR::FRLogger::~FRLogger()
{
	mCoreLogger.reset();
	spdlog::shutdown();
}
