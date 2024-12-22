#include "FRIndexBufferWarp.h"
#include "FREngineWarp.h"
#include "FRBufferDescriptorWarp.h"

FR::FRIndexBufferWarp::FRIndexBufferWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}

size_t FR::FRIndexBufferWarp::GetIndexCount()
{
	return mValue->getIndexCount();
}

void FR::FRIndexBufferWarp::SetBuffer(FREngineWarp* pEngine, FRBufferDescriptorWarp&& pBuffer, uint32_t pByteOffset)
{
	PtrValue(this)->setBuffer(*PtrValue(pEngine), filament::backend::BufferDescriptor(std::move(RefValue(pBuffer))), pByteOffset);
}
