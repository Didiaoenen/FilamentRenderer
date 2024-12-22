#pragma once

#include "Log.FRILogHandler.h"

#include <Tools.FROptRef.h>
#include <Tools.FRMessage.h>

#include <spdlog/fmt/chrono.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>

#include <mutex>

namespace FR
{
	template <typename Mutex>
	class FRConsoleSink
		: public spdlog::sinks::base_sink<Mutex>
	{
	public:
		explicit FRConsoleSink() {}

		FRConsoleSink(const FRConsoleSink&) = delete;

		FRConsoleSink& operator=(const FRConsoleSink&) = delete;
		
		// SPDLog sink interface
		virtual void sink_it_(const spdlog::details::log_msg& pMsg) override
		{
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<Mutex>::formatter_->format(pMsg, formatted);
			std::string source = std::format("File : {0} | Function : {1} | Line : {2} {3}", "None", pMsg.source.funcname, pMsg.source.line, pMsg.payload.data());
			
			std::time_t time_t = std::chrono::system_clock::to_time_t(pMsg.time);
			std::string time = std::format("{:02}:{:02}:{:02}", std::localtime(&time_t)->tm_hour, std::localtime(&time_t)->tm_min, std::localtime(&time_t)->tm_sec);

			FRMessage::Invoke<FRILogHandler::LogData>(EventType::LOG, FRILogHandler::LogData{ time, fmt::to_string(formatted), GetMessageLevel(pMsg.level)});
		}

		virtual void flush_() override
		{
			//ConsolePanel::Flush();
		};

		static FRILogHandler::ELogLevel GetMessageLevel(const spdlog::level::level_enum level)
		{
			switch (level)
			{
			case spdlog::level::level_enum::info:
				return FRILogHandler::ELogLevel::LOG_INFO;
			case spdlog::level::level_enum::warn:
				return FRILogHandler::ELogLevel::LOG_WARN;
			case spdlog::level::level_enum::trace:
				return FRILogHandler::ELogLevel::LOG_TRACE;
			case spdlog::level::level_enum::debug:
				return FRILogHandler::ELogLevel::LOG_DEBUG;
			case spdlog::level::level_enum::err:
				return FRILogHandler::ELogLevel::LOG_ERROR;
			case spdlog::level::level_enum::critical:
				return FRILogHandler::ELogLevel::LOG_CRITICAL;
			default:
				return FRILogHandler::ELogLevel::LOG_INFO;
			}
		}

	public:
		virtual ~FRConsoleSink() = default;

	};

	using ConsoleSink_mt = FRConsoleSink<std::mutex>;
	using ConsoleSink_st = FRConsoleSink<spdlog::details::null_mutex>;

}