#pragma once

#include "Log.FRLogger.h"

namespace FR
{
	template<typename T>
	inline void FRLogger::LogToHandlerMap(std::map<std::string, T>& pMap, const FRILogHandler::LogData& pData, std::string pID)
	{
		if (pID != "default")
		{
			reinterpret_cast<FRILogHandler&>(pMap[pID]).Log(pData);
		}
		else
		{
			if (pMap.find("default") == pMap.end())
			{
				pMap.emplace("default", T());
			}
			reinterpret_cast<FRILogHandler&>(pMap["default"]).Log(pData);
		}
	}
}