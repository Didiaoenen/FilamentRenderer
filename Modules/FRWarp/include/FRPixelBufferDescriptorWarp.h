#pragma once

#include "FRObjWarp.h"
#include <backend/PixelBufferDescriptor.h>

namespace FR
{
	class FRPixelBufferDescriptorWarp
		: public FRObjWarp<filament::backend::PixelBufferDescriptor>
	{
	public:

		using Callback = void(*)(void* pBuffer, size_t pSize, void* pUser);

		FRPixelBufferDescriptorWarp() = default;

		FRPixelBufferDescriptorWarp(void const* pBuffer, size_t pSize, filament::backend::PixelDataFormat pFormat,
			filament::backend::PixelDataType pType, uint8_t pAlignment = 1,
			uint32_t pLeft = 0, uint32_t pTop = 0, uint32_t pStride = 0,
			Callback pCallback = nullptr, void* pUser = nullptr);

	};
}

