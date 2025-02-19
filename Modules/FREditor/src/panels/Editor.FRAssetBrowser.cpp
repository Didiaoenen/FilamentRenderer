#include "Editor.FRAssetBrowser.h"

#include "Editor.FRApplication.h"
#include "Editor.FREditorActions.h"
#include "Editor.FRMaterialEditor.h"
#include "Editor.FREditorResources.h"

#include <Core.FRMesh.h>
#include <Core.FRModel.h>
#include <Core.FRShader.h>
#include <Core.FRTexture.h>
#include <Core.FRMaterial.h>
#include <Core.FRModelManager.h>
#include <Core.FRShaderManager.h>
#include <Core.FRTextureManager.h>
#include <Core.FRMaterialManager.h>

#include <SystemExec.h>
#include <SystemCalls.h>
#include <StringExtension.h>
#include <Tools.FRPathUtils.h>
#include <Tools.FRServiceLocator.h>

#include <utils/Path.h>

using namespace FR::GUI;

namespace
{
	using GroupPair = std::pair<std::string, FR::GUI::FRGroup*>;
}

namespace FR
{
	std::string GetMetaFile(const std::string& pAssetPath)
	{
		return pAssetPath + ".meta";
	}

	void RemoveAsset(const std::string& pToDelete)
	{
		std::filesystem::remove(pToDelete);

		if (const std::string metaPath = GetMetaFile(pToDelete); std::filesystem::exists(metaPath))
		{
			std::filesystem::remove(metaPath);
		}
	}

	void RenameAsset(const std::string& pPrev, const std::string& pNew)
	{
		std::filesystem::rename(pPrev, pNew);

		if (const std::string previousMetaPath = GetMetaFile(pPrev); std::filesystem::exists(previousMetaPath))
		{
			if (const std::string newMetaPath = GetMetaFile(pNew); !std::filesystem::exists(newMetaPath))
			{
				std::filesystem::rename(previousMetaPath, newMetaPath);
			}
		}
	}

	class TexturePreview
		: public FRIPlugin
	{
	public:
		TexturePreview()
			: image(nullptr, { 100.f, 100.f })
		{
		}

		void SetTexturePreview(const std::string& pPath)
		{
			texture = GetService(FRTextureManager)[pPath];
		}

		virtual void Execute() override
		{
			if (ImGui::IsItemHovered())
			{
				if (texture)
				{
					image.textureID = texture;
				}

				ImGui::BeginTooltip();
				{
					image.Draw();
				}
				ImGui::EndTooltip();
			}
		}

	public:
		FRImage image;
		FRTexture* texture{ nullptr };

	};

	class BrowserItemMenu
		: public FRContextualMenu
	{
	public:
		BrowserItemMenu(const std::string pFilePath, bool pProtect = false)
			: filePath(pFilePath)
			, protect(pProtect)
		{
		}

		virtual void CreateList()
		{
			if (!protect)
			{
				auto& deleteAction = CreateWidget<FRMenuItem>("Delete");
				deleteAction.ClickedEvent += [this] { DeleteItem(); };
			}
		}

		virtual void Execute() override
		{
			if (mWidgets.size() > 0)
			{
				FRContextualMenu::Execute();
			}
		}

		virtual void DeleteItem() = 0;

	public:
		std::string filePath;
		bool protect{ false };

		FREvent<std::string> DestroyedEvent;

	};

	class FolderItemMenu
		: public BrowserItemMenu
	{
	public:
		FolderItemMenu(const std::string& pFilePath, bool pProtect = false)
			: BrowserItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			auto& showInExplorer = CreateWidget<FRMenuItem>("Show In Explorer");
			showInExplorer.ClickedEvent += [this] { SystemCalls::ShowInExplorer(filePath); };

			if (!protect)
			{
				auto& createMenu = CreateWidget<FRMenuList>("Create..");

				auto& folderMenu = createMenu.CreateWidget<FRMenuList>("Folder");
				{
					auto& folder = folderMenu.CreateWidget<FRInputText>("");
					folder.showDefaultLable = false;
					folder.EnterPressedEvent += [this](std::string pFolderName)
						{
							size_t fails = 0;
							std::string finalPath;

							do
							{
								finalPath = filePath + '/' + (!fails ? pFolderName : pFolderName + " (" + std::to_string(fails) + ')');

								++fails;
							} while (std::filesystem::exists(finalPath));

							std::filesystem::create_directory(finalPath);
							ItemAddedEvent.Invoke(finalPath);
							Close();
						};

					folderMenu.ClickedEvent += [&folder] { folder.content = ""; };
				}

				auto& shaderMenu = createMenu.CreateWidget<FRMenuList>("Shader");
				{
					auto& standardShaderMenu = shaderMenu.CreateWidget<FRMenuList>("Standard template");
					auto& standardShader = standardShaderMenu.CreateWidget<FRInputText>("");
					standardShader.showDefaultLable = false;
					standardShader.EnterPressedEvent += [this](std::string pShaderName)
						{
							size_t fails = 0;
							std::string finalPath1;
							std::string finalPath2;

							do
							{
								finalPath1 = utils::Path(filePath).concat((!fails ? pShaderName : pShaderName + " (" + std::to_string(fails) + ")") + ".shader");
								finalPath2 = utils::Path(filePath).concat((!fails ? pShaderName : pShaderName + " (" + std::to_string(fails) + ")") + ".filamat");

								++fails;
							} while (std::filesystem::exists(finalPath1));

							std::filesystem::copy_file(FRPathUtils::GetEngineAssetsPath() + "/Shaders/aiDefaultMat.shader", finalPath1);
							std::filesystem::copy_file(FRPathUtils::GetEngineAssetsPath() + "/Shaders/aiDefaultMat.filamat", finalPath2);
							ItemAddedEvent.Invoke(finalPath1);
							ItemAddedEvent.Invoke(finalPath2);
							Close();
						};

					standardShaderMenu.ClickedEvent += [&standardShader] { standardShader.content = ""; };
				}

				auto& materialMenu = createMenu.CreateWidget<FRMenuList>("Material");
				{
					auto& standardMaterialMenu = materialMenu.CreateWidget<FRMenuList>("Standard template");
					auto& standardMaterial = standardMaterialMenu.CreateWidget<FRInputText>("");
					standardMaterial.showDefaultLable = false;
					standardMaterial.EnterPressedEvent += [this](std::string pMaterialName)
						{
							size_t fails = 0;
							std::string finalPath;

							do
							{
								finalPath = utils::Path(filePath).concat((!fails ? pMaterialName : pMaterialName + " (" + std::to_string(fails) + ")") + ".mat");

								++fails;
							} while (std::filesystem::exists(finalPath));

							std::filesystem::copy_file(FRPathUtils::GetEngineAssetsPath() + "/Materials/Default.mat", finalPath);
							ItemAddedEvent.Invoke(finalPath);

							auto resourcesPath = GetService(FREditorActions).GetResourcePath(finalPath, protect);
							if (FRMaterial* material = GetService(FRMaterialManager)[resourcesPath])
							{
								auto materialEditor = FRApplication::GuiHelper()->GetPanel<FRMaterialEditor>();
								materialEditor->SetTarget(*material);
								materialEditor->Open();
								materialEditor->Focus();
							}

							Close();
						};

					standardMaterialMenu.ClickedEvent += [&standardMaterial] { standardMaterial.content = ""; };
				}

				BrowserItemMenu::CreateList();
			}
		}

		virtual void DeleteItem() override
		{
			if (false)
			{
				if (std::filesystem::exists(filePath) == true)
				{
					std::filesystem::remove_all(filePath);
					DestroyedEvent.Invoke(filePath);
				}
			}
		}

	public:
		FREvent<std::string> ItemAddedEvent;

	};

	class FileItemMenu
		: public BrowserItemMenu
	{
	public:
		FileItemMenu(const std::string& pFilePath, bool pProtect = false)
			: BrowserItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			auto& editAction = CreateWidget<FRMenuItem>("Open");
			editAction.ClickedEvent += [this] { SystemCalls::OpenFile(filePath); };

			if (!protect)
			{
				BrowserItemMenu::CreateList();
			}
		}

		virtual void DeleteItem() override
		{
			if (false)
			{
				RemoveAsset(filePath);
				DestroyedEvent.Invoke(filePath);
			}
		}
	};

	class ShaderMenu
		: public FileItemMenu
	{
	public:
		ShaderMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();

			auto& reloadAction = CreateWidget<FRMenuItem>("Compile");

			reloadAction.ClickedEvent += [this]
				{
					auto resourcesPath = GetService(FREditorActions).GetResourcePath(filePath, protect);
					{
						auto splits = StringExtension::Split(filePath, '.');
						auto command = std::format("matc -E -p desktop -a opengl -o {0} {1}", splits[0] + ".filamat", filePath);
						SystemExec::Exec(utils::Path(FRApplication::GetBinPath()) + command);

						if (FRShader* shader = GetService(FRShaderManager)[resourcesPath])
						{
							auto materials = shader->GetRefMaterials();

							FRShader* reloadShader = GetService(FRShaderManager).CreateResource(resourcesPath);
							GetService(FRShaderManager).RegisterResource(resourcesPath, reloadShader);

							if (materials.size() > 0)
							{
								for (const auto& material : materials)
								{
									material->SetShader(reloadShader, false);
									for (auto& [_, mesh] : material->GetRefMeshs())
									{
										mesh->SetMaterial(material);
									}
								}
							}
							
							if (auto materialEditor = FRApplication::GuiHelper()->GetPanel<FRMaterialEditor>())
							{
								if (materialEditor->IsOpened())
								{
									materialEditor->Refresh();
								}
							}
						}
					}
				};
		}
	};

	template<typename Resource, typename ResourceLoader>
	class PreviewableMenu
		: public FileItemMenu
	{
	public:
		PreviewableMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();
		}
	};

	class ModelMenu
		: public PreviewableMenu<FRModel, FRModelManager>
	{
	public:
		ModelMenu(const std::string& pFilePath, bool pProtect = false)
			: PreviewableMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			PreviewableMenu::CreateList();
		}
	};

	class TextureMenu
		: public PreviewableMenu<FRTexture, FRTextureManager>
	{
	public:
		TextureMenu(const std::string& pFilePath, bool pProtect = false)
			: PreviewableMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			PreviewableMenu::CreateList();
		}
	};

	class SceneMenu
		: public FileItemMenu
	{
	public:
		SceneMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();
		}
	};

	class MaterialMenu
		: public PreviewableMenu<FRMaterial, FRMaterialManager>
	{
	public:
		MaterialMenu(const std::string& pFilePath, bool pProtect = false)
			: PreviewableMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			auto& editAction = CreateWidget<FRMenuItem>("Edit");

			editAction.ClickedEvent += [this]
				{
					auto resourcesPath = GetService(FREditorActions).GetResourcePath(filePath, protect);
					if (FRMaterial* material = GetService(FRMaterialManager)[resourcesPath])
					{
						auto materialEditor = FRApplication::GuiHelper()->GetPanel<FRMaterialEditor>();
						materialEditor->SetTarget(*material);
						materialEditor->Open();
						materialEditor->Focus();
					}
				};

			PreviewableMenu::CreateList();
		}
	};

	class MeshMenu
		: public FileItemMenu
	{
	public:
		MeshMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();
		}
	};

	class SkeletonMenu
		: public FileItemMenu
	{
	public:
		SkeletonMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();
		}
	};

	class AnimationMenu
		: public FileItemMenu
	{
	public:
		AnimationMenu(const std::string& pFilePath, bool pProtect = false)
			: FileItemMenu(pFilePath, pProtect)
		{
		}

		virtual void CreateList() override
		{
			FileItemMenu::CreateList();
		}
	};
}

FR::FRAssetBrowser::FRAssetBrowser(const std::string& pTitle, bool pOpened, const FRPanelWindowSettings& pSettings)
	: FRPanelWindow(ICON_MDI_FOLDER_STAR " " + pTitle, pOpened, pSettings)
{
	scrollable = false;

	mEngineFolder = FRPathUtils::GetEngineAssetsPath();
	mProjectFolder = FRPathUtils::GetProjectAssetsPath();

	auto& assetSetting = CreateWidget<FRPopup>("AssetSetting");
	{
		auto sizeGetter = [this]()
			{
				return mItemScale;
			};

		auto sizeSetter = [this](int pScale)
			{
				auto tableView = dynamic_cast<FRTableView*>(mAssetView);
				tableView->cellSize = glm::vec2{ 120.f * pScale / 100.f, 200.f * pScale / 100.f };

				for (auto [widget, _] : mAssetView->GetWidgets())
				{
					auto group = dynamic_cast<FRGroup*>(widget);
					for (auto [item, _] : group->GetWidgets())
					{
						auto file = dynamic_cast<FRFileItem*>(item);
						file->scalePercent = pScale;
					}
				}

				mItemScale = pScale;
			};

		FRGuiDrawer::DrawSlider<int>(assetSetting, "Size", sizeGetter, sizeSetter, 45, 120);
	}

	auto& setting = CreateWidget<FRButton>(ICON_MDI_COGS);
	{
		setting.ClickedEvent += [&assetSetting]() { assetSetting.OpenPopup(); };
		setting.lineBreak = false;
	}

	auto& searchBar = CreateWidget<FRInputText>("");
	{
		searchBar.ContentChangedEvent += [this](const std::string& pContent)
			{

			};
	}

	auto& backButton = CreateWidget<FRButton>(ICON_MDI_ARROW_LEFT_CIRCLE_OUTLINE);
	{
		backButton.lineBreak = false;
	}

	auto& frontButton = CreateWidget<FRButton>(ICON_MDI_ARROW_RIGHT_CIRCLE_OUTLINE);
	{

	}

	CreateWidget<FRSeparator>();

	auto& tableView = CreateWidget<FRTableView>("TableView", true, 2, glm::vec2{}, glm::vec2{}, ETableViewLayout::Horizontal);
	{
		tableView.resizable = true;
	}

	auto& assets = tableView.CreateWidget<FRTableView>("Assets", true, 1, glm::vec2{}, glm::vec2{}, ETableViewLayout::Horizontal);
	{
		assets.scrollY = true;
		mAssetList = &assets;
	}

	auto cellSize = glm::vec2{ 120.f * mItemScale / 100.f, 200.f * mItemScale / 100.f };
	auto& items = tableView.CreateWidget<FRTableView>("Items", false, 1, cellSize, glm::vec2{ 1.f, 1.f }, ETableViewLayout::Horizontal);
	{
		items.scrollY = true;
		items.padOuterX = true;
		items.sizingFixedFit = true;
		items.sizeType = EWidgetSizeType::RELATIVE;
		mAssetView = &items;
	}
	
	ConsiderItem(nullptr, mEngineFolder, true);
	ConsiderItem(nullptr, mProjectFolder, false);
}

void FR::FRAssetBrowser::Refresh()
{
	mAssetList->RemoveAllWidgets();
	mAssetView->RemoveAllWidgets();

	ConsiderItem(nullptr, mEngineFolder, true);
	ConsiderItem(nullptr, mProjectFolder, false);
}

void FR::FRAssetBrowser::ParseFolder(FRWidgetContainer& pRoot, const std::string& pDirectory, bool pIsEngineItem)
{
	std::vector<std::filesystem::directory_entry> tempFile;
	std::vector<std::filesystem::directory_entry> tempDirectory;
	for (auto& item : std::filesystem::directory_iterator(pDirectory))
	{
		if (!item.is_directory())
		{
			tempFile.push_back(item);
		}
		else
		{
			tempDirectory.push_back(item);
		}
	}

	for (auto& item : tempDirectory)
	{
		ConsiderItem(&pRoot, item.path().string(), pIsEngineItem, false);
		RenderItemBody(nullptr, item.path().string(), pIsEngineItem, false);
	}

	for (auto& item : tempFile)
	{
		ConsiderItem(&pRoot, item.path().string(), pIsEngineItem, false);
		RenderItemBody(nullptr, item.path().string(), pIsEngineItem, false);
	}
}

void FR::FRAssetBrowser::ConsiderItem(FRWidgetContainer* pRoot, const std::string& pDirectory, bool pIsEngineItem, bool pAutoOpen)
{
	auto path = utils::Path(pDirectory);
	std::string itemname = path.getName();

	bool protectedItem = !pRoot || pIsEngineItem;
	std::string resourceFormatPath = GetService(FREditorActions).GetResourcePath(path);

	EFileType fileType = FRPathUtils::GetFileType(itemname);
	if (fileType == EFileType::NONE && !path.isDirectory())
	{
		return;
	}

	auto& itemGroup = pRoot ? pRoot->CreateWidget<FRGroup>() : mAssetList->CreateWidget<FRGroup>();

	if (path.isDirectory())
	{
		//ICON_MDI_FOLDER_OPEN: ICON_MDI_FOLDER;
		auto& treeNode = itemGroup.CreateWidget<FRTreeNode>(itemname, ICON_MDI_FOLDER_OPEN, ICON_MDI_FOLDER);
		{
			if (pAutoOpen)
			{
				treeNode.Open();
			}
		}

		treeNode.AddPlugin<FRPluginSource<GroupPair>>("Folder", resourceFormatPath, std::make_pair(resourceFormatPath, &itemGroup));

		if (!pRoot)
		{
			treeNode.RemoveAllPlugins();
		}

		auto& contextMenu = treeNode.AddPlugin<FolderItemMenu>(path, protectedItem && resourceFormatPath != "");
		{
			contextMenu.userData = static_cast<void*>(&treeNode);
			contextMenu.ItemAddedEvent += [this, &treeNode, path, pIsEngineItem](std::string pString)
				{
					treeNode.Open();
					treeNode.RemoveAllWidgets();
					ParseFolder(treeNode, FRPathUtils::GetContainingFolder(pString), pIsEngineItem);
				};
		}

		if (!pIsEngineItem)
		{
			treeNode.AddPlugin<FRPluginTarget<GroupPair>>("Folder").DataReceivedEvent += [this, &treeNode, path, pIsEngineItem](GroupPair pData)
				{
					if (!pData.first.empty())
					{
						std::string folderReceivedPath = FRPathUtils::GetRealPath(pData.first);
						std::string folderName = FRPathUtils::GetElementName(folderReceivedPath) + '\\';
						std::string correctPath = mPathUpdate.find(&treeNode) != mPathUpdate.end() ? mPathUpdate[&treeNode] : path.getPath();
						std::string newPath = correctPath + folderName;

						std::string prevPath = folderReceivedPath;
						if (!(newPath.find(prevPath) != std::string::npos) || prevPath == newPath)
						{
							if (!std::filesystem::exists(newPath))
							{
								bool isEngineFolder = pData.first[0] == ':';

								if (isEngineFolder)
								{
									std::filesystem::copy(prevPath, newPath, std::filesystem::copy_options::recursive);
								}
								else
								{
									RenameAsset(prevPath, newPath);
								}

								treeNode.Open();
								treeNode.RemoveAllWidgets();
								ParseFolder(treeNode, correctPath, pIsEngineItem);

								if (!isEngineFolder)
								{
									pData.second->Destroy();
								}
							}
							else if (prevPath == newPath)
							{
								// Ignore
							}
						}
					}
				};

			treeNode.AddPlugin<FRPluginTarget<GroupPair>>("File").DataReceivedEvent += [this, &treeNode, path, pIsEngineItem](GroupPair pData)
				{
					if (!pData.first.empty())
					{
						std::string fileReceivedPath = FRPathUtils::GetRealPath(pData.first);
						std::string fileName = FRPathUtils::GetElementName(fileReceivedPath);
						std::string correctPath = mPathUpdate.find(&treeNode) != mPathUpdate.end() ? mPathUpdate[&treeNode] : path.getPath();
						std::string newPath = correctPath + fileName;

						std::string prevPath = fileReceivedPath;
						if (!std::filesystem::exists(newPath))
						{
							bool isEngineFile = pData.first[0] == ':';

							if (isEngineFile)
							{
								std::filesystem::copy_file(prevPath, newPath);
							}
							else
							{
								RenameAsset(prevPath, newPath);
							}

							treeNode.Open();
							treeNode.RemoveAllWidgets();
							ParseFolder(treeNode, correctPath, pIsEngineItem);

							if (!isEngineFile)
							{
								pData.second->Destroy();
							}
						}
						else if (prevPath == newPath)
						{
							// Ignore
						}
					}
				};

			contextMenu.DestroyedEvent += [&itemGroup](std::string pDeletedPath) { itemGroup.Destroy(); };

			contextMenu.ItemAddedEvent += [this, &treeNode, pIsEngineItem](std::string pPath)
				{
					treeNode.RemoveAllWidgets();
					ParseFolder(treeNode, FRPathUtils::GetContainingFolder(pPath), pIsEngineItem);
				};

		}

		contextMenu.CreateList();

		treeNode.OpenedEvent += [this, &treeNode, path, pIsEngineItem]
			{
				treeNode.RemoveAllWidgets();
				mAssetView->RemoveAllWidgets();
				std::string updatedPath = FRPathUtils::GetContainingFolder(path) + treeNode.name;
				ParseFolder(treeNode, updatedPath, pIsEngineItem);
			};

		treeNode.ClosedEvent += [this, &treeNode] { treeNode.RemoveAllWidgets(); };
	}
	else
	{
		auto& clickableText = itemGroup.CreateWidget<FRTextClickable>(itemname);

		FileItemMenu* contextMenu = nullptr;

		switch (fileType)
		{
			case EFileType::MODEL:
				contextMenu = &clickableText.AddPlugin<ModelMenu>(path, protectedItem);
				break;
			case EFileType::TEXTURE:
				contextMenu = &clickableText.AddPlugin<TextureMenu>(path, protectedItem);
				break;
			case EFileType::SHADER:
				contextMenu = &clickableText.AddPlugin<ShaderMenu>(path, protectedItem);
				break;
			case EFileType::MATERIAL:
				contextMenu = &clickableText.AddPlugin<MaterialMenu>(path, protectedItem);
				break;
			case EFileType::SCENE:
				contextMenu = &clickableText.AddPlugin<SceneMenu>(path, protectedItem);
				break;
			case EFileType::ANIMATION:
				contextMenu = &clickableText.AddPlugin<AnimationMenu>(path, protectedItem);
				break;
			case EFileType::OZZMODEL:
				contextMenu = &clickableText.AddPlugin<AnimationMenu>(path, protectedItem);
				break;
			default:
				contextMenu = &clickableText.AddPlugin<FileItemMenu>(path, protectedItem);
				break;
		}

		contextMenu->CreateList();

		contextMenu->DestroyedEvent += [&itemGroup](std::string pDeletedPath) { itemGroup.Destroy(); };

		clickableText.AddPlugin<FRPluginSource<GroupPair>>("File", resourceFormatPath, std::make_pair(resourceFormatPath, &itemGroup));

		if (fileType == EFileType::TEXTURE)
		{
			auto& texturePreview = clickableText.AddPlugin<TexturePreview>();
			texturePreview.SetTexturePreview(resourceFormatPath);
		}
	}
}

void FR::FRAssetBrowser::RenderItemBody(FRWidgetContainer* pRoot, const std::string& pDirectory, bool pIsEngineItem, bool pAutoOpen)
{
	auto path = utils::Path(pDirectory);
	std::string itemname = path.getName();

	bool protectedItem = !pRoot || pIsEngineItem;
	std::string resourceFormatPath = GetService(FREditorActions).GetResourcePath(path);

	EFileType fileType = FRPathUtils::GetFileType(itemname);
	if (fileType == EFileType::NONE && !path.isDirectory())
	{
		return;
	}

	auto& itemGroup = pRoot ? pRoot->CreateWidget<FRGroup>() : mAssetView->CreateWidget<FRGroup>();

	if (path.isDirectory())
	{
		auto backgroundTexture = FRApplication::EditorResources()->GetTexture("DarkBackground_Texture");
		auto directoryIcon = FRApplication::EditorResources()->GetTexture("DirectoryIcon_Texture");
		auto emptyTexture = FRApplication::EditorResources()->GetTexture("Empty_Texture");

		auto& fileItem = itemGroup.CreateWidget<FRFileItem>(itemname, glm::vec2{ 120.f, 200.f }, true, mItemScale, backgroundTexture, directoryIcon, emptyTexture);

		fileItem.AddPlugin<FRPluginSource<GroupPair>>("Folder", resourceFormatPath, std::make_pair(resourceFormatPath, &itemGroup));

		if (!pRoot)
		{
			fileItem.RemoveAllPlugins();
		}

		auto& contextMenu = fileItem.AddPlugin<FolderItemMenu>(path, protectedItem && resourceFormatPath != "");
		{
			contextMenu.userData = static_cast<void*>(&fileItem);
			contextMenu.ItemAddedEvent += [this, &fileItem, path, pIsEngineItem](std::string pString)
				{
					mAssetView->RemoveAllWidgets();
					ParseFolder(*mAssetView, FRPathUtils::GetContainingFolder(pString), pIsEngineItem);
				};
		}

		if (!pIsEngineItem)
		{
			fileItem.AddPlugin<FRPluginTarget<GroupPair>>("Folder").DataReceivedEvent += [this, &fileItem, path, pIsEngineItem](GroupPair pData)
				{
					if (!pData.first.empty())
					{
						std::string folderReceivedPath = FRPathUtils::GetRealPath(pData.first);
						std::string folderName = FRPathUtils::GetElementName(folderReceivedPath) + '\\';
						std::string correctPath = mPathUpdate.find(&fileItem) != mPathUpdate.end() ? mPathUpdate[&fileItem] : path.getPath();
						std::string newPath = correctPath + folderName;

						std::string prevPath = folderReceivedPath;
						if (!(newPath.find(prevPath) != std::string::npos) || prevPath == newPath)
						{
							if (!std::filesystem::exists(newPath))
							{
								bool isEngineFolder = pData.first[0] == ':';

								if (isEngineFolder)
								{
									std::filesystem::copy(prevPath, newPath, std::filesystem::copy_options::recursive);
								}
								else
								{
									RenameAsset(prevPath, newPath);
								}

								//treeNode.Open();
								//treeNode.RemoveAllWidgets();
								//ParseFolder(treeNode, std::filesystem::directory_entry(correctPath), pIsEngineItem);

								if (!isEngineFolder)
								{
									pData.second->Destroy();
								}
							}
							else if (prevPath == newPath)
							{
								// Ignore
							}
						}
					}
				};

			fileItem.AddPlugin<FRPluginTarget<GroupPair>>("File").DataReceivedEvent += [this, &fileItem, path, pIsEngineItem](GroupPair pData)
				{
					if (!pData.first.empty())
					{
						std::string fileReceivedPath = FRPathUtils::GetRealPath(pData.first);

						std::string fileName = FRPathUtils::GetElementName(fileReceivedPath);
						std::string correctPath = mPathUpdate.find(&fileItem) != mPathUpdate.end() ? mPathUpdate[&fileItem] : path.getPath();
						std::string newPath = correctPath + fileName;

						std::string prevPath = fileReceivedPath;
						if (!std::filesystem::exists(newPath))
						{
							bool isEngineFile = pData.first[0] == ':';

							if (isEngineFile)
							{
								std::filesystem::copy_file(prevPath, newPath);
							}
							else
							{
								RenameAsset(prevPath, newPath);
							}

							//treeNode.Open();
							//treeNode.RemoveAllWidgets();
							//ParseFolder(treeNode, std::filesystem::directory_entry(correctPath), pIsEngineItem);

							if (!isEngineFile)
							{
								pData.second->Destroy();
							}
						}
						else if (prevPath == newPath)
						{
							// Ignore
						}
					}
				};

			contextMenu.DestroyedEvent += [&itemGroup](std::string pDeletedPath) { itemGroup.Destroy(); };

			contextMenu.ItemAddedEvent += [this, &fileItem, pIsEngineItem](std::string pPath)
				{
					mAssetView->RemoveAllWidgets();
					ParseFolder(*mAssetView, FRPathUtils::GetContainingFolder(pPath), pIsEngineItem);
				};
		}

		contextMenu.CreateList();

		fileItem.OpenedEvent += [this, &fileItem, path, pIsEngineItem]
			{
				mAssetView->RemoveAllWidgets();
				std::string updatedPath = FRPathUtils::GetContainingFolder(path) + fileItem.name;
				ParseFolder(*mAssetView, updatedPath, pIsEngineItem);
			};
	}
	else
	{
		auto backgroundTexture = FRApplication::EditorResources()->GetTexture("DarkBackground_Texture");
		auto fileIconTexture = FRApplication::EditorResources()->GetTexture("FileIcon_Texture");
		auto emptyTexture = FRApplication::EditorResources()->GetTexture("Empty_Texture");
		
		auto& fileItem = itemGroup.CreateWidget<FRFileItem>(itemname, glm::vec2{ 120.f, 200.f }, true, mItemScale, backgroundTexture, fileIconTexture, emptyTexture);

		FileItemMenu* contextMenu = nullptr;

		switch (fileType)
		{
		case EFileType::SCENE:
			contextMenu = &fileItem.AddPlugin<SceneMenu>(path, protectedItem);
			break;
		case EFileType::MODEL:
			contextMenu = &fileItem.AddPlugin<ModelMenu>(path, protectedItem);
			break;
		case EFileType::SHADER:
			contextMenu = &fileItem.AddPlugin<ShaderMenu>(path, protectedItem);
			break;
		case EFileType::TEXTURE:
			contextMenu = &fileItem.AddPlugin<TextureMenu>(path, protectedItem);
			break;
		case EFileType::MATERIAL:
			contextMenu = &fileItem.AddPlugin<MaterialMenu>(path, protectedItem);
			break;
		default:
			contextMenu = &fileItem.AddPlugin<FileItemMenu>(path, protectedItem);
			break;
		}

		contextMenu->CreateList();

		contextMenu->DestroyedEvent += [&itemGroup](std::string pDeletedPath) { itemGroup.Destroy(); };

		fileItem.AddPlugin<FRPluginSource<GroupPair>>("File", resourceFormatPath, std::make_pair(resourceFormatPath, &itemGroup));

		if (fileType == EFileType::TEXTURE)
		{
			auto& texturePreview = fileItem.AddPlugin<TexturePreview>();
			texturePreview.SetTexturePreview(resourceFormatPath);
		}
	}
}
