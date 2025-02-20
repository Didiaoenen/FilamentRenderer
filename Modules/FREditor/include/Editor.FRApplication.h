#pragma once

#include "Editor.FRInput.h"
#include "Editor.FRImGuiHelper.h"
#include "Editor.FREditorResources.h"

#include <AnimationManager.h>
#include <Core.FRKtxManager.h>
#include <Core.FRModelManager.h>
#include <Core.FRSceneRenderer.h>
#include <Core.FRShaderManager.h>
#include <Core.FRTextureManager.h>
#include <Core.FRMaterialManager.h>

#include <Tools.FRTimer.h>

namespace FR
{
	class FRLogger;
	class FREditorController;

	class FRApplication
	{
	public:
		FRApplication();

		static void Destroy();

		static FRApplication* Instance();

		static std::unique_ptr<FRImGuiHelper>& GuiHelper();

		static std::unique_ptr<FREditorResources>& EditorResources();

		static std::unique_ptr<FRSceneRenderer>& SceneRenderer();

		static const std::string GetBinPath();

		void Initialize(const std::string& pProjectPath, const std::string& pProjectName);

		void TryRun();

	public:
		virtual ~FRApplication();

	public:
		std::string projectPath;
		std::string projectName;
		std::string editorAssetsPath;
		std::string engineAssetsPath;
		std::string projectAssetsPath;

	private:
		FRInput mInput;
		FRTimer mTimer;

		FRKtxManager ktxManager;
		FRModelManager modelManager;
		FRShaderManager shaderManager;
		FRTextureManager textureManager;
		FRMaterialManager materialManager;
		AnimationManager animationManager;

		std::unique_ptr<FRLogger> logger;

		std::unique_ptr<FREditorController> editor;

		inline static FRApplication* sApplication{ nullptr };

		inline static std::unique_ptr<FRImGuiHelper> guiHelper{ nullptr };
		inline static std::unique_ptr<FREditorResources> editorResources{ nullptr };
		
		inline static std::unique_ptr<FRSceneRenderer> renderer{ nullptr };

		inline static std::string mBinPath;
	};
}

