#include "Log.FRFileHandler.h"

#include <Tools.FRTimer.h>

#include <fstream>
#include <iostream>

namespace FR
{
	std::ofstream FRFileHandler::OUTPUT_FILE;

	std::string FRFileHandler::__APP_LAUNCH_DATE = FRTimer::GetDateAsString();
	std::string FRFileHandler::LOG_FILE_PATH = std::string(getenv("APPDATA")) + "/FREditor/Editor/" + __APP_LAUNCH_DATE + ".log";
}

void FR::FRFileHandler::Log(const FRILogHandler::LogData& pLogData)
{
	if (!OUTPUT_FILE.is_open())
	{
		OUTPUT_FILE.open(LOG_FILE_PATH, std::ios_base::app);
	}

	if (OUTPUT_FILE.is_open())
	{
		OUTPUT_FILE << pLogData.date << " " << pLogData.message << std::endl;
	}
}

std::string& FR::FRFileHandler::GetLogFilePath()
{
	return LOG_FILE_PATH;
}

void FR::FRFileHandler::SetLogFilePath(const std::string& pPath)
{
	int i = pPath.size() - 1;
	while (pPath[i] != '/') --i;

	std::string fileName = pPath.substr(i + 1, pPath.size() - 1);

	LOG_FILE_PATH = pPath.substr(0, i + 1) + __APP_LAUNCH_DATE + fileName;
}
