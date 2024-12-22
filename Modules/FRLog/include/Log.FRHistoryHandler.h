#pragma once

#include <queue>
#include "Log.FRILogHandler.h"

namespace FR
{
	class FRHistoryHandler
		: public FRILogHandler
	{
	public:
		virtual void Log(const FRILogHandler::LogData& pLogData);

		static std::queue<FRILogHandler::LogData>& GetLogQueue();

	private:
		static std::queue<FRILogHandler::LogData> LOG_QUEUE;

	};
}