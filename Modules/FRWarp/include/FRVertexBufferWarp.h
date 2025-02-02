#pragma once

#include "FRPtrWarp.h"
#include <filament/VertexBuffer.h>

namespace FR
{
	class FREngineWarp;
	class FRBufferDescriptorWarp;

	class FRVertexBufferWarp
		: public FRPtrWarp<filament::VertexBuffer>
	{
	public:

		class Builder
		{
			friend class FRVertexBufferWarp;

		public:
			Builder()
				: mBuilder()
			{

			}

			Builder& VertexCount(uint32_t pVertexCount)
			{
				mBuilder.vertexCount(pVertexCount);
				return *this;
			}

			Builder& BufferCount(uint8_t pBufferCount)
			{
				mBuilder.bufferCount(pBufferCount);
				return *this;
			}

			Builder& Attribute(
				filament::VertexAttribute pAttribute, uint8_t pBufferIndex,
				filament::VertexBuffer::AttributeType pAttributeType, uint32_t pByteOffset = 0, uint8_t pByteStride = 0)
			{
				mBuilder.attribute(pAttribute, pBufferIndex, pAttributeType, pByteOffset, pByteStride);
				return *this;
			}

			Builder& Normalized(filament::VertexAttribute pAttribute, bool pNormalize = true)
			{
				mBuilder.normalized(pAttribute, pNormalize);
				return *this;
			}

			FRVertexBufferWarp* Build(FREngineWarp* pEngine)
			{
				return new FRVertexBufferWarp(pEngine, this);
			}

		private:
			filament::VertexBuffer::Builder mBuilder;
		};

		FRVertexBufferWarp() = default;

		FRVertexBufferWarp(FREngineWarp* pEngine, Builder* pBuilder);

		void SetBufferAt(FREngineWarp* pEngine, uint8_t pBufferIndex, FRBufferDescriptorWarp&& pBuffer, uint32_t pByteOffset = 0);

		size_t GetVertexCount();

	};
}

