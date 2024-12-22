#include "Tools.FRIniFile.h"

#include <fstream>
#include <filesystem>

FR::FRIniFile::FRIniFile(const std::string& pFilePath)
	: mFilePath(pFilePath)
{
	Load();
}

void FR::FRIniFile::Reload()
{
	RemoveAll();
	Load();
}

void FR::FRIniFile::Rewrite() const
{
	std::ofstream outfile;
	outfile.open(mFilePath, std::ios_base::trunc);

	if (outfile.is_open())
	{
		for (const auto& [key, value] : mData)
		{
			outfile << key << "=" << value << std::endl;
		}
	}

	outfile.close();
}

bool FR::FRIniFile::Remove(const std::string& pKey)
{
	if (IsKeyExisting(pKey))
	{
		mData.erase(pKey);
		return true;
	}
	return false;
}

void FR::FRIniFile::RemoveAll()
{
	mData.clear();
}

bool FR::FRIniFile::IsKeyExisting(const std::string& pKey) const
{
	return mData.find(pKey) != mData.end();
}

std::vector<std::string> FR::FRIniFile::GetFormattedContent() const
{
	std::vector<std::string> result;
	for (const auto& [key, value] : mData)
	{
		result.push_back(key + "=" + value);
	}
	return result;
}

void FR::FRIniFile::RegisterPair(const std::string& pKey, const std::string& pValue)
{
	RegisterPair(std::make_pair(pKey, pValue));
}

void FR::FRIniFile::RegisterPair(const AttributePair& pPair)
{
	mData.insert(pPair);
}

void FR::FRIniFile::Load()
{
	std::fstream iniFile;
	iniFile.open(mFilePath);

	if (iniFile.is_open())
	{
		std::string currentLine;

		while (std::getline(iniFile, currentLine))
		{
			if (IsValidLine(currentLine))
			{
				currentLine.erase(std::remove_if(currentLine.begin(), currentLine.end(), isspace), currentLine.end());
				RegisterPair(ExtractKeyAndValue(currentLine));
			}
		}

		iniFile.close();
	}
}

FR::FRIniFile::AttributePair FR::FRIniFile::ExtractKeyAndValue(const std::string& pAttributeLine) const
{
	return AttributePair();
}

bool FR::FRIniFile::IsValidLine(const std::string& pAttributeLine) const
{
	if (pAttributeLine.size() == 0)
	{
		return false;
	}

	if (pAttributeLine[0] == '#' || pAttributeLine[0] == ';' || pAttributeLine[0] == '[')
	{
		return false;
	}

	if (std::count(pAttributeLine.begin(), pAttributeLine.end(), '=') != 1)
	{
		return false;
	}

	return true;
}

bool FR::FRIniFile::StringToBoolean(const std::string& pValue) const
{
	return (pValue == "1" || pValue == "T" || pValue == "t" || pValue == "True" || pValue == "true");
}
