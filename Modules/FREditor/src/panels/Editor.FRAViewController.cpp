#include "Editor.FRAViewController.h"
#include "Editor.FRApplication.h"
#include "Editor.FRHierarchy.h"

using namespace FR::GUI;

namespace FR
{
	const glm::vec3 kDefaultCameraPosition{ 0.0f, 0.0f, 10.0f };
	const glm::quat kDefaultCameraRotation = glm::angleAxis(glm::radians(180.f), glm::vec3(0, 1, 0));
}

FR::FRAViewController::FRAViewController(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSetting)
	: FRAPanelView(pTitle, pOpened, pSetting)
{
	ResetCameraTransform();
}

void FR::FRAViewController::Update()
{
	auto hirarchy = FRApplication::GuiHelper()->GetPanel<FRHierarchy>();

	if (IsHovered() || hirarchy->IsHovered())
	{
		mCameraController.HandleInputs();
	}

	FRAPanelView::Update();
}

void FR::FRAViewController::InitRenderTarget(const glm::vec2& pSize)
{
	FRAPanelView::InitRenderTarget(pSize);
}

void FR::FRAViewController::ResetCameraTransform()
{
	mCameraController.SetPosition(kDefaultCameraPosition);
	mCameraController.SetRotation(kDefaultCameraRotation);
}

FR::FRCamera* FR::FRAViewController::GetCamera()
{
	return mCameraController.GetCamera();
}

FR::FRCameraController& FR::FRAViewController::GetCameraController()
{
	return mCameraController;
}
