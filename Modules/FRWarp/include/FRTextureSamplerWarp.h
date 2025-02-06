#pragma once

#include "FRObjWarp.h"
#include <filament/TextureSampler.h>

namespace FR
{
	class FRTextureSamplerWarp
		: public FRObjWarp<filament::TextureSampler>
	{
	public:
		using EWrapMode = filament::TextureSampler::WrapMode;

		using EMagFilter = filament::TextureSampler::MagFilter;

		using EMinFilter = filament::TextureSampler::MinFilter;

		FRTextureSamplerWarp() = default;

		FRTextureSamplerWarp(EMinFilter pMin, EMagFilter pMag, EWrapMode pStr = EWrapMode::CLAMP_TO_EDGE);

        void SetMinFilter(EMinFilter pFilter);

		void SetMagFilter(EMagFilter pFilter);

		void SetWrapModeS(EWrapMode pMode);

		void SetWrapModeT(EWrapMode pMode);

	};
}

