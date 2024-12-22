#include "Log.FRHistoryHandler.h"

namespace FR
{
	std::queue<FRILogHandler::LogData> FRHistoryHandler::LOG_QUEUE;
}

void FR::FRHistoryHandler::Log(const FRILogHandler::LogData& pLogData)
{
	LOG_QUEUE.push(pLogData);
}

std::queue<FR::FRILogHandler::LogData>& FR::FRHistoryHandler::GetLogQueue()
{
	return LOG_QUEUE;
}
