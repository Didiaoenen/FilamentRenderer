#pragma once

#include <FRSceneWarp.h>
#include "Core.FRISerializable.h"

#include <vector>
#include <string>
#include <memory>

namespace FR
{
	class FRActor;
	class FRLight;
	class FRRenderable;

	class FRComponent;
	class FRCompLight;
	class FRCompCamera;
	class FREnvironment;
	class FRCompModelRenderer;

	class FRScene
		: public FRISerializable
	{
	public:
		struct FastAccessComponents
		{
			std::vector<FRCompLight*> lights;
			std::vector<FRCompCamera*> cameras;
			std::vector<FRCompModelRenderer*> modelRenderers;
		};

		FRScene();

		void Playing();

		void Update();

		void LateUpdate();

		void FixedUpdate();

		FRActor* CreateActor();

		FRActor* CreateActor(const std::string& pName, const std::string& pTag = "");

		bool DestroyActor(FRActor* pTarget);

		void CollectGarbages();

		FRActor* FindActorByName(const std::string& pName) const;

		FRActor* FindActorByTag(const std::string& pTag) const;

		FRActor* FindActorByID(int64_t pID) const;

		std::vector<std::reference_wrapper<FRActor>> FindActorsByName(const std::string& pName) const;

		std::vector<std::reference_wrapper<FRActor>> FindActorsByTag(const std::string& pTag) const;

		FRCompCamera* FindMainCamera() const;

		void SetEnvironment(FREnvironment* pEnvironment);

		void OnComponentAdded(FRComponent* pCompononent);

		void OnComponentRemoved(FRComponent* pCompononent);

		const std::vector<FRActor*>& GetActors();

		const FastAccessComponents& GetFastAccessComponents() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pRoot) override;

		void ParseScene();

		void AddLight(FRLight* pLight);

		void AddGizmo(FRRenderable* pRenderable);

		void AddRenderable(FRRenderable* pRenderable);

		void RemoveRenderable(FRRenderable* pRenderable);

		void RemoveLight(FRLight* pLight);

		FRSceneWarp* NativePtr();

	public:
		virtual ~FRScene();

	public:
		bool playing{ false };

	private:
		FRSceneWarp* mScene{ nullptr };
		FREnvironment* mEnvironment{ nullptr };

		std::vector<FRActor*> mActors;
		FastAccessComponents mFastAccessComponents;

		int64_t mAvailableID{ 0 };

	};
}
