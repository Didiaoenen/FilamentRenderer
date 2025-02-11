#pragma once

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include <Tools.FREvent.h>

#include "Core.FRObject.h"
#include "Core.FRISerializable.h"

namespace FR
{
	class FRScene;
	class FRComponent;
	class FRCompTransform;

	class FRActor
		: public FRObject, public FRISerializable
	{
	public:
		FRActor(FRScene* pScene, const std::string& pName, const std::string& pTag);

		FRScene* GetScene() const;

		void SetActive(bool pActive);

		bool IsSelfActive() const;

		bool IsActive() const;

		void SetParent(FRActor& pParent);

		void DetachFromParent();

		bool IsDescendantOf(const FRActor* pActor) const;

		bool HasParent() const;

		FRActor* GetParent() const;

		std::vector<FRActor*>& GetChildren();

		void MarkAsDestroy();

		bool IsAlive() const;

		void OnAwake();

		void OnStart();

		void OnEnable();

		void OnDisable();

		void OnDestroy();

		void OnUpdate(float pDeltaTime);

		void OnFixedUpdate(float pDeltaTime);

		void OnLateUpdate(float pDeltaTime);

		template<typename T>
		T* GetComponent() const;

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... pArgs);

		template<typename T>
		bool RemoveComponent();

		bool RemoveComponent(FRComponent& pComponent);

		std::vector<std::shared_ptr<FRComponent>>& GetComponents();

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot) override;

	private:
		void RecursiveActiveUpdate();

		void RecursiveWasActiveUpdate();

	public:
		virtual ~FRActor() override;

	public:
		std::string	tag;

		FREvent<FRComponent&> ComponentAddedEvent;
		FREvent<FRComponent&> ComponentRemovedEvent;

		static FREvent<FRActor&> CreatedEvent;
		static FREvent<FRActor&> DettachEvent;
		static FREvent<FRActor&> DestroyedEvent;
		static FREvent<FRActor&, FRActor&> AttachEvent;

	private:
		bool mActive = true;

		bool mAwaked = false;
		bool mStarted = false;
		bool mDestroyed = false;
		bool mWasActive = false;

		FRScene* mScene{ nullptr };
		FRActor* mParent{ nullptr };
		std::vector<FRActor*> mChildren;

		std::vector<std::shared_ptr<FRComponent>> mComponents;

	public:
		FRCompTransform& transform;

	};
}

#include "Core.FRActor.inl"
