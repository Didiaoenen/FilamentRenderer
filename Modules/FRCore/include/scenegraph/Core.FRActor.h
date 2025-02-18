#pragma once

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include <Tools.FREvent.h>

#include "Core.FREntity.h"
#include "Core.FRISerializable.h"

namespace FR
{
	class FRScene;
	class FRComponent;
	class FRCompTransform;

	class FRActor
		: public FREntity, public FRISerializable
	{
	public:
		FRActor(const std::string& pName, const std::string& pTag);

		bool IsDescendantOf(const FRActor* pActor);

		void SetActive(bool pActive);

		bool IsSelfActive() const;

		bool IsActive() const;

		bool IsAlive() const;

		bool HasParent() const;

		FRActor* GetParent() const;

		void SetParent(FRActor* pParent);

		void DetachFromParent();

		const std::vector<FRActor*>& GetChildren();

		FRScene* GetScene() const;

		void OnAwake();

		void OnStart();

		void OnEnable();

		void OnDisable();

		void OnDestroy();

		void OnUpdate(float pDeltaTime);

		void OnFixedUpdate(float pDeltaTime);

		void OnLateUpdate(float pDeltaTime);

		void MarkAsDestroy();

		const std::vector<FRComponent*>& GetComponents();

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pActorsRoot) override;

		bool RemoveComponent(FRComponent* pComponent);

		template<typename T, typename ... Args>
		T* AddComponent(Args&&... pArgs);

		template<typename T>
		bool RemoveComponent();

		template<typename T>
		T* GetComponent();

	private:
		void RecursiveActiveUpdate();

		void RecursiveWasActiveUpdate();

	public:
		virtual ~FRActor();

	public:
		std::string	tag;

		FREvent<FRComponent*> ComponentAddedEvent;
		FREvent<FRComponent*> ComponentRemovedEvent;

		inline static FREvent<FRActor*> CreatedEvent;
		inline static FREvent<FRActor*> DettachEvent;
		inline static FREvent<FRActor*> DestroyedEvent;
		inline static FREvent<FRActor*, FRActor*> AttachEvent;

	private:
		bool mActive{ true };

		bool mAwaked{ false };
		bool mStarted{ false };
		bool mDestroyed{ false };
		bool mWasActive{ false };

		FRScene* mScene{ nullptr };
		FRActor* mParent{ nullptr };
		std::vector<FRActor*> mChildren;
		std::vector<FRComponent*> mComponents;

	public:
		FRCompTransform* transform{ nullptr };

	};
}

#include "Core.FRActor.inl"
