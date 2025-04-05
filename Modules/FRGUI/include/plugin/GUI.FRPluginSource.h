#pragma once

#include "GUI.FRIPlugin.h"

#include <imgui.h>

#include <string>

namespace FR::GUI
{
	template<typename T>
	class FRPluginSource
		: public FRIPlugin
	{
	public:
		FRPluginSource(const std::string& pIdentifier, const std::string& pTooltip, T pData)
			: identifier(pIdentifier)
			, tooltip(pTooltip)
			, data(pData)
		{
		}

		virtual void Execute() override
		{
			ImGuiDragDropFlags flags = 0;
			flags |= ImGuiDragDropFlags_SourceNoDisableHover;
			flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;

			if (!hasTooltip)
			{
				flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip;
			}

			if (ImGui::BeginDragDropSource(flags))
			{
				if (!mDragged)
				{
					DragStartEvent.Invoke();
				}

				mDragged = true;

				if (!(flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
				{
					ImGui::Text(tooltip.c_str());
				}

				ImGui::SetDragDropPayload(identifier.c_str(), &data, sizeof(data));
				
				ImGui::EndDragDropSource();
			}
			else
			{
				if (mDragged)
				{
					DragStopEvent.Invoke();
				}

				mDragged = false;
			}
		}

		bool IsDragged() const
		{
			return mDragged;
		}

	public:
		T data;

		std::string tooltip;
		
		std::string identifier;
		
		bool hasTooltip{ true };
		
		FREvent<> DragStartEvent;
		
		FREvent<> DragStopEvent;

	private:
		bool mDragged{ false };

	};
}