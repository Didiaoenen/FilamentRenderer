#include "Core.FRGuiDrawer.h"

#include "Core.FRModel.h"
#include "Core.FRShader.h"
#include "Core.FRTexture.h"
#include "Core.FRMaterial.h"
#include "Core.FRModelManager.h"
#include "Core.FRShaderManager.h"
#include "Core.FRTextureManager.h"
#include "Core.FRMaterialManager.h"

#include <MathExtension.h>
#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

namespace
{
	using GroupPair = std::pair<std::string, FR::GUI::FRGroup*>;
}

namespace FR
{
	FRTexture* FRGuiDrawer::__EMPTY_TEXTURE = nullptr;
	const float FRGuiDrawer::_MIN_FLOAT = -999999999.f;
	const float FRGuiDrawer::_MAX_FLOAT = +999999999.f;
	const Color FRGuiDrawer::TitleColor = { 0.85f, 0.65f, 0.0f };
	const Color FRGuiDrawer::ClearButtonColor = { 0.5f, 0.0f, 0.0f };
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawBoolean(FRWidgetContainer& pRoot, const std::string& pName, bool& pData)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRCheckBox>();
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<bool>>();
	dispatcher.RegisterReference(pData);
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawBoolean(FRWidgetContainer& pRoot, const std::string& pName, std::function<bool(void)> pGatherer, std::function<void(bool)> pProvider)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRCheckBox>();
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<bool>>();
	{
		dispatcher.RegisterGatherer([pGatherer]()
			{
				bool value = pGatherer();
				return reinterpret_cast<bool&>(value);
			});

		dispatcher.RegisterProvider([pProvider](bool pValue)
			{
				pProvider(reinterpret_cast<bool&>(pValue));
			});
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawString(FRWidgetContainer& pRoot, const std::string& pName, std::string& pData)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRInputText>("");
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::string>>();
	dispatcher.RegisterReference(pData);
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawString(FRWidgetContainer& pRoot, const std::string& pName, std::function<std::string(void)> pGatherer, std::function<void(std::string)> pProvider)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRInputText>("");
	widget.showDefaultLable = false;
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::string>>();
	dispatcher.RegisterGatherer(pGatherer);
	dispatcher.RegisterProvider(pProvider);
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec2(FRWidgetContainer& pRoot, const std::string& pName, glm::vec2& pData, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 2>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 2>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 2>&>(pData));
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec2(FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec2(void)> pGatherer, std::function<void(glm::vec2)> pProvider, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 2>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 2>>>();
	{
		dispatcher.RegisterGatherer([pGatherer]()
			{
				glm::vec2 value = pGatherer();
				return reinterpret_cast<const std::array<float, 2>&>(value);
			});

		dispatcher.RegisterProvider([pProvider](std::array<float, 2> pValue)
			{
				pProvider(reinterpret_cast<glm::vec2&>(pValue));
			});
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec3(FRWidgetContainer& pRoot, const std::string& pName, glm::vec3& pData, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 3>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 3>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(pData));
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec3(FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec3(void)> pGatherer, std::function<void(glm::vec3)> pProvider, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 3>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 3>>>();
	{
		dispatcher.RegisterGatherer([pGatherer]()
			{
				glm::vec3 value = pGatherer();
				auto value0 = std::make_any<glm::vec3>(value);
				auto alignedValue = AlignValue(value0, glm::vec3());
				return reinterpret_cast<const std::array<float, 3>&>(alignedValue);
			});

		dispatcher.RegisterProvider([pProvider](std::array<float, 3> pValue)
			{
				pProvider(reinterpret_cast<glm::vec3&>(pValue));
			});
	}

	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120, 0.f };

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec4(FRWidgetContainer& pRoot, const std::string& pName, glm::vec4& pData, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 4>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(pData));
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawVec4(FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::vec4(void)> pGatherer, std::function<void(glm::vec4)> pProvider, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 4>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 4>>>();
	{
		dispatcher.RegisterGatherer([pGatherer]()
			{
				glm::vec4 value = pGatherer();
				return reinterpret_cast<const std::array<float, 4>&>(value);
			});

		dispatcher.RegisterProvider([pProvider](std::array<float, 4> pValue)
			{
				pProvider(reinterpret_cast<glm::vec4&>(pValue));
			});
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawQuat(FRWidgetContainer& pRoot, const std::string& pName, glm::quat& pData, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 4>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 4>>>();
	dispatcher.RegisterReference(reinterpret_cast<std::array<float, 4>&>(pData));
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawQuat(FRWidgetContainer& pRoot, const std::string& pName, std::function<glm::quat(void)> pGatherer, std::function<void(glm::quat)> pProvider, float pStep, float pMin, float pMax)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRDragMultipleScalars<float, 4>>(GetDataType<float>(), pMin, pMax, 0.f, pStep, "", GetFormat<float>());
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::array<float, 4>>>();
	{
		dispatcher.RegisterGatherer([pGatherer]()
			{
				glm::quat value = pGatherer();
				return reinterpret_cast<const std::array<float, 4>&>(value);
			});

		dispatcher.RegisterProvider([&dispatcher, pProvider](std::array<float, 4> p_value)
			{
				pProvider(glm::normalize(reinterpret_cast<glm::quat&>(p_value)));
			});
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawColor(FRWidgetContainer& pRoot, const std::string& pName, Color& pColor, bool pHasAlpha)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRColorEdit>(pHasAlpha);
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<Color>>();
	dispatcher.RegisterReference(pColor);
	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120.f, 0.f };
	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawColor(FRWidgetContainer& pRoot, const std::string& pName, std::function<Color(void)> pGatherer, std::function<void(Color)> pProvider, bool pHasAlpha)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRColorEdit>(pHasAlpha);
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<Color>>();
	dispatcher.RegisterGatherer(pGatherer);
	dispatcher.RegisterProvider(pProvider);
	widget.sizeType = EWidgetSizeType::RELATIVE;
	widget.position = { 120.f, 0.f };
	return widget;
}

FR::GUI::FRItemSelect& FR::FRGuiDrawer::DrawMesh(FRWidgetContainer& pRoot, const std::string& pName, FRModel*& pData, FREvent<>* pUpdateNotifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	std::string displayedText = (pData ? pData->path : std::string("Empty"));
	auto& itemSelect = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MODEL, displayedText);
	{
		itemSelect.SetTextReceivedEvent([&pData, pUpdateNotifier](std::string& pContext, auto pReceivedData)
			{
				if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MODEL)
				{
					if (auto resource = GetService(FRModelManager).GetResource(pReceivedData.first); resource)
					{
						pData = resource;
						pContext = pReceivedData.first;

						if (pUpdateNotifier)
						{
							pUpdateNotifier->Invoke();
						}
					}
				}
			});
	}

	auto& widgetMaterials = pRoot.CreateWidget<FRTreeNode>("Materials", "", "", true);
	{
		widgetMaterials.framed = true;
		widgetMaterials.position = { 30.f, 0.f };
		for (auto materialName : pData->GetMaterialNames())
		{
			auto& widgetMaterial = widgetMaterials.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MATERIAL, "");
			widgetMaterial.SetText(materialName);
		}
	}

	return itemSelect;
}

FR::GUI::FRItemSelect& FR::FRGuiDrawer::DrawShader(FRWidgetContainer& pRoot, const std::string& pName, FRShader*& pData, FREvent<>* pUpdateNotifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::SHADER, pData ? pData->path : std::string("Empty"));
	widget.SetTextReceivedEvent([&pData, pUpdateNotifier](std::string& pContext, auto pReceivedData)
		{
			if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::SHADER)
			{
				if (auto resource = GetService(FRShaderManager).GetResource(pReceivedData.first))
				{
					pData = resource;
					pContext = pReceivedData.first;
					if (pUpdateNotifier)
					{
						pUpdateNotifier->Invoke();
					}
				}
			}
		});

	return widget;
}

FR::GUI::FRItemSelect& FR::FRGuiDrawer::DrawMaterial(FRWidgetContainer& pRoot, const std::string& pName, FRMaterial*& pData, FREvent<>* pUpdateNotifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRItemSelect>(FRItemSelect::EItemType::MATERIAL, pData ? pData->path : std::string("Empty"));
	widget.SetTextReceivedEvent([&pData, pUpdateNotifier](std::string& pContext, auto pReceivedData)
		{
			if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::MATERIAL)
			{
				if (auto resource = GetService(FRMaterialManager).GetResource(pReceivedData.first))
				{
					pData = resource;
					pContext = pReceivedData.first;
					if (pUpdateNotifier)
					{
						pUpdateNotifier->Invoke();
					}
				}
			}
		});

	return widget;
}

FR::GUI::FRImage& FR::FRGuiDrawer::DrawTexture(FRWidgetContainer& pRoot, const std::string& pName, FRTexture*& pData, FREvent<>* pUpdateNotifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& rightSide = pRoot.CreateWidget<FRGroup>();

	auto& widget = rightSide.CreateWidget<FRImage>(pData ? pData : __EMPTY_TEXTURE, glm::vec2{ 75, 75 });
	{
		widget.AddPlugin<FRPluginTarget<GroupPair>>("File").DataReceivedEvent += [&widget, &pData, pUpdateNotifier](auto pReceivedData)
			{
				if (FRPathUtils::GetFileType(pReceivedData.first) == EFileType::TEXTURE)
				{
					if (auto resource = GetService(FRTextureManager).GetResource(pReceivedData.first); resource)
					{
						pData = resource;
						widget.textureID = resource;

						if (pUpdateNotifier)
						{
							pUpdateNotifier->Invoke();
						}
					}
				}
			};

		widget.lineBreak = false;
	}

	auto& resetButton = rightSide.CreateWidget<FRButton>("Clear");
	{
		resetButton.idleBackgroundColor = ClearButtonColor;
		resetButton.ClickedEvent += [&widget, &pData, pUpdateNotifier]
			{
				pData = nullptr;
				widget.textureID = __EMPTY_TEXTURE ? __EMPTY_TEXTURE : 0;

				if (pUpdateNotifier)
				{
					pUpdateNotifier->Invoke();
				}
			};
	}

	return widget;
}

FR::GUI::FRText& FR::FRGuiDrawer::DrawAsset(FRWidgetContainer& pRoot, const std::string& pName, std::string& pData, FREvent<>* pUpdateNotifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& rightSide = pRoot.CreateWidget<FRGroup>();

	auto& widget = rightSide.CreateWidget<FRText>(pData.empty() ? std::string("Empty") : pData);
	{
		widget.AddPlugin<FRPluginTarget<GroupPair>>("File").DataReceivedEvent += [&widget, &pData, pUpdateNotifier](auto pReceivedData)
			{
				pData = pReceivedData.first;
				widget.content = pReceivedData.first;

				if (pUpdateNotifier)
				{
					pUpdateNotifier->Invoke();
				}
			};

		widget.lineBreak = false;
	}

	auto& resetButton = rightSide.CreateWidget<FRButtonSmall>("Clear");
	{
		resetButton.idleBackgroundColor = ClearButtonColor;
		resetButton.ClickedEvent += [&widget, &pData, pUpdateNotifier]
			{
				pData = "";
				widget.content = "Empty";

				if (pUpdateNotifier)
				{
					pUpdateNotifier->Invoke();
				}
			};
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::DrawDDString(FRWidgetContainer& pRoot, const std::string& pName, std::function<std::string(void)> pGatherer, std::function<void(std::string)> pProvider, const std::string& pIdentifier)
{
	CreateTitle(pRoot, pName).lineBreak = false;
	auto& widget = pRoot.CreateWidget<FRInputText>("");
	auto& dispatcher = widget.AddPlugin<FRDataDispatcher<std::string>>();
	{
		dispatcher.RegisterGatherer(pGatherer);
		dispatcher.RegisterProvider(pProvider);
	}

	auto& ddTarget = widget.AddPlugin<FRPluginTarget<GroupPair>>(pIdentifier);
	{
		ddTarget.DataReceivedEvent += [&widget, &dispatcher](GroupPair pData)
			{
				widget.content = pData.first;
				dispatcher.NotifyChange();
			};
	}

	return widget;
}

FR::GUI::FRAWidget& FR::FRGuiDrawer::CreateTitle(FRWidgetContainer& pRoot, const std::string& pName)
{
	return pRoot.CreateWidget<FRTextColored>(pName, TitleColor);
}

void FR::FRGuiDrawer::DrawSpace(GUI::FRWidgetContainer& pRoot, int pSpace)
{
	for (int i = 0; i < pSpace; i++)
	{
		pRoot.CreateWidget<FRSpacing>();
	}
}

void FR::FRGuiDrawer::ProvideEmptyTexture(FRTexture* pEmptyTexture)
{
	__EMPTY_TEXTURE = pEmptyTexture;
}

FR::FRTexture* FR::FRGuiDrawer::GetEmptyTexture()
{
	return __EMPTY_TEXTURE;
}
