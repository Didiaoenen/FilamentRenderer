#pragma once

#include "Log.FRILogHandler.h"

namespace FR
{
	class FRConsoleHandler
		: public FRILogHandler
	{
	public:
		virtual void Log(const FRILogHandler::LogData& pLogData);

	};
}