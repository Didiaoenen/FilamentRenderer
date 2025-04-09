#include "Core.FRActor.h"
#include "Core.FRSerializer.h"
#include "Core.FRSceneManager.h"
#include "Core.FRCompTransform.h"
#include "Core.FRCompRendererable.h"
#include "Core.FRCompCamera.h"

FR::FRActor::FRActor(const std::string& pName, const std::string& pTag)
	: mScene(FRSceneManager::Instance()->GetCurrentScene())
	, transform(AddComponent<FRCompTransform>())
{
	tag = pTag;
	name = pName;
	mTransform = transform->GetFRTransform();

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
	mParentUUID = pParent->uUID;
	transform->SetParent(*pParent->transform);
	pParent->mChildren.push_back(this);

	AttachEvent.Invoke(this, pParent);
}

size_t FR::FRActor::GetParentUUID()
{
	return mParentUUID;
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
	mParentUUID = 0;

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

	for (auto& child : mChildren)
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
	tinyxml2::XMLNode* actorNode = pDoc.NewElement("actor");
	pActorsRoot->InsertEndChild(actorNode);

	FRSerializer::SerializeBoolean(pDoc, actorNode, "active", mActive);
	FRSerializer::SerializeString(pDoc, actorNode, "name", name);
	FRSerializer::SerializeString(pDoc, actorNode, "tag", tag);

	FRSerializer::SerializeString(pDoc, actorNode, "uUID", std::to_string(uUID));
	FRSerializer::SerializeString(pDoc, actorNode, "parentUUID", std::to_string(mParentUUID));

	tinyxml2::XMLNode* componentsNode = pDoc.NewElement("components");
	actorNode->InsertEndChild(componentsNode);

	for (auto& component : mComponents)
	{
		tinyxml2::XMLNode* componentNode = pDoc.NewElement("component");
		componentsNode->InsertEndChild(componentNode);

		FRSerializer::SerializeString(pDoc, componentNode, "type", typeid(*component).name());

		tinyxml2::XMLElement* data = pDoc.NewElement("data");
		componentNode->InsertEndChild(data);

		component->OnSerialize(pDoc, data);
	}
}

void FR::FRActor::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot)
{
	
	FRSerializer::DeserializeBoolean(pDoc, pActorsRoot, "active", mActive);
	FRSerializer::DeserializeString(pDoc, pActorsRoot, "name", name);
	FRSerializer::DeserializeString(pDoc, pActorsRoot, "tag", tag);

	uUID = std::stoull(FRSerializer::DeserializeString(pDoc, pActorsRoot, "uUID"));
	mParentUUID = std::stoull(FRSerializer::DeserializeString(pDoc, pActorsRoot, "parentUUID"));

	{
		tinyxml2::XMLNode* componentsRoot = pActorsRoot->FirstChildElement("components");
		if (componentsRoot)
		{
			tinyxml2::XMLElement* currentComponent = componentsRoot->FirstChildElement("component");

			while (currentComponent)
			{
				tinyxml2::XMLElement* componentType = currentComponent->FirstChildElement("type");
				std::string text = componentType->GetText();
				
				FRComponent* component = nullptr;
				if (text == typeid(FRCompTransform).name())
					component = transform;
				else if (text == typeid(FRCompLight).name())
					component = AddComponent<FRCompLight>();
				else if (text == typeid(FRCompCamera).name())
					component = AddComponent<FRCompCamera>();
				else if (text == typeid(FRCompRendererable).name())
					component = AddComponent<FRCompRendererable>();

				if (component)
				{
					component->OnDeserialize(pDoc, currentComponent->FirstChildElement("data"));
				}

				currentComponent = currentComponent->NextSiblingElement("component");
			}
		}
	}
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

	for (auto& child : mChildren)
	{
		child->RecursiveActiveUpdate();
	}
}

void FR::FRActor::RecursiveWasActiveUpdate()
{
	mWasActive = IsActive();

	for (const auto& child : mChildren)
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

	OnDestroy();

	DestroyedEvent.Invoke(this);

	for (const auto& child : mChildren)
	{
		child->DetachFromParent();
	}
	DetachFromParent();

	for (auto& component : mComponents)
	{
		ComponentRemovedEvent.Invoke(component);
		delete component; component = nullptr;
	}
	mComponents.clear();

	for (auto& child : mChildren)
	{
		delete child; child = nullptr;
	}
	mChildren.clear();
}