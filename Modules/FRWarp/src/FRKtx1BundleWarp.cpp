#include "FRKtx1BundleWarp.h"

FR::FRKtx1BundleWarp::FRKtx1BundleWarp(uint8_t const* pData, uint32_t pCount)
{
	mValue = FRPtrValue(new image::Ktx1Bundle(pData, pCount));
}

FR::FRKtx1BundleWarp::~FRKtx1BundleWarp()
{
}