#pragma once

#include "Log.FRILogHandler.h"

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
		static std::string GetLogHeader(ELogLevel pLogLevel);

		static std::string __APP_LAUNCH_DATE;

		static std::string LOG_FILE_PATH;

		static std::ofstream OUTPUT_FILE;

	};
}