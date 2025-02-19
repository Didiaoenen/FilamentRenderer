#include "Core.FRCompLight.h"
#include "Core.FRActor.h"
#include "Core.FRSerializer.h"
#include "Core.FRCompTransform.h"

FR::FRCompLight::FRCompLight(FRActor& pOwner)
	: FRComponent(pOwner)
	, mLight(pOwner.GetEntity(), pOwner.GetTransform())
{
	lightType = FRLightManagerWarp::EType::DIRECTIONAL;
	mLight.CreateLight(lightType);

	owner.GetScene()->AddLight(&mLight);
}

const FR::Color& FR::FRCompLight::GetColor() const
{
	return mLight.color;
}

float FR::FRCompLight::GetIntensity() const
{
	return mLight.intensity;
}

void FR::FRCompLight::SetColor(const Color& pColor)
{
	mLight.color = pColor;
}

void FR::FRCompLight::SetIntensity(float pIntensity)
{
	mLight.intensity = pIntensity;
}

void FR::FRCompLight::OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{

}

void FR::FRCompLight::OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode)
{

}

void FR::FRCompLight::OnInspector(FRWidgetContainer& pRoot)
{
	FRGuiDrawer::DrawColor(pRoot, "Color", mLight.color);
	FRGuiDrawer::DrawScalar(pRoot, "Intensity", mLight.intensity, 10.f);

	auto& widgetInner = FRGuiDrawer::DrawScalar(pRoot, "Inner", mLight.inner, 0.1f);
	auto& innerWidget = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 1].first;
	auto& innerWidgetLabel = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 2].first;
	innerWidget.enabled = innerWidgetLabel.enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT;

	auto& widgetOuter = FRGuiDrawer::DrawScalar(pRoot, "Outer", mLight.outer, 0.1f);
	auto& outerWidget = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 1].first;
	auto& outerWidgetLabel = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 2].first;
	outerWidget.enabled = outerWidgetLabel.enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT;

	auto& widgetFalloff = FRGuiDrawer::DrawScalar(pRoot, "Falloff", mLight.falloff, 0.1f);
	auto& falloffWidget = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 1].first;
	auto& falloffWidgetLabel = *pRoot.GetWidgets()[pRoot.GetWidgets().size() - 2].first;
	falloffWidget.enabled = falloffWidgetLabel.enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT || lightType == FRLightManagerWarp::EType::POINT;

	auto& lightTypeWidget = FRGuiDrawer::DrawComboBox(pRoot, "Light Type", static_cast<int>(lightType),
		{ "SUN", "DIRECTIONAL", "POINT", "FOCUSED_SPOT", "SPOT" }, this, &FRCompLight::ValueChangeCallback, &innerWidget, &innerWidgetLabel, &outerWidget, &outerWidgetLabel, &falloffWidget, &falloffWidgetLabel);

	FRGuiDrawer::DrawBoolean(pRoot, "Shadow Caster", mLight.shadowCaster).alignment = EWidgetAlignment::RIGHT;
}

const std::string FR::FRCompLight::GetName()
{
	return ICON_MDI_LIGHTBULB " Light";
}

FR::FRComponent::EComponentType FR::FRCompLight::GetType()
{
	return FRComponent::EComponentType::LIGHT;
}

FR::FRLight& FR::FRCompLight::GetLight()
{
	return mLight;
}

void FR::FRCompLight::ValueChangeCallback(int pChoice, FRAWidget* pInner, FRAWidget* pInnerLabel, FRAWidget* pOuter, FRAWidget* pOuterLabel, FRAWidget* pFalloff, FRAWidget* pFalloffLabel)
{
	if (auto tempType = static_cast<FRLightManagerWarp::EType>(pChoice); tempType != lightType)
	{
		lightType = tempType;
		mLight.CreateLight(lightType);
		pInner->enabled = pInnerLabel->enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT;
		pOuter->enabled = pOuterLabel->enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT;
		pFalloff->enabled = pFalloffLabel->enabled = lightType == FRLightManagerWarp::EType::SPOT || lightType == FRLightManagerWarp::EType::FOCUSED_SPOT || lightType == FRLightManagerWarp::EType::POINT;
	}
}

FR::FRCompLight::~FRCompLight()
{
	FRFilamentHelper::GetLightManager()->Destroy(owner.GetEntity());
}
