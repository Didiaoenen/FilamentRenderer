#include "Core.FRActor.h"

#include "Core.FRScene.h"
#include "Core.FRSceneManager.h"
#include "Core.FRCompTransform.h"
#include "FRTransformManagerWarp.h"
#include "FRRenderableManagerWarp.h"

FR::FRActor::FRActor(const std::string& pName, const std::string& pTag)
	: mScene(FRSceneManager::Instance()->GetCurrentScene())
	, FREntity()
{
	tag = pTag;
	name = pName;
	transform = AddComponent<FRCompTransform>();

	auto engine = FRFilamentHelper::GetEngine();
	auto tcm = engine->GetTransformManager();
	tcm->Create(mEntity, {}, glm::mat4(1.0));

	FRRenderableManagerWarp::Builder builder(1);
	builder.BoundingBox({ { -0.5f, -0.5f , -0.5f }, { 0.5f ,0.5f ,0.5f } });
	builder.Build(engine, mEntity);

	CreatedEvent.Invoke(this);
}

bool FR::FRActor::IsDescendantOf(const FRActor* pActor)
{
	const FRActor* parentActor = mParent;

	while (parentActor)
	{
		if (parentActor == pActor)
		{
			return true;
		}
		parentActor = parentActor->GetParent();
	}

	return false;
}

void FR::FRActor::SetActive(bool pActive)
{
	if (pActive != mActive)
	{
		RecursiveWasActiveUpdate();

		mActive = pActive;
		RecursiveActiveUpdate();
	}
}

bool FR::FRActor::IsSelfActive() const
{
	return mActive;
}

bool FR::FRActor::IsActive() const
{
	return mActive && (mParent ? mParent->IsActive() : true);
}

bool FR::FRActor::IsAlive() const
{
	return !mDestroyed;
}

bool FR::FRActor::HasParent() const
{
	return mParent;
}

FR::FRActor* FR::FRActor::GetParent() const
{
	return mParent;
}

void FR::FRActor::SetParent(FRActor* pParent)
{
	DetachFromParent();

	mParent = pParent;
	transform->SetParent(*pParent->transform);
	pParent->mChildren.push_back(this);

	AttachEvent.Invoke(this, pParent);
}

void FR::FRActor::DetachFromParent()
{
	DettachEvent.Invoke(this);

	if (mParent)
	{
		mParent->mChildren.erase(std::remove_if(mParent->mChildren.begin(), mParent->mChildren.end(), [this](FRActor* pElement)
			{
				return pElement == this;
			}));
	}

	mParent = nullptr;

	transform->RemoveParent();
}

const std::vector<FR::FRActor*>& FR::FRActor::GetChildren()
{
	return mChildren;
}

FR::FRScene* FR::FRActor::GetScene() const
{
	return mScene;
}

void FR::FRActor::OnAwake()
{
	mAwaked = true;
	std::for_each(mComponents.begin(), mComponents.end(), [](auto element) { element->OnAwake(); });
}

void FR::FRActor::OnStart()
{
	mStarted = true;
	std::for_each(mComponents.begin(), mComponents.end(), [](auto element) { element->OnStart(); });
}

void FR::FRActor::OnEnable()
{
	std::for_each(mComponents.begin(), mComponents.end(), [](auto element) { element->OnEnable(); });
}

void FR::FRActor::OnDisable()
{
	std::for_each(mComponents.begin(), mComponents.end(), [](auto element) { element->OnDisable(); });
}

void FR::FRActor::OnDestroy()
{
	std::for_each(mComponents.begin(), mComponents.end(), [](auto element) { element->OnDestroy(); });
}

void FR::FRActor::OnUpdate(float pDeltaTime)
{
	if (IsActive())
	{
		std::for_each(mComponents.begin(), mComponents.end(), [&](auto element) { element->OnUpdate(pDeltaTime); });
	}
}

void FR::FRActor::OnFixedUpdate(float pDeltaTime)
{
	if (IsActive())
	{
		std::for_each(mComponents.begin(), mComponents.end(), [&](auto element) { element->OnFixedUpdate(pDeltaTime); });
	}
}

void FR::FRActor::OnLateUpdate(float pDeltaTime)
{
	if (IsActive())
	{
		std::for_each(mComponents.begin(), mComponents.end(), [&](auto element) { element->OnLateUpdate(pDeltaTime); });
	}
}

void FR::FRActor::MarkAsDestroy()
{
	mDestroyed = true;

	for (auto child : mChildren)
	{
		child->MarkAsDestroy();
	}
}

const std::vector<FR::FRComponent*>& FR::FRActor::GetComponents()
{
	return mComponents;
}

void FR::FRActor::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot)
{
}

void FR::FRActor::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot)
{
}

bool FR::FRActor::RemoveComponent(FRComponent* pComponent)
{
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (*it == pComponent)
		{
			ComponentRemovedEvent.Invoke(pComponent);
			mComponents.erase(it);
			return true;
		}
	}

	return false;
}

void FR::FRActor::RecursiveActiveUpdate()
{
	bool isActive = IsActive();

	if (!mWasActive && isActive)
	{
		if (!mAwaked)
		{
			OnAwake();
		}

		if (!mStarted)
		{
			OnStart();
		}

		OnEnable();
	}

	if (mWasActive && !isActive)
	{
		OnDisable();
	}

	for (auto child : mChildren)
	{
		child->RecursiveActiveUpdate();
	}
}

void FR::FRActor::RecursiveWasActiveUpdate()
{
	mWasActive = IsActive();
	for (auto child : mChildren)
	{
		child->RecursiveWasActiveUpdate();
	}
}

FR::FRActor::~FRActor()
{
	if (IsActive())
	{
		OnDisable();
	}

	{
		OnDestroy();
	}

	{
		DestroyedEvent.Invoke(this);
	}

	std::vector<FRActor*> toDetach = mChildren;

	for (auto child : toDetach)
	{
		child->DetachFromParent();
	}

	toDetach.clear();

	DetachFromParent();

	for (const auto component : mComponents)
	{
		ComponentRemovedEvent.Invoke(component);
		delete component;
	}
	mComponents.clear();

	for (const auto child : mChildren)
	{
		delete child;
	}
	mChildren.clear();

	FRFilamentHelper::DestroyEntity(mEntity);
}