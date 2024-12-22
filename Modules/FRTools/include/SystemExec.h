#pragma once

#include <string>
#include <stdlib.h>

#include <Log.FRLogger.h>

namespace FR
{
    class SystemExec
    {
    public:
        static bool Exec(const std::string& pCommand)
        {
            if (system(pCommand.c_str()) == 0)
            {
                FRLogger::Log(std::format("Exec Success {0}", pCommand), FRILogHandler::ELogLevel::LOG_INFO);
                return true;
            }

			FRLogger::Log(std::format("Exec Failed {0}", pCommand), FRILogHandler::ELogLevel::LOG_INFO);
            return false;
        }

    };
}