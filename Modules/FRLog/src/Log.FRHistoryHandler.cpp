#include "Log.FRHistoryHandler.h"

void FR::FRHistoryHandler::Log(const FRILogHandler::LogData& pLogData)
{
	LOG_QUEUE.push(pLogData);
}

std::queue<FR::FRILogHandler::LogData>& FR::FRHistoryHandler::GetLogQueue()
{
	return LOG_QUEUE;
}
