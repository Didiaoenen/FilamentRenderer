#include "FRTextureSamplerWarp.h"

FR::FRTextureSamplerWarp::FRTextureSamplerWarp(filament::TextureSampler::MinFilter pMin, filament::TextureSampler::MagFilter pMag, filament::TextureSampler::WrapMode pStr)
	: FRObjWarp(pMin, pMag, pStr)
{
}

void FR::FRTextureSamplerWarp::SetMinFilter(filament::TextureSampler::MinFilter pFilter)
{
	PtrValue(this).setMinFilter(pFilter);
}

void FR::FRTextureSamplerWarp::SetMagFilter(filament::TextureSampler::MagFilter pFilter)
{
	PtrValue(this).setMagFilter(pFilter);
}

void FR::FRTextureSamplerWarp::SetWrapModeS(filament::TextureSampler::WrapMode pMode)
{
	PtrValue(this).setWrapModeS(pMode);
}

void FR::FRTextureSamplerWarp::SetWrapModeT(filament::TextureSampler::WrapMode pMode)
{
	PtrValue(this).setWrapModeT(pMode);
}
