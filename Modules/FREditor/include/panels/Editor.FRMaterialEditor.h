#pragma once

#include <any>
#include <map>
#include <Core.FRGuiDrawer.h>
#include <GUI.FRPanelWindow.h>

namespace FR
{
	class FRShader;
	class FRMaterial;

	class FRMaterialEditor
		: public GUI::FRPanelWindow
	{
	public:
		FRMaterialEditor(const std::string& pTitle, bool pOpened, const GUI::FRPanelWindowSettings& pSettings);

		void Refresh();

		FRMaterial* GetTarget() const;
		
		void SetTarget(FRMaterial* pNewTarget);

	private:
		void OnShaderDropped();

		void OnMaterialDropped();

		void CreateShaderSelector();

		void CreateMaterialSelector();

		void CreateShaderSettings();

		void CreateMaterialSettings();

		void CreateHeaderButtons();

		void GenerateShaderSettingsContent();

		void GenerateMaterialSettingsContent();

	private:
		GUI::FRItemSelect* mShaderText{ nullptr };
		GUI::FRItemSelect* mMaterialText{ nullptr };

		GUI::FRGroup* mSettings{ nullptr };
		GUI::FRGroup* mShaderSettings{ nullptr };
		GUI::FRGroup* mMaterialSettings{ nullptr };

		GUI::FRColumns<2>* mShaderSettingsColumns{ nullptr };
		GUI::FRColumns<2>* mMaterialSettingsColumns{ nullptr };

		FRShader* mShader{ nullptr };
		FRMaterial* mTarget{ nullptr };

		FREvent<> mShaderDroppedEvent;
		FREvent<> mMaterialDroppedEvent;

	};
}

