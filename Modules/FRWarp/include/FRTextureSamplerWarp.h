#pragma once

#include "FRObjWarp.h"
#include <filament/TextureSampler.h>

namespace FR
{
	class FRTextureSamplerWarp
		: public FRObjWarp<filament::TextureSampler>
	{
	public:
		FRTextureSamplerWarp() = default;

		FRTextureSamplerWarp(
			filament::TextureSampler::MinFilter pMin, filament::TextureSampler::MagFilter pMag,
			filament::TextureSampler::WrapMode pStr = filament::TextureSampler::WrapMode::CLAMP_TO_EDGE);

        void SetMinFilter(filament::TextureSampler::MinFilter pFilter);

		void SetMagFilter(filament::TextureSampler::MagFilter pFilter);

		void SetWrapModeS(filament::TextureSampler::WrapMode pMode);

		void SetWrapModeT(filament::TextureSampler::WrapMode pMode);

	};
}

