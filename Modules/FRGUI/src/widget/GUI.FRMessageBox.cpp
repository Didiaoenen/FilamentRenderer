#include "GUI.FRMessageBox.h"

FR::GUI::FRMessageBox::FRMessageBox(const std::string& pName)
	: FRAWidget(pName)
{
}

void FR::GUI::FRMessageBox::InitMessageBox(const std::string& pTitle, const std::string& pContext, std::vector<std::string> pCaptions)
{
	mTitle = pTitle;
	mContext = pContext;
	mCaptions = pCaptions;
	mInited = true;
}

void FR::GUI::FRMessageBox::OpenMessageBox()
{
	ImGui::OpenPopup(mTitle.c_str());
}

bool FR::GUI::FRMessageBox::IsInited()
{
	return mInited;
}

void FR::GUI::FRMessageBox::_Draw_Impl()
{
	//if (size != glm::vec2{ 0.f, 0.f })
	{
		ImGui::SetNextWindowSize({ 324.f, size.y });
	}

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal(mTitle.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 316.f);
		ImGui::Text(mContext.c_str());
		ImGui::Separator();

		for (int i = 0; i < mCaptions.size(); i++)
		{
			if (ImGui::Button(mCaptions[i].c_str(), {150.f, 0.f}))
			{
				ImGui::CloseCurrentPopup();
				ClickedEvent.Invoke(i);
				break;
			}

			ImGui::SameLine();
		}

		ImGui::EndPopup();
	}
}
