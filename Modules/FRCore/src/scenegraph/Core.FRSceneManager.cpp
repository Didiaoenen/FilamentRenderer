#include "Core.FRSceneManager.h"

#include "Core.FRScene.h"
#include "Core.FRActor.h"
#include "Core.FRCompLight.h"
#include "Core.FRCompCamera.h"
#include "Core.FRCompTransform.h"

#include "Tools.FRTimer.h"

#include "PlayableGraphManager.h"

FR::FRSceneManager::FRSceneManager()
{
	//LoadEmptyScene();
}

void FR::FRSceneManager::Update()
{
	if (mDelayedLoadCall)
	{
		mDelayedLoadCall();
		mDelayedLoadCall = 0;
	}

	PlayableGraphManager::Instance()->Update(FRTimer::GetDeltaTimeSec());
}

void FR::FRSceneManager::LoadAndPlayDelayed(const std::string& pPath, bool pAbsolute)
{
	mDelayedLoadCall = [this, pPath, pAbsolute]
		{
			std::string previousSourcePath = GetCurrentSceneSourcePath();
			LoadScene(pPath, pAbsolute);
			StoreCurrentSceneSourcePath(previousSourcePath);
			GetCurrentScene()->Playing();
		};
}

void FR::FRSceneManager::LoadEmptyScene()
{
	UnloadCurrentScene();

	mCurrentScene = new FRScene();

	SceneLoadEvent.Invoke();
}

FR::FRScene* FR::FRSceneManager::LoadEmptyLightedScene()
{
	UnloadCurrentScene();

	mCurrentScene = new FRScene();

	SceneLoadEvent.Invoke();

	auto light = mCurrentScene->CreateActor("Directional Light");
	light->AddComponent<FRCompLight>();
	light->transform->SetLocalPosition({ 0.0f, 10.0f, 0.0f });
	auto lightRyp = glm::radians(glm::vec3(0.0f, 0.0f, 0.0f));
	light->transform->SetLocalRotation(glm::quat(glm::eulerAngleYXZ(lightRyp.y, lightRyp.x, lightRyp.z)));

	auto camera = mCurrentScene->CreateActor("Main Camera");
	camera->AddComponent<FRCompCamera>();
	camera->transform->SetLocalPosition({ 0.0f, 3.0f, 8.0f });
	auto cameraRyp = glm::radians(glm::vec3(20.0f, 180.0f, 0.0f));
	camera->transform->SetLocalRotation(glm::quat(glm::eulerAngleYXZ(cameraRyp.y, cameraRyp.x, cameraRyp.z)));

	return mCurrentScene;
}

bool FR::FRSceneManager::LoadScene(const std::string& pPath, bool pAbsolute)
{
	std::string completePath = (pAbsolute ? "" : mSceneRootFolder) + pPath;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(completePath.c_str());

	if (LoadSceneFromMemory(doc))
	{
		StoreCurrentSceneSourcePath(completePath);
		return true;
	}

	return false;
}

bool FR::FRSceneManager::LoadSceneFromMemory(tinyxml2::XMLDocument& pDoc)
{
	if (!pDoc.Error())
	{
		tinyxml2::XMLNode* root = pDoc.FirstChild();
		if (root)
		{
			tinyxml2::XMLNode* sceneNode = root->FirstChildElement("scene");
			if (sceneNode)
			{
				LoadEmptyScene();
				mCurrentScene->OnDeserialize(pDoc, sceneNode);
				return true;
			}
		}
	}

	return false;
}

void FR::FRSceneManager::UnloadCurrentScene()
{
	if (mCurrentScene)
	{
		delete mCurrentScene;
		mCurrentScene = nullptr;
		SceneUnloadEvent.Invoke();
	}

	ForgetCurrentSceneSourcePath();
}

FR::FRScene* FR::FRSceneManager::GetCurrentScene() const
{
	return mCurrentScene;
}

std::string FR::FRSceneManager::GetCurrentSceneSourcePath() const
{
	return mCurrentSceneSourcePath;
}

bool FR::FRSceneManager::IsCurrentSceneLoadedFromDisk() const
{
	return mCurrentSceneLoadedFromPath;
}

void FR::FRSceneManager::StoreCurrentSceneSourcePath(const std::string& pPath)
{
	mCurrentSceneSourcePath = pPath;
	mCurrentSceneLoadedFromPath = true;
	CurrentSceneSourcePathChangedEvent.Invoke(mCurrentSceneSourcePath);
}

void FR::FRSceneManager::ForgetCurrentSceneSourcePath()
{
	mCurrentSceneSourcePath = "";
	mCurrentSceneLoadedFromPath = false;
	CurrentSceneSourcePathChangedEvent.Invoke(mCurrentSceneSourcePath);
}

FR::FRSceneManager* FR::FRSceneManager::Instance()
{
	if (!sInstance)
	{
		sInstance = new FRSceneManager();
	}
	return sInstance;
}

FR::FRSceneManager::~FRSceneManager()
{
}