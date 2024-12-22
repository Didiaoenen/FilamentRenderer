#include "ImguiTextClipped.h"

void ImGui::TextClipped(const char* text, const ImVec2& pos_min, const ImVec2& pos_max, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect, float wrap_width)
{
	const char* text_display_end = ImGui::FindRenderedTextEnd(text, text_end);
	const int text_len = static_cast<int>(text_display_end - text);
	if (text_len == 0)
		return;

	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	ImGui::TextClipped(text, window->DrawList, pos_min, pos_max, text_display_end, text_size_if_known, align, clip_rect, wrap_width);
	if (g.LogEnabled)
		ImGui::LogRenderedText(&pos_min, text, text_display_end);
}

void ImGui::TextClipped(const char* text, ImDrawList* draw_list, const ImVec2& pos_min, const ImVec2& pos_max, const char* text_display_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect, float wrap_width)
{
	// Perform CPU side clipping for single clipped element to avoid using scissor state
	ImVec2 pos = pos_min;
	const ImVec2 text_size = text_size_if_known ? *text_size_if_known : ImGui::CalcTextSize(text, text_display_end, false, wrap_width);

	const ImVec2* clip_min = clip_rect ? &clip_rect->Min : &pos_min;
	const ImVec2* clip_max = clip_rect ? &clip_rect->Max : &pos_max;

	// Align whole block. We should defer that to the better rendering function when we'll have support for individual line alignment.
	if (align.x > 0.0f)
		pos.x = ImMax(pos.x, pos.x + (pos_max.x - pos.x - text_size.x) * align.x);

	if (align.y > 0.0f)
		pos.y = ImMax(pos.y, pos.y + (pos_max.y - pos.y - text_size.y) * align.y);

	// Render
	ImVec4 fine_clip_rect(clip_min->x, clip_min->y, clip_max->x, clip_max->y);
	draw_list->AddText(nullptr, 0.f, pos, ImGui::GetColorU32(ImGuiCol_Text), text, text_display_end, wrap_width, &fine_clip_rect);
}