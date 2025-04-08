#include "Editor.FRApplication.h"
#include "Editor.FREditorController.h"

#include <Core.FRGuiDrawer.h>
#include <Core.FRSceneManager.h>

#include <SystemExec.h>
#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <Log.FRLogger.h>
#include <Log.FRConsoleSink.h>

#include <utils/Path.h>

void FR::FRApplication::Destroy()
{
	FRSceneManager::Instance()->UnloadCurrentScene();

	FRApplication::Instance()->ktxManager.UnloadResources();
	FRApplication::Instance()->modelManager.UnloadResources();
	FRApplication::Instance()->textureManager.UnloadResources();
	FRApplication::Instance()->skeletonManager.UnloadResources();
	FRApplication::Instance()->animationManager.UnloadResources();
	FRApplication::Instance()->materialManager.UnloadResources();
	FRApplication::Instance()->shaderManager.UnloadResources();

	editorResources = nullptr;
	guiHelper = nullptr;
}

FR::FRApplication* FR::FRApplication::Instance()
{
	if (!sApplication)
	{
		sApplication = new FRApplication();
	}
	return sApplication;
}

std::unique_ptr<FR::FRImGuiHelper>& FR::FRApplication::GuiHelper()
{
	return Instance()->guiHelper;
}

std::unique_ptr<FR::FREditorResources>& FR::FRApplication::EditorResources()
{
	return Instance()->editorResources;
}

std::unique_ptr<FR::FRSceneRenderer>& FR::FRApplication::SceneRenderer()
{
	return Instance()->renderer;
}

const std::string FR::FRApplication::GetBinPath()
{
	return utils::Path(mBinPath).getAbsolutePath();
}

FR::FRApplication::FRApplication()
{
	FRServiceLocator::Provide<FRKtxManager>(ktxManager);
	FRServiceLocator::Provide<FRModelManager>(modelManager);
	FRServiceLocator::Provide<FRTextureManager>(textureManager);
	FRServiceLocator::Provide<FROzzSkeletonManager>(skeletonManager);
	FRServiceLocator::Provide<FROzzAnimationManager>(animationManager);
	FRServiceLocator::Provide<FRMaterialManager>(materialManager);
	FRServiceLocator::Provide<FRShaderManager>(shaderManager);
}

void FR::FRApplication::Initialize(const std::string& pProjectPath, const std::string& pProjectName)
{
	projectPath = pProjectPath;
	projectName = pProjectName;
	engineAssetsPath = "../../Resources/Data/Engine/";
	editorAssetsPath = "../../Resources/Data/Editor/";
	mBinPath = "../../Resources/Bin/";

	//logger = std::make_unique<FRLogger>();
	FRLogger::Instance()->AddSink(std::make_shared<FR::ConsoleSink_mt>());

	FRPathUtils::SetAssetPaths(projectPath, engineAssetsPath, editorAssetsPath);

	Window::Settings settings = { .title = "FREditor", .width = 1600.f, .height = 900.f };
	guiHelper = std::make_unique<FRImGuiHelper>(settings);
	{
		guiHelper->EnableDocking(true);
	}

	editorResources = std::make_unique<FREditorResources>();

	editor = std::make_unique<FREditorController>();

	renderer = std::make_unique<FRSceneRenderer>();

	FRGuiDrawer::ProvideEmptyTexture(editorResources->GetTexture("Empty_Texture"));

	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_INFO);
	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_WARN);
	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_TRACE);
	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_DEBUG);
	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_ERROR);
	FRLogger::Log("123123123123123", FRILogHandler::ELogLevel::LOG_CRITICAL);
}

void FR::FRApplication::TryRun()
{
	auto window = guiHelper->GetWindow();
	while (!window->ShouldClose())
	{
		window->Update();

		mInput.Update();
		editor->Update();

		mTimer.Update();
		mInput.Reset();
	}
}

FR::FRApplication::~FRApplication()
{
}
