#pragma once

#include "FRRefWarp.h"
#include "FREntityWarp.h"
#include <glm/glm.hpp>
#include <filament/TransformManager.h>

namespace FR
{
	class FREngineWarp;

	class FRTransformManagerWarp
		: public FRRefWarp<filament::TransformManager>
	{
	public:

		class Instance
		{
		public:
			Instance() = default;

			Instance(FRTransformManagerWarp* pTransformManager, FREntityWarp* pEntity)
				: mIns(PtrValue(pTransformManager).getInstance(PtrValue(pEntity)))
			{
			}

			filament::TransformManager::Instance Ins()
			{
				return mIns;
			}

		private:
			filament::TransformManager::Instance mIns;

		};

		FRTransformManagerWarp() = default;

		FRTransformManagerWarp(FREngineWarp* pEngine);

		void SetTransform(Instance pInstance, const glm::mat4& pLocalTransform);

		void Create(FREntityWarp* pEntity, Instance pParent, const glm::mat4& pLocalTransform);

		Instance GetInstance(FREntityWarp* pEntity);

		void Destroy(FREntityWarp* pEntity);

	};
}

