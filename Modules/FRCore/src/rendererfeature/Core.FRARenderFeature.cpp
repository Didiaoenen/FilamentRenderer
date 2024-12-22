#include "Core.FRARenderFeature.h"

FR::ARenderFeature::ARenderFeature(FRCompositeRenderer& pRenderer)
	: mRenderer(pRenderer)
{
}

void FR::ARenderFeature::SetEnabled(bool pEnabled)
{
	mEnabled = pEnabled;
}

bool FR::ARenderFeature::IsEnabled() const
{
	return mEnabled;
}

void FR::ARenderFeature::OnBeginFrame()
{
}

void FR::ARenderFeature::OnEndFrame()
{
}

void FR::ARenderFeature::OnBeforeDraw(const FRDrawable& pDrawable)
{
}

void FR::ARenderFeature::OnAfterDraw(const FRDrawable& pDrawable)
{
}
