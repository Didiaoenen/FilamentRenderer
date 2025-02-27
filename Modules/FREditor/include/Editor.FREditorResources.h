#pragma once

#include <string>
#include <unordered_map>

namespace FR
{
	class FRModel;
	class FRShader;
	class FRTexture2D;
	class FRMaterial;

	class FREditorResources
	{
	public:
		FREditorResources();

		FRTexture2D* GetTexture(const std::string& pID);

		FRShader* GetShader(const std::string& pID);

		FRModel* GetModel(const std::string& pID);

		FRMaterial* GetDefaultMaterial();

	public:
		virtual ~FREditorResources();

	private:
		FRMaterial* mDefaultMaterial{ nullptr };

		std::unordered_map<std::string, FRModel*> mModels;

		std::unordered_map<std::string, FRShader*> mShaders;

		std::unordered_map<std::string, FRTexture2D*> mTextures;

	};
}

