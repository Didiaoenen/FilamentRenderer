#pragma once

#include <string>
#include <EFileType.h>

namespace FR
{
	class FRPathUtils
	{
	public:
		static void SetAssetPaths(const std::string& pProjectAssetsPath, const std::string& pEngineAssetsPath, const std::string& pEditorAssetsPath);

		static std::string MakeWindowsStyle(const std::string& pPath);

		static std::string MakeNonWindowsStyle(const std::string& pPath);

		static std::string GetContainingFolder(const std::string& pPath);

		static std::string GetElementName(const std::string& pPath);

		static std::string GetExtension(const std::string& pPath);

		static std::string FileTypeToString(EFileType pFileType);

		static EFileType GetFileType(const std::string& pPath);

		static std::string GetRealPath(const std::string& pPath);

		static std::string GetEditorPath(const std::string& pPath);
		
		static std::string GetEngineAssetsPath();

		static std::string GetProjectAssetsPath();

	private:
		inline static std::string __PROJECT_ASSETS_PATH = "";
		inline static std::string __ENGINE_ASSETS_PATH = "";
		inline static std::string __EDITOR_ASSETS_PATH = "";

	};
}

