#include "Editor.FREditorResources.h"

#include <Core.FRMesh.h>
#include <Core.FRModel.h>
#include <Core.FRScene.h>
#include <Core.FRShader.h>
#include <Core.FRMaterial.h>

#include <Core.FRKtxManager.h>
#include <Core.FRModelLoader.h>
#include <Core.FRShaderLoader.h>
#include <Core.FRTextureLoader.h>
#include <Core.FRMaterialLoader.h>

#include <FRFilamentHelper.h>
#include <FRTextureSamplerWarp.h>

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <utils/Path.h>

FR::FREditorResources::FREditorResources()
{
	std::string editorPath = FRPathUtils::GetEditorPath("");

	mTextures["FileIcon_Texture"] = FRTextureLoader::Create(utils::Path::concat(editorPath, "Icons/FileIcon.png"), FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false);
	mTextures["DirectoryIcon_Texture"] = FRTextureLoader::Create(utils::Path::concat(editorPath, "Icons/DirectoryIcon.png"), FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false);

	mModels["Plane"] = FRModelLoader::Create(utils::Path::concat(editorPath, "Models/Plane.fbx"));
	mModels["Camera"] = FRModelLoader::Create(utils::Path::concat(editorPath, "Models/Camera.fbx"));

	mShaders["Grid"] = FRShaderLoader::Create(utils::Path::concat(editorPath, "Shaders/grid.shader"));

	{
		mTextures["Empty_Texture"] = FRTextureLoader::Create(utils::Path::concat(editorPath, "Textures/Empty.png"), FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false);
		mTextures["DarkBackground_Texture"] = FRTextureLoader::Create(utils::Path::concat(editorPath, "Textures/DarkBackground.png"), FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR, false);
	}

	mTextures["IBL"] = GetService(FRKtxManager)[":IBL/lightroom_14b/lightroom_14b_ibl.ktx"];
	mTextures["Skybox"] = GetService(FRKtxManager)[":IBL/lightroom_14b/lightroom_14b_skybox.ktx"];
}

FR::FRTexture2D* FR::FREditorResources::GetTexture(const std::string& pID)
{
	if (mTextures.find(pID) != mTextures.end())
	{
		return mTextures[pID];
	}
	return nullptr;
}

FR::FRShader* FR::FREditorResources::GetShader(const std::string& pID)
{
	if (mShaders.find(pID) != mShaders.end())
	{
		return mShaders[pID];
	}
	return nullptr;
}

FR::FRModel* FR::FREditorResources::GetModel(const std::string& pID)
{
	if (mModels.find(pID) != mModels.end())
	{
		return mModels[pID];
	}
	return nullptr;
}

FR::FRMaterial* FR::FREditorResources::GetDefaultMaterial()
{
	return mDefaultMaterial;
}

FR::FREditorResources::~FREditorResources()
{
}
