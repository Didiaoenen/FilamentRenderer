#include "FRIndexBufferWarp.h"
#include "FREngineWarp.h"
#include "FRBufferDescriptorWarp.h"

FR::FRIndexBufferWarp::FRIndexBufferWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
	pEngine->RegisterIndexBuffer(this);
}

void FR::FRIndexBufferWarp::SetBuffer(FREngineWarp* pEngine, FRBufferDescriptorWarp&& pBuffer, uint32_t pByteOffset)
{
	PtrValue(this)->setBuffer(*PtrValue(pEngine), FRBufferDescriptor(std::move(RefValue(pBuffer))), pByteOffset);
}

size_t FR::FRIndexBufferWarp::GetIndexCount()
{
	return mValue->getIndexCount();
}
