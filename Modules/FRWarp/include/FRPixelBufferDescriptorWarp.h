#pragma once

#include "FRObjWarp.h"
#include <backend/PixelBufferDescriptor.h>

namespace FR
{
	class FRPixelBufferDescriptorWarp
		: public FRObjWarp<filament::backend::PixelBufferDescriptor>
	{
	public:
		using EPixelDataType = filament::backend::PixelDataType;

		using EPixelDataFormat = filament::backend::PixelDataFormat;

		using Callback = filament::backend::BufferDescriptor::Callback;

	public:
		FRPixelBufferDescriptorWarp() = default;

		FRPixelBufferDescriptorWarp(void const* pBuffer, size_t pSize, EPixelDataFormat pFormat, EPixelDataType pType,
			uint8_t pAlignment = 1, uint32_t pLeft = 0, uint32_t pTop = 0, uint32_t pStride = 0,
			Callback pCallback = nullptr, void* pUser = nullptr);

	};
}

