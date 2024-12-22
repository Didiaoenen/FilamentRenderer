#include "FRBufferDescriptorWarp.h"

FR::FRBufferDescriptorWarp::FRBufferDescriptorWarp(void const* pBuffer, size_t pSize, Callback pCallback, void* pUser)
	: FRObjWarp(pBuffer, pSize, pCallback, pUser)
{
}
