#include "FRVertexBufferWarp.h"
#include "FREngineWarp.h"
#include "FRBufferDescriptorWarp.h"

FR::FRVertexBufferWarp::FRVertexBufferWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}

void FR::FRVertexBufferWarp::SetBufferAt(FREngineWarp* pEngine, uint8_t pBufferIndex, FRBufferDescriptorWarp&& pBuffer, uint32_t pByteOffset)
{
	PtrValue(this)->setBufferAt(*PtrValue(pEngine), pBufferIndex, filament::backend::BufferDescriptor(std::move(RefValue(pBuffer))), pByteOffset);
}

size_t FR::FRVertexBufferWarp::GetVertexCount()
{
	return PtrValue(this)->getVertexCount();
}
