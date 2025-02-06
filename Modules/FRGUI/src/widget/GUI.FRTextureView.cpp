#include "GUI.FRTextureView.h"

#include <Core.FRTexture.h>

FR::GUI::FRTextureView::FRTextureView(const glm::vec2& pSize, FRTexture* pBackgroud)
	: backgroud(pBackgroud)
{
	size = pSize;
}

void FR::GUI::FRTextureView::SetClickedEvent(std::function<void()> pEvent)
{
	mClickedEvent += [pEvent] { pEvent(); };
}

void FR::GUI::FRTextureView::SetTexture(FRTexture* pBackgroud)
{
	backgroud = pBackgroud;
}

void FR::GUI::FRTextureView::_Draw_Impl()
{
	auto cursorPos = ImGui::GetCursorPos();
	ImGui::Image(backgroud->NativePtr(), MathConvert::ToImVec2(size), { 0.f, 0.f }, { 1.f, 1.f });

	auto& style = ImGui::GetStyle();
	auto defaultIdleColor = style.Colors[ImGuiCol_Button];

	style.Colors[ImGuiCol_Button] = MathConvert::ToImVec4({ 0.5f, 0.0f, 0.0f });

	ImGui::SetItemAllowOverlap();
	ImGui::SetCursorPos({ cursorPos.x + 25, cursorPos.y + 55 });
	if (ImGui::ButtonEx(("Clear" + mWidgetID).c_str(), MathConvert::ToImVec2({ 50, 20 }), ImGuiButtonFlags_None))
	{
		mClickedEvent.Invoke();
	}

	style.Colors[ImGuiCol_Button] = defaultIdleColor;
}
