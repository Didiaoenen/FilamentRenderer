#pragma once

#include <string>
#include <vector>
#include <functional>

namespace FR
{
	class StringExtension
	{
	public:
		static std::vector<std::string> Split(const std::string& pTarget, const char pChar);
		
		static bool Replace(std::string& pTarget, const std::string& pFrom, const std::string& pTo);

		static void ReplaceAll(std::string& pTarget, const std::string& pFrom, const std::string& pTo);

		static std::string GenerateUnique(const std::string& pSource, std::function<bool(std::string)> pIsAvailable);
	};
}
