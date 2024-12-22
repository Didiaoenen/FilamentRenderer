#include "Core.FRRenderTarget.h"

#include "Core.FRTexture.h"
#include "EAttachmentPoint.h"

#include <FREngineWarp.h>
#include <FRFilamentHelper.h>
#include <FRRenderTargetWarp.h>

FR::FRRenderTarget::FRRenderTarget()
{
}

FR::FRRenderTarget::FRRenderTarget(FRTexture* mColorTexture, FRTexture* mDepthTexture)
{
	auto engine = FRFilamentHelper::GetEngine();
	mRenderTarget = FRRenderTargetWarp::Builder()
		.Texture(EAttachmentPoint::COLOR, mColorTexture->NativePtr())
		.Texture(EAttachmentPoint::DEPTH, mDepthTexture->NativePtr())
		.Build(engine);
}

FR::FRRenderTargetWarp* FR::FRRenderTarget::NativePtr()
{
	return mRenderTarget;
}

FR::FRRenderTarget::~FRRenderTarget()
{
	FRFilamentHelper::GetEngine()->Destroy(mRenderTarget);
	mRenderTarget = nullptr;
}
