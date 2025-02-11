#pragma once

#include "Core.FRLight.h"
#include "Core.FRComponent.h"

namespace FR
{
	class FRActor;

	class FRCompLight
		: public FRComponent
	{
	public:
		FRCompLight(FRActor& pOwner);

		const Color& GetColor() const;

		float GetIntensity() const;

		void SetColor(const Color& pColor);

		void SetIntensity(float pIntensity);

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName();

		virtual EComponentType GetType();

		FRLight& GetLight();

	private:
		void ValueChangeCallback(int pChoice, FRAWidget* pInner, FRAWidget* pInnerLabel, FRAWidget* pOuter, FRAWidget* pOuterLabel, FRAWidget* pFalloff, FRAWidget* pFalloffLabel);

	public:
		FRLightManagerWarp::EType lightType;

	protected:
		FRLight mLight;

	};
}

