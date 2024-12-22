#include "GUI.FRAWidget.h"
#include "GUI.FRWidgetContainer.h"

namespace FR::GUI
{
	uint64_t FRAWidget::__WIDGET_ID_INCREMENT = 0;
}

FR::GUI::FRAWidget::FRAWidget(const std::string& pName)
	:name(pName)
{
	mWidgetID = "##" + std::to_string(__WIDGET_ID_INCREMENT++);
}

void FR::GUI::FRAWidget::Draw()
{
	if (enabled)
	{
		_Draw_Impl();

		if (mAutoExecutePlugins)
		{
			ExecutePlugins();
		}

		if (!lineBreak)
		{
			ImGui::SameLine();
		}
	}
}

void FR::GUI::FRAWidget::LinkTo(const FRAWidget* pWidget)
{
	mWidgetID = pWidget->mWidgetID;
}

void FR::GUI::FRAWidget::Destroy()
{
	mDestroyed = true;
}

bool FR::GUI::FRAWidget::IsDestroyed()
{
	return mDestroyed;
}

void FR::GUI::FRAWidget::SetParent(FRWidgetContainer* pParent)
{
	parent = pParent;
}

FR::GUI::FRWidgetContainer* FR::GUI::FRAWidget::GetParent()
{
	return parent;
}

std::string FR::GUI::FRAWidget::GetWidgetID()
{
	return mWidgetID;
}

glm::vec2 FR::GUI::FRAWidget::GetLabelSize()
{
	return MathConvert::ToGlmVec2(ImGui::CalcTextSize(name.c_str()));
}

void FR::GUI::FRAWidget::SetItemSize()
{
	if (sizeType == EWidgetSizeType::RELATIVE)
	{
		if (size == glm::vec2{ 0.f, 0.f })
		{
			size.x = 1.f;
		}
	}

	if (size != glm::vec2{ 0.f, 0.f })
	{
		mCaculeteSize = CaculateSize();
		ImGui::SetNextItemWidth(mCaculeteSize.x);
	}
}

void FR::GUI::FRAWidget::SetItemAlign()
{
	switch (alignment)
	{
	case EWidgetAlignment::LEFT:
	{
		if (position != glm::vec2{ 0.f, 0.f })
		{
			ImGui::SetCursorPosX(position.x);
			if (position.y != 0.f)
			{
				ImGui::SetCursorPosY(position.y);
			}
		}
	}
	break;
	case EWidgetAlignment::RIGHT:
	{
		auto contentSize = ImGui::GetContentRegionMax();
		ImGui::SetCursorPosX(contentSize.x - size.x);
		if (position.y != 0.f)
		{
			ImGui::SetCursorPosY(position.y);
		}
	}
	break;
	case EWidgetAlignment::CENTER:
	{
		auto contentSize = ImGui::GetContentRegionMax();
		ImGui::SetCursorPosX(contentSize.x * 0.5f - size.x * 0.5f);
		if (position.y != 0.f)
		{
			ImGui::SetCursorPosY(position.y);
		}
	}
		break;
	default:
		break;
	}
}

void FR::GUI::FRAWidget::SetItemLayout()
{
	SetItemSize();
	SetItemAlign();
}

void FR::GUI::FRAWidget::DrawItemActivityOutline(glm::vec2 pMin, glm::vec2 pMax, bool pInactive, Color pColorActive)
{
	auto style = ImGui::GetStyle();
	auto* drawList = ImGui::GetWindowDrawList();

	ImRect expandedRect = ImRect({ pMin.x, pMin.y }, { pMax.x, pMax.y });
	expandedRect.Min.x -= 1.0f;
	expandedRect.Min.y -= 1.0f;
	expandedRect.Max.x += 1.0f;
	expandedRect.Max.y += 1.0f;

	const ImRect rect = expandedRect;
	if (ImGui::IsItemHovered() && !ImGui::IsItemActive())
	{
		drawList->AddRect(rect.Min, rect.Max, ImColor(60.f, 60.f, 60.f), style.FrameRounding, 0, 1.5f);
	}
	if (ImGui::IsItemActive())
	{
		ImColor color = ImColor(pColorActive.r, pColorActive.g, pColorActive.b);
		drawList->AddRect(rect.Min, rect.Max, color, style.FrameRounding, 0, 1.f);
	}
	else if (!ImGui::IsItemHovered() && pInactive)
	{
		drawList->AddRect(rect.Min, rect.Max, ImColor(50.f, 50.0f, 50.f), style.FrameRounding, 0, 1.f);
	}
}

glm::vec2 FR::GUI::FRAWidget::CaculateSize()
{
	glm::vec2 result(0.f);
	switch (sizeType)
	{
	case FR::GUI::EWidgetSizeType::ABSOLUTE:
	{
		result = size;
	}
	break;
	case FR::GUI::EWidgetSizeType::RELATIVE:
	{
		result = size;
		if (position != glm::vec2{ 0.f, 0.f })
		{
			auto contentSize = ImGui::GetContentRegionMax();
			result.x *= (contentSize.x - position.x);
			result.y *= (contentSize.y - position.y);
		}
		else
		{
			auto avaliSize = ImGui::GetContentRegionAvail();
			result.x *= avaliSize.x;
			result.y *= avaliSize.y;
		}
	}
		break;
	default:
		break;
	}

	return result;
}
