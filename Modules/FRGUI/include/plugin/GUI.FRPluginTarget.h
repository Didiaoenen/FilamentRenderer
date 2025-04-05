#pragma once

#include "GUI.FRIPlugin.h"
#include <Tools.FREvent.h>

#include <imgui.h>

#include <string>

namespace FR::GUI
{
	template<typename T>
	class FRPluginTarget
		: public FRIPlugin
	{
	public:
		FRPluginTarget(const std::string& pIdentifier) 
			: identifier(pIdentifier)
		{
		}

		virtual void Execute() override
		{
			if (ImGui::BeginDragDropTarget())
			{
				if (!mHovered)
				{
					HoverStartEvent.Invoke();
				}

				mHovered = true;

				ImGuiDragDropFlags targetFlags = 0;

				if (!showYellowRect)
				{
					targetFlags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
				}

				if (const auto payload = ImGui::AcceptDragDropPayload(identifier.c_str(), targetFlags))
				{
					T* data = static_cast<T*>(payload->Data);
					DataReceivedEvent.Invoke(*data);
				}
				
				ImGui::EndDragDropTarget();
			}
			else
			{
				if (mHovered)
				{
					HoverEndEvent.Invoke();
				}

				mHovered = false;
			}
		}

		bool IsHovered() const
		{
			return mHovered;
		}

	public:
		std::string identifier;

		bool showYellowRect{ true };

		FREvent<> HoverEndEvent;
		
		FREvent<> HoverStartEvent;
		
		FREvent<T> DataReceivedEvent;

	private:
		bool mHovered{ false };

	};
}