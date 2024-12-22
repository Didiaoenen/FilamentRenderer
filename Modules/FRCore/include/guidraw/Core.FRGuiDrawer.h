#pragma once

#include <string>
#include <imgui.h>
#include <glm/glm.hpp>

#include <GUI.FRMenu.h>
#include <GUI.FRText.h>
#include <GUI.FRImage.h>
#include <GUI.FRPopup.h>
#include <GUI.FRButton.h>
#include <GUI.FRLayout.h>
#include <GUI.FRCheckBox.h>
#include <GUI.FRFileItem.h>
#include <GUI.FRComboBox.h>
#include <GUI.FRSeparator.h>
#include <GUI.FRColorEdit.h>
#include <GUI.FRInputText.h>
#include <GUI.FRTableView.h>
#include <GUI.FRItemSelect.h>
#include <GUI.FRDragScalar.h>
#include <GUI.FRDataDispatcher.h>
#include <GUI.FRWidgetContainer.h>
#include <GUI.FRSliderSingleScalar.h>
#include <GUI.FRSliderMultipleScalars.h>
#include <GUI.FRContextualMenu.h>
#include <GUI.FRPluginTarget.h>
#include <GUI.FRPluginSource.h>

#include <Color.h>
#include <Tools.FREvent.h>

namespace FR
{
	class FRModel;
	class FRShader;
	class FRTexture;
	class FRMaterial;
	class Animation;

	class FRGuiDrawer
	{
	public:
		template <typename T>
		static std::string GetFormat();

		template <typename T>
		static ImGuiDataType_ GetDataType();

		template <typename T>
		static GUI::FRAWidget& DrawSlider(GUI::FRWidgetContainer& pRoot, const std::string& pName, T& pData, T pMin = std::numeric_limits<T>::min(), T pMax = std::numeric_limits<T>::max());
		
		template <typename T>
		static GUI::FRAWidget& DrawSlider(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<T(void)> pGatherer, std::function<void(T)> pProvider, T pMin = std::numeric_limits<T>::min(), T pMax = std::numeric_limits<T>::max());
		
		template <typename T>
		static GUI::FRAWidget& DrawScalar(GUI::FRWidgetContainer& pRoot, const std::string& pName, T& pData, float pStep = 1.f, T pMin = std::numeric_limits<T>::min(), T pMax = std::numeric_limits<T>::max());

		template <typename T>
		static GUI::FRAWidget& DrawScalar(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<T(void)> pGatherer, std::function<void(T)> pProvider, float pStep = 1.f, T pMin = std::numeric_limits<T>::min(), T pMax = std::numeric_limits<T>::max());

		template <typename T, typename ...TArgs>
		static GUI::FRAWidget& DrawComboBox(GUI::FRWidgetContainer& pRoot, const std::string& pName, int pIndex, std::vector<std::string> pChoices, T* pObject, void(T::* pCallback)(TArgs...), auto... pArgs);

		template <typename T, typename ...TArgs>
		static GUI::FRAWidget& DrawItemSelect(GUI::FRWidgetContainer& pRoot, const std::string& pName, GUI::FRItemSelect::EItemType pType, T* pObject, void(T::* pCallback)(TArgs...), auto... pArgs);

		static GUI::FRAWidget& DrawBoolean(GUI::FRWidgetContainer& pRoot, const std::string& pName, bool& pData);
		static GUI::FRAWidget& DrawBoolean(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<bool(void)> pGatherer, std::function<void(bool)> pProvider);

		static GUI::FRAWidget& DrawString(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::string& pData);
		static GUI::FRAWidget& DrawString(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<std::string(void)> pGatherer, std::function<void(std::string)> pProvider);

		static GUI::FRAWidget& DrawVec2(GUI::FRWidgetContainer& pRoot, const std::string& pName, glm::vec2& pData, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);
		static GUI::FRAWidget& DrawVec2(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec2(void)> pGatherer, std::function<void(glm::vec2)> pProvider, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);

		static GUI::FRAWidget& DrawVec3(GUI::FRWidgetContainer& pRoot, const std::string& pName, glm::vec3& pData, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);
		static GUI::FRAWidget& DrawVec3(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec3(void)> pGatherer, std::function<void(glm::vec3)> pProvider, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);

		static GUI::FRAWidget& DrawVec4(GUI::FRWidgetContainer& pRoot, const std::string& pName, glm::vec4& pData, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);
		static GUI::FRAWidget& DrawVec4(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec4(void)> pGatherer, std::function<void(glm::vec4)> pProvider, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);

		static GUI::FRAWidget& DrawQuat(GUI::FRWidgetContainer& pRoot, const std::string& pName, glm::quat& pData, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);
		static GUI::FRAWidget& DrawQuat(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::quat(void)> pGatherer, std::function<void(glm::quat)> pProvider, float pStep = 1.f, float pMin = _MIN_FLOAT, float pMax = _MAX_FLOAT);

		static GUI::FRAWidget& DrawColor(GUI::FRWidgetContainer& pRoot, const std::string& pName, Color& pColor, bool pHasAlpha = false);
		static GUI::FRAWidget& DrawColor(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<Color(void)> pGatherer, std::function<void(Color)> pProvider, bool pHasAlpha = false);

		static GUI::FRAWidget& DrawDDString(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<std::string(void)> pGatherer, std::function<void(std::string)> pProvider, const std::string& pIdentifier);

		static GUI::FRItemSelect& DrawMesh(GUI::FRWidgetContainer& pRoot, const std::string& pName, FRModel*& pData, FREvent<>* pUpdateNotifier = nullptr);
		static GUI::FRItemSelect& DrawShader(GUI::FRWidgetContainer& pRoot, const std::string& pName, FRShader*& pData, FREvent<>* pUpdateNotifier = nullptr);
		static GUI::FRItemSelect& DrawMaterial(GUI::FRWidgetContainer& pRoot, const std::string& pName, FRMaterial*& pData, FREvent<>* pUpdateNotifier = nullptr);
		static GUI::FRImage& DrawTexture(GUI::FRWidgetContainer& pRoot, const std::string& pName, FRTexture*& pData, FREvent<>* pUpdateNotifier = nullptr);
		
		static GUI::FRText& DrawAsset(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::string& pData, FREvent<>* pUpdateNotifier = nullptr);
		
		static GUI::FRAWidget& CreateTitle(GUI::FRWidgetContainer& pRoot, const std::string& pName);
		
		static void DrawSpace(GUI::FRWidgetContainer& pRoot, int pSpace);

		static void ProvideEmptyTexture(FRTexture* pEmptyTexture);

		static FRTexture* GetEmptyTexture();

	public:
		static const Color TitleColor;
		static const Color ClearButtonColor;

		static const float _MIN_FLOAT;
		static const float _MAX_FLOAT;

	private:
		static FRTexture* __EMPTY_TEXTURE;

	};
}

#include "Core.FRGuiDrawer.inl"