#include "FRPixelBufferDescriptorWarp.h"

FR::FRPixelBufferDescriptorWarp::FRPixelBufferDescriptorWarp(void const* pBuffer, size_t pSize, EPixelDataFormat pFormat,
	EPixelDataType pType, uint8_t pAlignment, uint32_t pLeft, uint32_t pTop, uint32_t pStride, Callback pCallback, void* pUser)
	: FRObjWarp(pBuffer, pSize, pFormat, pType, pAlignment, pLeft, pTop, pStride, pCallback, pUser)
{
}
