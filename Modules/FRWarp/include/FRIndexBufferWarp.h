#pragma once

#include "FRPtrWarp.h"
#include <filament/IndexBuffer.h>

namespace FR
{
	class FREngineWarp;
	class FRBufferDescriptorWarp;

	class FRIndexBufferWarp
		: public FRPtrWarp<filament::IndexBuffer>
	{
	public:
		class Builder
		{
			friend class FRIndexBufferWarp;

		public:
			Builder()
				: mBuilder()
			{
			}

			Builder& IndexCount(uint32_t pIndexCount)
			{
				mBuilder.indexCount(pIndexCount);
				return *this;
			}

			Builder& BufferType(filament::IndexBuffer::IndexType pIndexType)
			{
				mBuilder.bufferType(pIndexType);
				return *this;
			}

			FRIndexBufferWarp* Build(FREngineWarp* pEngine)
			{
				return new FRIndexBufferWarp(pEngine, this);
			}

		private:
			filament::IndexBuffer::Builder mBuilder;
		};

		FRIndexBufferWarp(FREngineWarp* pEngine, Builder* pBuilder);

		void SetBuffer(FREngineWarp* pEngine, FRBufferDescriptorWarp&& pBuffer, uint32_t pByteOffset = 0);
		
		size_t GetIndexCount();
	};
}

