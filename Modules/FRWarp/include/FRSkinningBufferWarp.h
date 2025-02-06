#pragma once

#include "FRPtrWarp.h"
#include <glm/glm.hpp>
#include <filament/SkinningBuffer.h>

namespace FR
{
	class FREngineWarp;

	class FRSkinningBufferWarp
		: public FRPtrWarp<filament::SkinningBuffer>
	{
	public:

		class Builder
		{
			friend class FRSkinningBufferWarp;

		public:
			Builder()
				: mBuilder()
			{
			}

			Builder& BoneCount(uint32_t pBoneCount)
			{
				mBuilder.boneCount(pBoneCount);
				return *this;
			}

			Builder& Initialize(bool pInitialize = true)
			{
				mBuilder.initialize(pInitialize);
				return *this;
			}

			FRSkinningBufferWarp* Build(FREngineWarp* pEngine)
			{
				return new FRSkinningBufferWarp(pEngine, this);
			}

		private:
			filament::SkinningBuffer::Builder mBuilder;

		};

		FRSkinningBufferWarp() = default;

		FRSkinningBufferWarp(FREngineWarp* pEngine, Builder* pBuilder);

		void SetBones(FREngineWarp* pEngine, glm::mat4* pTransforms, size_t pCount, size_t pOffset = 0);

	};
}

