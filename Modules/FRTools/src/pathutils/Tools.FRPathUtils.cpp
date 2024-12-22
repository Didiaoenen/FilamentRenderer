#include "Tools.FRPathUtils.h"

#include <algorithm>

#include <utils/Path.h>

void FR::FRPathUtils::SetAssetPaths(const std::string& pProjectAssetsPath, const std::string& pEngineAssetsPath, const std::string& pEditorAssetsPath)
{
	__PROJECT_ASSETS_PATH = pProjectAssetsPath;
	__ENGINE_ASSETS_PATH = pEngineAssetsPath;
	__EDITOR_ASSETS_PATH = pEditorAssetsPath;
}

std::string FR::FRPathUtils::MakeWindowsStyle(const std::string& pPath)
{
	std::string result;
	result.resize(pPath.size());

    for (size_t i = 0; i < pPath.size(); ++i)
    {
		result[i] = pPath[i] == '/' ? '\\' : pPath[i];
    }
	return result;
}

std::string FR::FRPathUtils::MakeNonWindowsStyle(const std::string& pPath)
{
	std::string result;
	result.resize(pPath.size());

	for (size_t i = 0; i < pPath.size(); ++i)
	{
		result[i] = pPath[i] == '\\' ? '/' : pPath[i];
	}
	return result;
}

std::string FR::FRPathUtils::GetContainingFolder(const std::string& pPath)
{
	std::string result;

	bool extraction = false;

	for (auto it = pPath.rbegin(); it != pPath.rend(); ++it)
	{
		if (extraction)
		{
			result += *it;
		}

		if (!extraction && it != pPath.rbegin() && (*it == '\\' || *it == '/'))
		{
			extraction = true;
		}
	}

	std::reverse(result.begin(), result.end());

	if (!result.empty() && result.back() != '\\')
	{
		result += '\\';
	}
	return result;
}

std::string FR::FRPathUtils::GetElementName(const std::string& pPath)
{
	std::string result;

	std::string path = pPath;
	if (!path.empty() && path.back() == '\\')
	{
		path.pop_back();
	}

	for (auto it = path.rbegin(); it != path.rend() && *it != '\\' && *it != '/'; ++it)
	{
		result += *it;
	}

	std::reverse(result.begin(), result.end());

	return result;
}

std::string FR::FRPathUtils::GetExtension(const std::string& pPath)
{
	std::string result;

	for (auto it = pPath.rbegin(); it != pPath.rend() && *it != '.'; ++it)
	{
		result += *it;
	}

	std::reverse(result.begin(), result.end());

	return result;
}

std::string FR::FRPathUtils::FileTypeToString(EFileType pFileType)
{
	switch (pFileType)
	{
	case EFileType::SCENE:
		return "Scene";
	case EFileType::MODEL:
		return "Model";
	case EFileType::SHADER:
		return "Shader";
	case EFileType::TEXTURE:
		return "Texture";
	case EFileType::MATERIAL:
		return "Material";
	case EFileType::FONT:
		return "Font";
	}

	return "Unknown";
}

FR::EFileType FR::FRPathUtils::GetFileType(const std::string& pPath)
{
	std::string ext = GetExtension(pPath);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	if (ext == "scene")
		return EFileType::SCENE;
	else if (ext == "obj")
		return EFileType::MODEL;
	else if (ext == "shader")
		return EFileType::SHADER;
	else if (ext == "png" || ext == "jpeg" || ext == "jpg" || ext == "tga")
		return EFileType::TEXTURE;
	else if (ext == "mat")
		return EFileType::MATERIAL;
	else if (ext == "anim")
		return EFileType::ANIMATION;
	else if (ext == "ozz")
		return EFileType::OZZMODEL;
	else if (ext == "ttf")
		return EFileType::FONT;

	return EFileType::NONE;
}

std::string FR::FRPathUtils::GetRealPath(const std::string& pPath)
{
	std::string result;

	if (pPath[0] == ':')
	{
		result = utils::Path(__ENGINE_ASSETS_PATH).getAbsolutePath().concat(std::string(pPath.data() + 1, pPath.data() + pPath.size()));
	}
	else
	{
		result = utils::Path(__PROJECT_ASSETS_PATH).concat("Assets").concat(pPath);
	}

	return result;
}

std::string FR::FRPathUtils::GetEditorPath(const std::string& pPath)
{
	return utils::Path(__EDITOR_ASSETS_PATH).getAbsolutePath() + (pPath);
}

std::string FR::FRPathUtils::GetEngineAssetsPath()
{
	return utils::Path(__ENGINE_ASSETS_PATH).getAbsolutePath();
}

std::string FR::FRPathUtils::GetProjectAssetsPath()
{
	return utils::Path(__PROJECT_ASSETS_PATH).concat("Assets");
}
