#pragma once

#include "FRRefWarp.h"
#include "FRBoxWarp.h"
#include "FREntityWarp.h"
#include "FREngineWarp.h"
#include "FRIndexBufferWarp.h"
#include "FRVertexBufferWarp.h"
#include "FRSkinningBufferWarp.h"
#include "FRMaterialInstanceWarp.h"
#include <filament/RenderableManager.h>

namespace FR
{
	class FRRenderableManagerWarp
		: public FRRefWarp<filament::RenderableManager>
	{
	public:
		using EPrimitiveType = filament::RenderableManager::PrimitiveType;

	public:

		class Builder
		{
			friend class FRRenderableManagerWarp;

		public:
			using EResult = filament::RenderableManager::Builder::Result;

		public:
			Builder(size_t pCount)
				: mBuilder(pCount)
			{
			}

			Builder& BoundingBox(FRBoxWarp&& pAxisAlignedBoundingBox)
			{
				mBuilder.boundingBox(RefValue(pAxisAlignedBoundingBox));
				return *this;
			}

			Builder& Geometry(size_t pIndex, EPrimitiveType pType,
				FRVertexBufferWarp* pVertices, FRIndexBufferWarp* pIndices, size_t pOffset, size_t pCount)
			{
				mBuilder.geometry(pIndex, pType, PtrValue(pVertices), PtrValue(pIndices), pOffset, pCount);
				return *this;
			}

			Builder& Material(size_t pIndex, FRMaterialInstanceWarp* pMmaterialInstance)
			{
				mBuilder.material(pIndex, PtrValue(pMmaterialInstance));
				return *this;
			}

			Builder& BlendOrder(size_t pPrimitiveIndex, uint16_t pOrder)
			{
				mBuilder.blendOrder(pPrimitiveIndex, pOrder);
				return *this;
			}

			Builder& Culling(bool pEnable)
			{
				mBuilder.culling(pEnable);
				return *this;
			}

			Builder& EnableSkinningBuffers(bool pEnabled = true)
			{
				mBuilder.enableSkinningBuffers(pEnabled);
				return *this;
			}

			Builder& Skinning(FRSkinningBufferWarp* pSkinningBuffer, size_t pCount, size_t pOffset)
			{
				mBuilder.skinning(PtrValue(pSkinningBuffer), pCount, pOffset);
				return *this;
			}

			EResult Build(FREngineWarp* pEngine, FREntityWarp* pEntity)
			{
				return mBuilder.build(*PtrValue(pEngine), PtrValue(pEntity));
			}

		private:
			filament::RenderableManager::Builder mBuilder;

		};

		class Instance
		{
		public:
			Instance(FRRenderableManagerWarp* pRenderableManager, FREntityWarp* pEntity)
				: mIns(PtrValue(pRenderableManager).getInstance(PtrValue(pEntity)))
			{
			}

			filament::RenderableManager::Instance Ins()
			{
				return mIns;
			}

		private:
			filament::RenderableManager::Instance mIns;

		};

		FRRenderableManagerWarp() = default;

		FRRenderableManagerWarp(FREngineWarp* pEngine);

		size_t GetPrimitiveCount(Instance pIinstance);

		void SetMaterialInstanceAt(Instance pInstance, size_t pPrimitiveIndex, FRMaterialInstanceWarp* pMaterialInstance);

		void SetAxisAlignedBoundingBox(Instance pInstance, FRBoxWarp&& pAABB);

		Instance GetInstance(FREntityWarp* pEntity);

		void Destroy(FREntityWarp* pEntity);

	};
}

