#include "GUI.FRCanvas.h"
#include "GUI.FRAPanel.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <backends/imgui_impl_sdl2.h>

void FR::GUI::FRCanvas::Draw()
{
	if (!mPanels.empty())
	{
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();

		ImGuizmo::BeginFrame();

		auto viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.f, 0.f });

		auto flags = ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_MenuBar;

		ImGui::Begin("##dockspace", nullptr, flags);
		
		ImGuiID dockspaceID = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspaceID, { 0.f, 0.f }, ImGuiDockNodeFlags_PassthruCentralNode);
		
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetWindowSize(io.DisplaySize);
		
		ImGui::SetWindowPos({ 0.f, 0.f });

		ImGui::End();

		ImGui::PopStyleVar(3);

		for (const auto& panel : mPanels)
		{
			panel->Draw();
		}

		ImGui::Render();
	}
}


void FR::GUI::FRCanvas::AddPanel(FRAPanel* pPanel)
{
	mPanels.emplace_back(pPanel);
}

void FR::GUI::FRCanvas::RemovePanel(FRAPanel* pPanel)
{
	mPanels.erase(std::remove_if(mPanels.begin(), mPanels.end(), [pPanel](FRAPanel* pItem)
		{
			return pPanel == pItem;
		}));
}

void FR::GUI::FRCanvas::RemoveAllPanels()
{
	mPanels.clear();
}

FR::GUI::FRCanvas::~FRCanvas()
{

}
