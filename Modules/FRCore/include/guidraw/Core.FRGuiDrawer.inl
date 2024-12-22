#pragma once

#include "Core.FRGuiDrawer.h"

using namespace FR::GUI;

template<typename T>
std::string FR::FRGuiDrawer::GetFormat()
{
	if constexpr (std::is_same<T, double>::value)
		return "%.2f";
	else if constexpr (std::is_same<T, float>::value)
		return "%.2f";
	else
		return "%d";
}

template<typename T>
ImGuiDataType_ FR::FRGuiDrawer::GetDataType()
{
	if constexpr (std::is_same<T, float>::value)
		return ImGuiDataType_Float;
	else if constexpr (std::is_same<T, double>::value)
		return ImGuiDataType_Double;
	else if constexpr (std::is_same<T, uint8_t>::value)
		return ImGuiDataType_U8;
	else if constexpr (std::is_same<T, uint16_t>::value)
		return ImGuiDataType_U16;
	else if constexpr (std::is_same<T, uint32_t>::value)
		return ImGuiDataType_U32;
	else if constexpr (std::is_same<T, uint64_t>::value)
		return ImGuiDataType_U64;
	else if constexpr (std::is_same<T, int8_t>::value)
		return ImGuiDataType_S8;
	else if constexpr (std::is_same<T, int16_t>::value)
		return ImGuiDataType_S16;
	else if constexpr (std::is_same<T, int32_t>::value)
		return ImGuiDataType_S32;
	else if constexpr (std::is_same<T, int64_t>::value)
		return ImGuiDataType_S64;
}

template<typename T>
inline FRAWidget& FR::FRGuiDrawer::DrawSlider(FRWidgetContainer& pRoot, const std::string& pName, T& pData, T pMin, T pMax)
{
	static_assert(std::is_scalar<T>::value, "T must be a scalar");
	
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRSliderSingleScalar<T>>(GetDataType<T>(), pMin, pMax, pData, ESliderOrientation::HORIZONTAL, "", GetFormat<T>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<T>>();
	dispatcher.RegisterReference(pData);
	return widget;
}

template<typename T>
inline FRAWidget& FR::FRGuiDrawer::DrawSlider(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<T(void)> pGatherer, std::function<void(T)> pProvider, T pMin, T pMax)
{
	static_assert(std::is_scalar<T>::value, "T must be a scalar");

	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRSliderSingleScalar<T>>(GetDataType<T>(), pMin, pMax, static_cast<T>(0), ESliderOrientation::HORIZONTAL, "", GetFormat<T>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<T>>();
	dispatcher.RegisterGatherer(pGatherer);
	dispatcher.RegisterProvider(pProvider);
	return widget;
}

template<typename T>
inline FRAWidget& FR::FRGuiDrawer::DrawScalar(GUI::FRWidgetContainer& pRoot, const std::string& pName, T& pData, float pStep, T pMin, T pMax)
{
	static_assert(std::is_scalar<T>::value, "T must be a scalar");

	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragSingleScalar<T>>(GetDataType<T>(), pMin, pMax, pData, pStep, "", GetFormat<T>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<T>>();
	dispatcher.RegisterReference(pData);
	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120.f, 0.f };
	return widget;
}

template<typename T>
inline FRAWidget& FR::FRGuiDrawer::DrawScalar(GUI::FRWidgetContainer& pRoot, const std::string& pName, std::function<T(void)> pGatherer, std::function<void(T)> pProvider, float pStep, T pMin, T pMax)
{
	static_assert(std::is_scalar<T>::value, "T must be a scalar");
	
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragSingleScalar<T>>(GetDataType<T>(), pMin, pMax, static_cast<T>(0), pStep, "", GetFormat<T>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<T>>();
	dispatcher.RegisterGatherer(pGatherer);
	dispatcher.RegisterProvider(pProvider);
	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120.f, 0.f };
	return widget;
}

template<typename T, typename ...TArgs>
inline FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawComboBox(GUI::FRWidgetContainer& pRoot, const std::string& pName, int pIndex, std::vector<std::string> pChoices, T* pObject, void(T::* pCallback)(TArgs...), auto... pArgs)
{
	auto& group = pRoot.CreateWidget<FRGroup>();

	FRGuiDrawer::CreateTitle(group, pName).lineBreak = false;
	auto& widget = group.CreateWidget<FRComboBox>(pIndex);
	widget.SetValueChanged(pObject, pCallback, pArgs...);
	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120.f, 0.f };

	for (int i = 0; i < pChoices.size(); i++)
	{
		widget.choices.emplace(i, pChoices[i]);
	}

	return group;
}

template<typename T, typename ...TArgs>
inline FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawItemSelect(GUI::FRWidgetContainer& pRoot, const std::string& pName, GUI::FRItemSelect::EItemType pType, T* pObject, void(T::* pCallback)(TArgs...), auto... pArgs)
{
	auto& widget = pRoot.CreateWidget<FRItemSelect>(pType, pName);
	widget.SetDataReceivedChanged(pObject, pCallback, pArgs...);
	return widget;
}
