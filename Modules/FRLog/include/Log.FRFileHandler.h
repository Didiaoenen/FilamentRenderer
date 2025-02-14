#pragma once

#include <Tools.FRTimer.h>
#include "Log.FRILogHandler.h"

#include <string>

namespace FR
{
	class FRFileHandler
		: public FRILogHandler
	{
	public:
		virtual void Log(const FRILogHandler::LogData& pLogData);

		static void SetLogFilePath(const std::string& pPath);
		
		static std::string& GetLogFilePath();

	private:
		static std::ofstream OUTPUT_FILE;

		inline static std::string __APP_LAUNCH_DATE = FRTimer::GetDateAsString();

		inline static std::string LOG_FILE_PATH = std::string(getenv("APPDATA")) + "/FREditor/Editor/" + __APP_LAUNCH_DATE + ".log";

	};
}