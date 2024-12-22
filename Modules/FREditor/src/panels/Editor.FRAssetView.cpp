#include "Editor.FRAssetView.h"

#include <Core.FRShader.h>

using namespace FR::GUI;

FR::FRAssetView::FRAssetView(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRAViewController(pTitle, pOpened, pSettings)
{

}

FR::FRScene* FR::FRAssetView::GetScene()
{
	return &mScene;
}

void FR::FRAssetView::SetResource(ViewableResource pResource)
{

}

void FR::FRAssetView::ClearResource()
{

}

void FR::FRAssetView::SetTexture(FRTexture& pTexture)
{

}

void FR::FRAssetView::SetModel(FRModel& pModel)
{

}

void FR::FRAssetView::SetMaterial(FRMaterial& pMaterial)
{

}

const FR::FRAssetView::ViewableResource& FR::FRAssetView::GetResource() const
{
	return mResource;
}
