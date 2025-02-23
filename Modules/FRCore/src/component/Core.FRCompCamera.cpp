#include "Core.FRCompCamera.h"
#include "Core.FRActor.h"
#include "Core.FRCompTransform.h"

FR::FRCompCamera::FRCompCamera(FRActor& pOwner)
	: FRComponent(pOwner)
	, mCamera(&pOwner)
{
	mCamera.clearColor = { 0.1921569f, 0.3019608f, 0.4745098f };
}

const std::string FR::FRCompCamera::GetName()
{
	return ICON_MDI_CAMERA " Camera";
}

FR::FRComponent::EComponentType FR::FRCompCamera::GetType()
{
	return FRComponent::EComponentType::CAMERA;
}

void FR::FRCompCamera::SetFov(float pValue)
{
	mCamera.fov = pValue;
}

void FR::FRCompCamera::SetSize(float pValue)
{
	mCamera.size = pValue;
}

void FR::FRCompCamera::SetNear(float pValue)
{
	mCamera.near = pValue;
}

void FR::FRCompCamera::SetFar(float pValue)
{
	mCamera.far = pValue;
}

void FR::FRCompCamera::SetClearColor(const Color& pClearColor)
{
	mCamera.clearColor = pClearColor;
}

void FR::FRCompCamera::SetProjectionMode(FRCamera::EProjectionMode pProjectionMode)
{
	mCamera.projectionMode = pProjectionMode;
}

float FR::FRCompCamera::GetFov() const
{
	return mCamera.fov;
}

float FR::FRCompCamera::GetSize() const
{
	return mCamera.size;
}

float FR::FRCompCamera::GetNear() const
{
	return mCamera.near;
}

float FR::FRCompCamera::GetFar() const
{
	return mCamera.far;
}

const FR::Color& FR::FRCompCamera::GetClearColor() const
{
	return mCamera.clearColor;
}

FR::FRCamera::EProjectionMode FR::FRCompCamera::GetProjectionMode() const
{
	return mCamera.projectionMode;
}

FR::FRCamera& FR::FRCompCamera::GetCamera()
{
	return mCamera;
}

void FR::FRCompCamera::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompCamera::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{
}

void FR::FRCompCamera::OnInspector(FRWidgetContainer& pRoot)
{
	auto& widgetFov = FRGuiDrawer::DrawScalar<float>(pRoot, "Field Of View", std::bind(&FRCompCamera::GetFov, this), std::bind(&FRCompCamera::SetFov, this, std::placeholders::_1));
	auto& fovWidget = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 1].first;
	auto& fovWidgetLabel = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 2].first;
	fovWidget.enabled = fovWidgetLabel.enabled = mCamera.projectionMode == FRCamera::EProjectionMode::PERSPECTIVE;

	auto& widgetSize = FRGuiDrawer::DrawScalar<float>(pRoot, "Size", std::bind(&FRCompCamera::GetSize, this), std::bind(&FRCompCamera::SetSize, this, std::placeholders::_1));
	auto& sizeWidget = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 1].first;
	auto& sizeWidgetLabel = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 2].first;
	sizeWidget.enabled = sizeWidgetLabel.enabled = mCamera.projectionMode == FRCamera::EProjectionMode::ORTHOGRAPHIC;

	FRGuiDrawer::DrawScalar<float>(pRoot, "Near", std::bind(&FRCompCamera::GetNear, this), std::bind(&FRCompCamera::SetNear, this, std::placeholders::_1));
	
	FRGuiDrawer::DrawScalar<float>(pRoot, "Far", std::bind(&FRCompCamera::GetFar, this), std::bind(&FRCompCamera::SetFar, this, std::placeholders::_1));
	
	FRGuiDrawer::DrawColor(pRoot, "Clear Color", [this]() { return GetClearColor(); }, [this](Color pColor) { SetClearColor(pColor); });

	FRGuiDrawer::DrawComboBox(pRoot, "Projection Mode", static_cast<int>(mCamera.projectionMode),
		{"ORTHOGRAPHIC", "PERSPECTIVE"}, this, &FRCompCamera::ValueChangeCallback, &fovWidget, &fovWidgetLabel, &sizeWidget, &sizeWidgetLabel);
}

void FR::FRCompCamera::ValueChangeCallback(int pChoice, FRAWidget* pFov, FRAWidget* pFovLabel, FRAWidget* pSize, FRAWidget* pSizeLabel)
{
	auto newProjectionMode = static_cast<FRCamera::EProjectionMode>(pChoice);
	pFov->enabled = pFovLabel->enabled = newProjectionMode == FRCamera::EProjectionMode::PERSPECTIVE;
	pSize->enabled = pSizeLabel->enabled = newProjectionMode == FRCamera::EProjectionMode::ORTHOGRAPHIC;
	SetProjectionMode(newProjectionMode);
}

FR::FRCompCamera::~FRCompCamera()
{
	FRFilamentHelper::GetEngine()->DestroyCamera(owner.NatrivePtr());
	FRFilamentHelper::GetEngine()->UnRegisterCamera(mCamera.NativePtr());
}
