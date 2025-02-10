#include "FRTextureSamplerWarp.h"

FR::FRTextureSamplerWarp::FRTextureSamplerWarp(EMinFilter pMin, EMagFilter pMag, EWrapMode pStr)
	: FRObjWarp(pMin, pMag, pStr)
{
}

void FR::FRTextureSamplerWarp::SetMinFilter(EMinFilter pFilter)
{
	PtrValue(this).setMinFilter(pFilter);
}

void FR::FRTextureSamplerWarp::SetMagFilter(EMagFilter pFilter)
{
	PtrValue(this).setMagFilter(pFilter);
}

void FR::FRTextureSamplerWarp::SetWrapModeS(EWrapMode pMode)
{
	PtrValue(this).setWrapModeS(pMode);
}

void FR::FRTextureSamplerWarp::SetWrapModeT(EWrapMode pMode)
{
	PtrValue(this).setWrapModeT(pMode);
}

void FR::FRTextureSamplerWarp::SetWrapModeR(EWrapMode pMode)
{
	PtrValue(this).setWrapModeR(pMode);
}
