#pragma once

#include "FRObjWarp.h"
#include <backend/BufferDescriptor.h>

namespace FR
{
	class FRBufferDescriptorWarp
		: public FRObjWarp<filament::backend::BufferDescriptor>
	{
	public:
		using Callback = filament::backend::BufferDescriptor::Callback;

	public:
		FRBufferDescriptorWarp() = default;

		FRBufferDescriptorWarp(void const* pBuffer, size_t pSize, Callback pCallback = nullptr, void* pUser = nullptr);

	};
}

