#pragma once

#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
	void TextClipped(const char* text, const ImVec2& pos_min, const ImVec2& pos_max, const char* text_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect, float wrap_width);

	void TextClipped(const char* text, ImDrawList* draw_list, const ImVec2& pos_min, const ImVec2& pos_max, const char* text_display_end, const ImVec2* text_size_if_known, const ImVec2& align, const ImRect* clip_rect, float wrap_width);
}