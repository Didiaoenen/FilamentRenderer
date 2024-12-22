#pragma once

#include <string>
#include <unordered_map>

namespace FR
{
	class FRIniFile
	{
	public:
		using AttributePair = std::pair<std::string, std::string>;
		using AttributeMap = std::unordered_map<std::string, std::string>;

		FRIniFile() = default;

		FRIniFile(const std::string& pFilePath);

		void Reload();

		void Rewrite() const;

		template<typename T>
		T Get(const std::string& pKey);

		template<typename T>
		T GetOrDefault(const std::string& pKey, T pDefault);

		template<typename T>
		bool Set(const std::string& pKey, const T& pValue);

		template<typename T>
		bool Add(const std::string& pKey, const T& pValue);

		bool Remove(const std::string& pKey);

		void RemoveAll();

		bool IsKeyExisting(const std::string& pKey) const;

		std::vector<std::string> GetFormattedContent() const;

	private:
		void RegisterPair(const std::string& pKey, const std::string& pValue);
		void RegisterPair(const AttributePair& pPair);

		void Load();

		AttributePair	ExtractKeyAndValue(const std::string& pAttributeLine) const;
		bool			IsValidLine(const std::string& pAttributeLine) const;
		bool			StringToBoolean(const std::string& pValue) const;

	private:
		AttributeMap	mData;
		std::string		mFilePath;

	};
}

#include "Tools.FRIniFile.inl"