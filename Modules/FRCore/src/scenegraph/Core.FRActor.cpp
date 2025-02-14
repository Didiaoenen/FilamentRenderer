#include "Core.FRActor.h"

#include "Core.FRScene.h"
#include "Core.FRCompTransform.h"

FR::FRActor::FRActor(FRScene* pScene, const std::string& pName, const std::string& pTag)
	: transform(AddComponent<FRCompTransform>())
	, mScene(pScene)
	, tag(pTag)
{
	name = pName;
	CreatedEvent.Invoke(this);
}

FR::FRScene* FR::FRActor::GetScene() const
{
	return mScene;
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

void FR::FRActor::SetParent(FRActor* pParent)
{
	DetachFromParent();

	mParent = pParent;
	transform.SetParent(pParent->transform);

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

	transform.RemoveParent();
}

bool FR::FRActor::IsDescendantOf(const FRActor* pActor) const
{
	const FRActor* currentParentActor = mParent;

	while (currentParentActor != nullptr)
	{
		if (currentParentActor == pActor)
		{
			return true;
		}
		currentParentActor = currentParentActor->GetParent();
	}

	return false;
}

bool FR::FRActor::HasParent() const
{
	return mParent;
}

FR::FRActor* FR::FRActor::GetParent() const
{
	return mParent;
}

std::vector<FR::FRActor*>& FR::FRActor::GetChildren()
{
	return mChildren;
}

void FR::FRActor::MarkAsDestroy()
{
	mDestroyed = true;

	for (auto child : mChildren)
	{
		child->MarkAsDestroy();
	}
}

bool FR::FRActor::IsAlive() const
{
	return !mDestroyed;
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

bool FR::FRActor::RemoveComponent(FRComponent& pComponent)
{
	for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
	{
		if (it->get() == &pComponent)
		{
			ComponentRemovedEvent.Invoke(pComponent);
			mComponents.erase(it);
			return true;
		}
	}
	return false;
}

std::vector<std::shared_ptr<FR::FRComponent>>& FR::FRActor::GetComponents()
{
	return mComponents;
}

void FR::FRActor::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot)
{
}

void FR::FRActor::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot)
{
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

	std::for_each(mComponents.begin(), mComponents.end(), [&](std::shared_ptr<FRComponent> pComponent) { ComponentRemovedEvent.Invoke(*pComponent); });
	std::for_each(mChildren.begin(), mChildren.end(), [](FRActor* pElement) { delete pElement; });
}