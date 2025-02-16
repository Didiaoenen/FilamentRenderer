#pragma once

#include <Color.h>
#include "Core.FRCamera.h"
#include "Core.FRComponent.h"

namespace FR
{
	class FRCompCamera
		: public FRComponent
	{
	public:
		FRCompCamera(FRActor& pOwner);

		float GetFov() const;

		float GetSize() const;

		float GetNear() const;

		float GetFar() const;

		const Color& GetClearColor() const;

		void SetFov(float pValue);

		void SetSize(float pValue);

		void SetNear(float pValue);

		void SetFar(float pValue);

		void SetClearColor(const Color& pClearColor);

		void SetProjectionMode(EProjectionMode pProjectionMode);

		EProjectionMode GetProjectionMode() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& pDoc, tinyxml2::XMLNode* pNode) override;

		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) override;

		virtual const std::string GetName() override;

		virtual EComponentType GetType() override;

		FRCamera& GetCamera();

	private:
		void ValueChangeCallback(int, GUI::FRAWidget*, GUI::FRAWidget*, GUI::FRAWidget*, GUI::FRAWidget*);

	private:
		FRCamera mCamera;

	};
}

