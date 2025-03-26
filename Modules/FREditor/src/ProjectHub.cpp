#include "ProjectHub.h"

#include "Window.h"
#include "MessageBox.h"
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"

#include "Editor.FRImGuiHelper.h"

#include <GUI.FRText.h>
#include <GUI.FRLayout.h>
#include <GUI.FRButton.h>
#include <GUI.FRSeparator.h>
#include <GUI.FRInputText.h>
#include <GUI.FRPanelWindow.h>

#include <Core.FRInput.h>
#include <Core.FRGuiDrawer.h>

#include <Color.h>
#include <FRRendererWarp.h>
#include <FRFilamentHelper.h>

#include <fstream>
#include <filesystem>

#include <utils/Path.h>
#include <IconsMaterialDesignIcons.h>

using namespace FR::GUI;

namespace FR
{
	utils::Path kProjectFile= utils::Path(std::string(getenv("APPDATA")) + "/FREditor/Editor/projects.ini");

	class ProjectHubPanel
		: public FRPanelWindow
	{
	public:
		ProjectHubPanel(const std::string& pTitle, bool& pReadyToGo, std::string& pProjectPath, std::string& pProjectName)
			: FRPanelWindow(pTitle)
			, mReadyToGo(pReadyToGo)
			, mProjectPath(pProjectPath)
			, mProjectName(pProjectName)
		{
			movable = false;
			titleBar = false;
			resizable = false;

			SetSize({ 1000, 580 });
			SetPosition({ 0.f, 0.f });

			if (auto tempDir = kProjectFile.getParent(); !tempDir.exists())
			{
				tempDir.mkdirRecursive();
			}

			auto& openBtn = CreateWidget<FRButton>(ICON_MDI_FOLDER_OPEN " Open Project");
			{
				openBtn.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
				openBtn.lineBreak = false;
			}
			
			auto& newBtn = CreateWidget<FRButton>(ICON_MDI_FOLDER_EDIT " New Project");
			{
				newBtn.idleBackgroundColor = { 0.0f, 0.5f, 0.0f };
				newBtn.lineBreak = false;
			}

			auto& pathField = CreateWidget<FRInputText>("");
			{
				pathField.alignment = EWidgetAlignment::LEFT;
				pathField.lineBreak = false;
				pathField.size.x = 585.f;
			}

			mGoBtn = &CreateWidget<FRButton>(ICON_MDI_GESTURE_DOUBLE_TAP " GO");
			{
				mGoBtn->idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
				mGoBtn->lineBreak = false;
			}
			
			UpdateBtnState("");

			openBtn.ClickedEvent += [this]
				{
					OpenFileDialog dialog("Open Project");
					dialog.AddFileType("FR Project", "*.project");
					dialog.Show();

					if (dialog.HasSucceeded())
					{
						std::string projectPath = dialog.GetSelectedFilePath();
						utils::Path path = utils::Path(projectPath);
						utils::Path parentPath = path.getParent();
						RegisterProject(parentPath);
						OpenProject(parentPath);
					}
				};

			newBtn.ClickedEvent += [this, &pathField]
				{
					SaveFileDialog dialog("New Project Location");
					dialog.DefineExtension("FR Project", "");
					dialog.Show();
					
					if (dialog.HasSucceeded())
					{
						std::string projectPath = dialog.GetSelectedFilePath();
						utils::Path path = utils::Path(projectPath);
						pathField.content = path.getParent();
						pathField.showDefaultLable = path.isEmpty();
						UpdateBtnState(pathField.content);
					}
				};

			pathField.ContentChangedEvent += [this, &pathField](std::string pContent)
				{
					utils::Path path = utils::Path(pContent);
					pathField.content = path.getPath();
					pathField.showDefaultLable = path.isEmpty();
					UpdateBtnState(pathField.content);
				};

			mGoBtn->ClickedEvent += [this, &pathField]
				{
					CreateProject(pathField.content);
					RegisterProject(pathField.content);
					OpenProject(pathField.content);
				};

			FRGuiDrawer::DrawSpace(*this, 4);

			CreateWidget<FRSeparator>();

			FRGuiDrawer::DrawSpace(*this, 4);

			auto& columns = CreateWidget<FRColumns<2>>();
			columns.widths = { 750, 500 };

			std::string line;
			std::ifstream file(kProjectFile);
			if (file.is_open())
			{
				while (getline(file, line))
				{
					utils::Path path = utils::Path(line);
					if (!path.isEmpty())
					{
						auto& text = columns.CreateWidget<FRText>(path);
						auto& actions = columns.CreateWidget<FRGroup>();
						auto& openBtn = actions.CreateWidget<FRButton>(ICON_MDI_FOLDER_OPEN " Open");
						{
							openBtn.idleBackgroundColor = { 0.7f, 0.5f, 0.0f };
							openBtn.lineBreak = false;
						}

						auto& deleteBtn = actions.CreateWidget<FRButton>(ICON_MDI_FOLDER_REMOVE " Delete");
						{
							deleteBtn.idleBackgroundColor = { 0.5f, 0.0f, 0.0f };
							//deleteBtn.lineBreak = false;
						}

						openBtn.ClickedEvent += [this, path]
							{
								OpenProject(path);
							};

						std::string toErase = path;
						deleteBtn.ClickedEvent += [this, &text, &actions, toErase]
							{
								text.Destroy();
								actions.Destroy();

								std::string line;
								std::ofstream temp("temp");
								std::ifstream file(kProjectFile);

								while (getline(file, line))
								{
									if (line != toErase)
									{
										temp << line << std::endl;
									}
								}

								temp.close();
								file.close();

								std::filesystem::remove(kProjectFile.getPath());
								std::filesystem::rename("temp", kProjectFile.getPath());
							};
					}
				}
				
				file.close();
			}
		}

		void CreateProject(const std::string& pPath)
		{
			auto path = utils::Path(pPath);
			if (!path.isEmpty() && !path.exists())
			{
				path.mkdir();
				path.concat("Assets").mkdir();
				utils::Path parent = path.getParent();
				std::ofstream projectFile(parent.concat(parent.getName() + ".project"));
			}
		}

		void RegisterProject(const std::string& pPath)
		{
			bool registered = false;

			{
				std::string line;
				std::ifstream file(kProjectFile);
				if (file.is_open())
				{
					while (getline(file, line))
					{
						if (line == pPath)
						{
							registered = true;
							break;
						}
					}
					file.close();
				}
			}

			if (!registered)
			{
				std::ofstream projectsFile(kProjectFile, std::ios::app);
				projectsFile << pPath << std::endl;
			}
		}

		void OpenProject(const std::string& pPath)
		{
			auto path = utils::Path(pPath);
			if (!path.isEmpty() && path.exists())
			{
				mReadyToGo = true;
				mProjectPath = path;
				mProjectName = path.getName();
			}
			
			Close();
		}

		void UpdateBtnState(std::string pPath)
		{
			utils::Path path = utils::Path(pPath);
			bool validPath = !path.isEmpty() && path.exists();
			mGoBtn->idleBackgroundColor = validPath ? Color{ 0.0f, 0.5f, 0.0f } : Color{ 0.1f, 0.1f, 0.1f };
			mGoBtn->disabled = !validPath;
		}

		void Draw() override
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 50.f, 50.f });
			{
				FRPanelWindow::Draw();
			}
			ImGui::PopStyleVar(1);
		}

	private:
		bool& mReadyToGo;
		std::string& mProjectPath;
		std::string& mProjectName;
		GUI::FRButton* mGoBtn{ nullptr };

	};
}

FR::ProjectHub::ProjectHub()
{
	Window::Settings settings = { .title = "Project Hub", .width = 1000.f, .height = 580.f };
	mGuiHelper = std::make_unique<FRImGuiHelper>(settings);
	{
		mGuiHelper->EnableDocking(false);
		mGuiHelper->EnableEditorLayoutSave(false);
	
		mGuiHelper->AddPanel<ProjectHubPanel>("ProjectHubPanel", mReadyToGo, mProjectPath, mProjectName);
	}
}

FR::ProjectHub::Result FR::ProjectHub::Run()
{
	auto renderer = FRFilamentHelper::GetRenderer();
	auto hubPanel = mGuiHelper->GetPanel<ProjectHubPanel>();

	while (!mGuiHelper->ShouldClose())
	{
		mGuiHelper->Update();

		if (renderer->BeginFrame(FRFilamentHelper::GetSwapChain()))
		{
			mGuiHelper->Render();

			renderer->EndFrame();
		}
		else
		{
			++mSkippedFrames;
		}

		if (!hubPanel->IsOpened())
		{
			mGuiHelper->SetShouldClose(true);
		}
	}

	return { mReadyToGo, mProjectPath, mProjectName };
}

FR::ProjectHub::~ProjectHub()
{

}
