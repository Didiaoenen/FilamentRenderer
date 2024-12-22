#pragma once

#include <string>
#include <cstdint>

namespace FR
{
	class FRILogHandler
	{
		friend class FRLogger;

	public:

		enum class ELogLevel : uint8_t
		{
			LOG_INFO,
			LOG_WARN,
			LOG_TRACE,
			LOG_DEBUG,
			LOG_ERROR,
			LOG_CRITICAL,
		};

		enum class ELogMode : uint8_t
		{
			DEFAULT,
			CONSOLE,
			HISTORY,
			FILE,
			ALL
		};

		struct LogData
		{
			std::string date;
			std::string message;
			FRILogHandler::ELogLevel logLevel;
		};

	protected:
		virtual void Log(const LogData& pLogData) = 0;

	};
}