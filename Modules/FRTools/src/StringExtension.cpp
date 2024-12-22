#include "StringExtension.h"

std::vector<std::string> FR::StringExtension::Split(const std::string& pTarget, const char pChar)
{
	std::vector<std::string> strs;
	
	std::string temp = pTarget;
	size_t index = temp.find('.');
	while (index != std::string::npos)
	{
		strs.push_back(temp.substr(0, index));
		temp = temp.substr(index + 1, -1);
		index = temp.find('.');

		if (index == std::string::npos && !temp.empty())
		{
			strs.push_back(temp);
		}
	}

	return strs;
}

bool FR::StringExtension::Replace(std::string& pTarget, const std::string& pFrom, const std::string& pTo)
{
	size_t start_pos = pTarget.find(pFrom);

	if (start_pos != std::string::npos)
	{
		pTarget.replace(start_pos, pFrom.length(), pTo);
		return true;
	}

	return false;
}

void FR::StringExtension::ReplaceAll(std::string& pTarget, const std::string& pFrom, const std::string& pTo)
{
	if (pFrom.empty()) return;

	size_t start_pos = 0;
	while ((start_pos = pTarget.find(pFrom, start_pos)) != std::string::npos)
	{
		pTarget.replace(start_pos, pFrom.length(), pTo);
		start_pos += pTo.length();
	}
}

std::string FR::StringExtension::GenerateUnique(const std::string& pSource, std::function<bool(std::string)> pIsAvailable)
{
    return std::string();
}
