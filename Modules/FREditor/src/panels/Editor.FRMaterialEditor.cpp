#include "Editor.FRMaterialEditor.h"

#include "Editor.FRAssetView.h"
#include "Editor.FREditorActions.h"

#include <Core.FRShader.h>
#include <Core.FRMaterialLoader.h>

#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

using namespace FR::GUI;

namespace FR
{
	std::string UniformFormat(const std::string& p_string)
	{
		std::string result;
		std::string formattedInput = p_string;
		std::string capsChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

		bool first = true;
		bool capsNext = false;

		for (char c : formattedInput)
		{
			if (first || capsNext)
			{
				c = toupper(c);
				first = false;
				capsNext = false;
			}

			if (c == '_')
			{
				c = ' ';
				capsNext = true;
			}

			if (std::find(capsChars.begin(), capsChars.end(), c) != capsChars.end())
				result.push_back(' ');

			result.push_back(c);
		}

		return result;
	}

	void DrawHybridVec3(FRWidgetContainer& pRoot, const std::string& pName, glm::vec3& pData, float pStep, float pMin, float pMax)
	{
		FRGuiDrawer::CreateTitle(pRoot, pName).lineBreak = false;

		auto& rightSide = pRoot.CreateWidget<FRGroup>();

		auto& xyzWidget = rightSide.CreateWidget<FRDragMultipleScalars<float, 3>>(FRGuiDrawer::GetDataType<float>(), pMin, pMax, 0.f, pStep, "", FRGuiDrawer::GetFormat<float>());
		auto& xyzDispatcher = xyzWidget.AddPlugin<FRDataDispatcher<std::array<float, 3>>>();
		xyzDispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(pData));
		xyzWidget.sizeType = EWidgetSizeType::ABSOLUTE;
		xyzWidget.position = { 120.f, 0.f };
		xyzWidget.lineBreak = false;
		xyzWidget.enabled = true;
		xyzWidget.size.x = 160.f;

		auto& rgbWidget = rightSide.CreateWidget<FRColorEdit>(false, Color{ pData.x, pData.y, pData.z });
		auto& rgbDispatcher = rgbWidget.AddPlugin<FRDataDispatcher<Color>>();
		rgbDispatcher.RegisterReference(reinterpret_cast<Color&>(pData));
		rgbWidget.sizeType = EWidgetSizeType::ABSOLUTE;
		rgbWidget.position = { 120.f, 0.f };
		rgbWidget.lineBreak = false;
		rgbWidget.enabled = false;
		rgbWidget.size.x = 160.f;

		auto& xyzButton = rightSide.CreateWidget<FRButton>("XYZ");
		xyzButton.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
		xyzButton.enabled = true;

		auto& rgbButton = rightSide.CreateWidget<FRButton>("RGB");
		rgbButton.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
		rgbButton.enabled = false;
	}

	void DrawHybridVec4(FRWidgetContainer& pRoot, const std::string& pName, glm::vec4& pData, float pStep, float pMin, float pMax)
	{
		FRGuiDrawer::CreateTitle(pRoot, pName);

		auto& rightSide = pRoot.CreateWidget<FRGroup>();

		auto& xyzWidget = rightSide.CreateWidget<FRDragMultipleScalars<float, 4>>(FRGuiDrawer::GetDataType<float>(), pMin, pMax, 0.f, pStep, "", FRGuiDrawer::GetFormat<float>());
		auto& xyzDispatcher = xyzWidget.AddPlugin<FRDataDispatcher<std::array<float, 4>>>();
		xyzDispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(pData));
		xyzWidget.lineBreak = false;
		xyzWidget.enabled = true;

		auto& rgbaWidget = rightSide.CreateWidget<FRColorEdit>(true, Color{ pData.x, pData.y, pData.z });
		auto& rgbaDispatcher = rgbaWidget.AddPlugin<FRDataDispatcher<Color>>();
		rgbaDispatcher.RegisterReference(reinterpret_cast<Color&>(pData));
		rgbaWidget.lineBreak = false;
		rgbaWidget.enabled = false;

		auto& xyzwButton = rightSide.CreateWidget<FRButton>("XYZW");
		xyzwButton.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
		xyzwButton.enabled = false;

		auto& rgbaButton = rightSide.CreateWidget<FRButton>("RGBA");
		rgbaButton.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
		rgbaButton.enabled = true;
	}
}

FR::FRMaterialEditor::FRMaterialEditor(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRPanelWindow(pTitle, pOpened, pSettings)
{
	CreateMaterialSelector();

	mSettings = &CreateWidget<FRGroup>();

	CreateShaderSelector();
	CreateMaterialSettings();
	CreateShaderSettings();
	CreateHeaderButtons();

	mSettings->enabled = false;
	mShaderSettings->enabled = false;

	mMaterialDroppedEvent += std::bind(&FRMaterialEditor::OnMaterialDropped, this);
	mShaderDroppedEvent += std::bind(&FRMaterialEditor::OnShaderDropped, this);
}

void FR::FRMaterialEditor::Refresh()
{
	if (mTarget)
	{
		SetTarget(*mTarget);
	}
}

FR::FRMaterial* FR::FRMaterialEditor::GetTarget() const
{
	return mTarget;
}

void FR::FRMaterialEditor::SetTarget(FRMaterial& pNewTarget)
{
	mTarget = &pNewTarget;
	mMaterialText->SetText(mTarget->path);
	OnMaterialDropped();
}

void FR::FRMaterialEditor::OnShaderDropped()
{
	mShaderSettings->enabled = mShader;

	if (mShader != mTarget->GetShader())
	{
		mTarget->SetShader(mShader);
	}

	if (mShaderSettings->enabled)
	{
		GenerateShaderSettingsContent();
	}
	else
	{
		mShaderSettingsColumns->RemoveAllWidgets();
	}
}

void FR::FRMaterialEditor::OnMaterialDropped()
{
	mSettings->enabled = mTarget;

	if (mSettings->enabled)
	{
		GenerateMaterialSettingsContent();
		mShaderText->SetText(mTarget->GetShader() ? mTarget->GetShader()->path : "Empty");
		mShader = mTarget->GetShader();
	}
	else
	{
		mMaterialSettingsColumns->RemoveAllWidgets();
	}

	mShaderSettings->enabled = false;
	mShaderSettingsColumns->RemoveAllWidgets();

	if (mTarget && mTarget->GetShader())
	{
		OnShaderDropped();
	}
}

void FR::FRMaterialEditor::CreateShaderSelector()
{
	mShaderText = &FRGuiDrawer::DrawShader(*mSettings, "Shader", mShader, &mShaderDroppedEvent);
}

void FR::FRMaterialEditor::CreateMaterialSelector()
{
	mMaterialText = &FRGuiDrawer::DrawMaterial(*this, "Material", mTarget, &mMaterialDroppedEvent);
}

void FR::FRMaterialEditor::CreateShaderSettings()
{
	mShaderSettings = &mSettings->CreateWidget<FRGroupCollapsable>("Shader Settings");
	mShaderSettingsColumns = &mShaderSettings->CreateWidget<FRColumns<2>>();
	mShaderSettingsColumns->widths[0] = 120;
}

void FR::FRMaterialEditor::CreateMaterialSettings()
{
	mMaterialSettings = &mSettings->CreateWidget<FRGroupCollapsable>("Material Settings");
	mMaterialSettingsColumns = &mMaterialSettings->CreateWidget<FRColumns<2>>();
	mMaterialSettingsColumns->widths[0] = 120;
}

void FR::FRMaterialEditor::CreateHeaderButtons()
{
	auto& saveButton = CreateWidget<FRButton>("Save");
	{
		saveButton.sizeType = EWidgetSizeType::RELATIVE;
		saveButton.idleBackgroundColor = { 0.0f, 0.5f, 0.0f };

		saveButton.ClickedEvent += [this]
			{
				if (mTarget)
				{
					FRMaterialLoader::Save(*mTarget, FRPathUtils::GetRealPath(mTarget->path));
				}
			};
	}
}

void FR::FRMaterialEditor::GenerateShaderSettingsContent()
{
	mShaderSettingsColumns->RemoveAllWidgets();

	for (auto& prop : mTarget->GetPropInfos())
	{
		if (!prop.sampler)
		{
			switch (prop.uniformType)
			{
			case FR::EUniformType::BOOL:
				FRGuiDrawer::DrawBoolean(*mShaderSettingsColumns, prop.name, reinterpret_cast<bool&>(prop.data));
				break;
			case FR::EUniformType::INT:
				FRGuiDrawer::DrawScalar<int>(*mShaderSettingsColumns, prop.name, reinterpret_cast<int&>(prop.data));
				break;
			case FR::EUniformType::FLOAT:
				FRGuiDrawer::DrawScalar<float>(*mShaderSettingsColumns, prop.name, reinterpret_cast<float&>(prop.data), 0.01f, FRGuiDrawer::_MIN_FLOAT, FRGuiDrawer::_MAX_FLOAT);
				break;
			case FR::EUniformType::FLOAT2:
				FRGuiDrawer::DrawVec2(*mShaderSettingsColumns, prop.name, reinterpret_cast<glm::vec2&>(prop.data), 0.01f, FRGuiDrawer::_MIN_FLOAT, FRGuiDrawer::_MAX_FLOAT);
				break;
			case FR::EUniformType::FLOAT3:
				DrawHybridVec3(*mShaderSettingsColumns, prop.name, reinterpret_cast<glm::vec3&>(prop.data), 0.01f, FRGuiDrawer::_MIN_FLOAT, FRGuiDrawer::_MAX_FLOAT);
				break;
			case FR::EUniformType::FLOAT4:
				DrawHybridVec4(*mShaderSettingsColumns, prop.name, reinterpret_cast<glm::vec4&>(prop.data), 0.01f, FRGuiDrawer::_MIN_FLOAT, FRGuiDrawer::_MAX_FLOAT);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (prop.samplerType)
			{
			case FR::ESamplerType::SAMPLER_2D:
				FRGuiDrawer::DrawTexture(*mShaderSettingsColumns, prop.name, reinterpret_cast<FRTexture*&>(prop.data));
				break;
			default:
				break;
			}
		}
	}
}

void FR::FRMaterialEditor::GenerateMaterialSettingsContent()
{
	mMaterialSettingsColumns->RemoveAllWidgets();
}
