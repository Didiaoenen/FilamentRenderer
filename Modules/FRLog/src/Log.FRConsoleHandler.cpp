#include "Log.FRConsoleHandler.h"

#include "Log.FRLogger.h"

void FR::FRConsoleHandler::Log(const FRILogHandler::LogData& pLogData)
{
	switch (pLogData.logLevel)
	{
	case ELogLevel::LOG_TRACE:
		FE_LOG_TRACE(pLogData.date + " " + pLogData.message);
		break;
	case ELogLevel::LOG_DEBUG:
		FE_LOG_DEBUG(pLogData.date + " " + pLogData.message);
		break;
	case ELogLevel::LOG_INFO:
		FE_LOG_INFO(pLogData.date + " " + pLogData.message);
		break;
	case ELogLevel::LOG_WARN:
		FE_LOG_WARN(pLogData.date + " " + pLogData.message);
		break;
	case ELogLevel::LOG_ERROR:
		FE_LOG_ERROR(pLogData.date + " " + pLogData.message);
		break;
	case ELogLevel::LOG_CRITICAL:
		FE_LOG_CRITICAL(pLogData.date + " " + pLogData.message);
		break;
	}
}
