#include "Editor.FRImGuiHelper.h"

#include <Window.h>
#include <FRViewWarp.h>
#include <FRSceneWarp.h>
#include <FRFenceWarp.h>
#include <FRCameraWarp.h>
#include <FREngineWarp.h>
#include <FRTextureWarp.h>
#include <FRMaterialWarp.h>
#include <FRRendererWarp.h>
#include <FRViewportWarp.h>
#include <FRIndexBufferWarp.h>
#include <FRVertexBufferWarp.h>
#include <FRMaterialInstanceWarp.h>
#include <FRBufferDescriptorWarp.h>
#include <FRPixelBufferDescriptorWarp.h>
#include <FRRenderableManagerWarp.h>
#include <FREntityManagerWarp.h>
#include <FRFilamentHelper.h>

#include <MathConvert.h>
#include <Tools.FRTimer.h>
#include <Tools.FRMessage.h>
#include <Tools.FRPathUtils.h>

#include <backends/imgui_impl_sdl2.h>

#include <utils/unwindows.h>
#include <utils/EntityManager.h>

#include <filagui_resources.h>
#include <IconsMaterialDesignIcons.h>

namespace FR
{
	class ImGuiScene
	{
	public:
		ImGuiScene()
		{
			mScene = FRFilamentHelper::CreateScene();
		}

	private:
		FRSceneWarp* mScene{ nullptr };

	};
}

FR::FRImGuiHelper::~FRImGuiHelper()
{
	mCanvas.RemoveAllPanels();

	mPanels.clear();

	mEngine->Destroy(mUIView);
	mEngine->Destroy(mUIScene);
	mEngine->Destroy(mRenderable);
	mEngine->Destroy(mCameraEntity);

	for (auto& mi : mMaterial2dInstances)
	{
		mEngine->Destroy(mi);
	}
	mEngine->Destroy(mMaterial2d);
	//mEngine->Destroy(mTexture);

	for (auto& vb : mVertexBuffers)
	{
		//mEngine->Destroy(vb);
	}
	for (auto& ib : mIndexBuffers)
	{
		//mEngine->Destroy(ib);
	}

	FRFilamentHelper::GetEntityManager()->Destroy(mRenderable);
	FRFilamentHelper::GetEntityManager()->Destroy(mCameraEntity);

	FRFilamentHelper::DestroyEngine();

	ImGui_ImplSDL2_Shutdown();

	ImGui::DestroyContext(mImGuiContext);
	mImGuiContext = nullptr;

	mWindow = nullptr;

	FRMessage::RemoveListener(EventType::SDL, mListenerID);
}

FR::FRImGuiHelper::FRImGuiHelper(const Window::Settings& pSetting, ETheme pTheme)
	: mImGuiContext(ImGui::CreateContext())
{
	mWindow = std::make_unique<Window>(pSetting);

	FRFilamentHelper::CreateEngine(mWindow->GetRawWindow());

	auto& io = ImGui::GetIO();
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	
	EnableDocking(false);

	mEngine = FRFilamentHelper::GetEngine();

	mUIView = mEngine->CreateView();
	mUIScene = mEngine->CreateScene();

	mCameraEntity = FRFilamentHelper::CreateEntity();
	mUICamera = mEngine->CreateCamera(mCameraEntity);
	
	mUIView->SetScene(mUIScene);
	mUIView->SetCamera(mUICamera);
	mUIView->SetBlendMode(FRViewWarp::EBlendMode::TRANSLUCENT);
	mUIView->SetShadowingEnabled(false);
	mUIView->SetPostProcessingEnabled(false);
	
	auto size = mWindow->GetSize();
	mUIView->SetViewport({ 0, 0, static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y) });
	mUICamera->SetProjection(FRCameraWarp::EProjection::ORTHO, 0.f, size.x, size.y, 0.f, 0.f, 1.f);

	mRenderable = FRFilamentHelper::CreateEntity();
	mUIScene->AddEntity(mRenderable);

	mMaterial2d = FRMaterialWarp::Builder()
		.Package(FILAGUI_RESOURCES_UIBLIT_DATA, FILAGUI_RESOURCES_UIBLIT_SIZE)
		.Build(mEngine);

	ImFontConfig config;
	config.MergeMode = true;
	config.PixelSnapH = true;
	config.GlyphMinAdvanceX = 16.0f;
	static const ImWchar iconsRanges[] = { ICON_MIN_MDI, ICON_MAX_MDI, 0 };

	io.Fonts->AddFontFromFileTTF("..\\..\\Resources\\Data\\Editor\\Fonts\\JetBrainsMono-Regular.ttf", 16.f);
	io.Fonts->AddFontFromFileTTF("..\\..\\Resources\\Data\\Editor\\Fonts\\MaterialdesignIcons-Webfont.ttf", 16.f, &config, iconsRanges);

	CreateAtlasTexture(mEngine);

	mSampler = FRTextureSamplerWarp(FRTextureSamplerWarp::EMinFilter::NEAREST, FRTextureSamplerWarp::EMagFilter::NEAREST);
	mMaterial2d->SetDefaultParameter("albedo", mTexture, mSampler);

	SetTheme(ETheme::Dark);

	SetDisplaySize(size.x, size.y);

	ImGui_ImplSDL2_InitForOther(mWindow->GetSDLWindow());

	mListenerID = FRMessage::AddListener<FRImGuiHelper, SDL_Event>(EventType::SDL, this, &FRImGuiHelper::ProcessEvent);
}

void FR::FRImGuiHelper::Update()
{
	mWindow->Update();

	{
		ImGui::SetCurrentContext(mImGuiContext);
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = FRTimer::GetDeltaTimeSec();

		mCanvas.Draw();

		ProcessImGuiCommands(ImGui::GetDrawData(), ImGui::GetIO());
	}
}

void FR::FRImGuiHelper::Render()
{
	FRFilamentHelper::GetRenderer()->Render(mUIView);
}

void FR::FRImGuiHelper::SetDisplaySize(int pWidth, int pHeight, float pScaleX, float pScaleY, bool pFlipVertical)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(pWidth, pHeight);
	io.DisplayFramebufferScale.x = pScaleX;
	io.DisplayFramebufferScale.y = pScaleY;
}

void FR::FRImGuiHelper::ProcessEvent(SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void FR::FRImGuiHelper::CreateAtlasTexture(FREngineWarp* pEngine)
{
	pEngine->Destroy(mTexture);
	ImGuiIO& io = ImGui::GetIO();

	static unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	size_t size = (size_t)(width * height * 4);
	FRPixelBufferDescriptorWarp pb(pixels, size, FRTextureWarp::EFormat::RGBA, FRTextureWarp::EType::UBYTE);
	mTexture = FRTextureWarp::Builder()
		.Width((uint32_t)width)
		.Height((uint32_t)height)
		.Levels((uint8_t)1)
		.Format(FRTextureWarp::EInternalFormat::RGBA8)
		.Sampler(FRTextureWarp::ESampler::SAMPLER_2D)
		.Build(pEngine);
	mTexture->SetImage(pEngine, 0, std::move(pb));

	mSampler = FRTextureSamplerWarp(FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR);
	mMaterial2d->SetDefaultParameter("albedo", mTexture, mSampler);
}

bool FR::FRImGuiHelper::LoadFont(const std::string& pID, const std::string& pPath, float pFontSize)
{
	if (mFonts.find(pID) == mFonts.end())
	{
		auto& io = ImGui::GetIO();
		ImFont* fontInstance = io.Fonts->AddFontFromFileTTF(pPath.c_str(), pFontSize);

		if (fontInstance)
		{
			mFonts[pID] = fontInstance;
			return true;
		}
	}
	return false;
}

bool FR::FRImGuiHelper::UnLoadFont(const std::string& pID)
{
	if (mFonts.find(pID) != mFonts.end())
	{
		mFonts.erase(pID);
		return true;
	}
	return false;
}

bool FR::FRImGuiHelper::UseFont(const std::string& pID)
{
	if (auto foundFont = mFonts.find(pID); foundFont != mFonts.end())
	{
		ImGui::GetIO().FontDefault = foundFont->second;
		return true;
	}
	return false;
}

void FR::FRImGuiHelper::UseDefaultFont()
{
	ImGui::GetIO().FontDefault = nullptr;
}

void FR::FRImGuiHelper::EnableEditorLayoutSave(bool pValue)
{
	if (pValue)
	{
		ImGui::GetIO().IniFilename = mLayoutSaveFilename.c_str();
	}
	else
	{
		ImGui::GetIO().IniFilename = nullptr;
	}
}

bool FR::FRImGuiHelper::IsEditorLayoutSaveEnabled() const
{
	return ImGui::GetIO().IniFilename != nullptr;
}

void FR::FRImGuiHelper::SetEditorLayoutSaveFilename(const std::string& pFilename)
{
	mLayoutSaveFilename = pFilename;
	if (IsEditorLayoutSaveEnabled())
	{
		ImGui::GetIO().IniFilename = mLayoutSaveFilename.c_str();
	}
}

void FR::FRImGuiHelper::SetEditorLayoutAutosaveFrequency(float pFrequency)
{
	ImGui::GetIO().IniSavingRate = pFrequency;
}

float FR::FRImGuiHelper::GetEditorLayoutAutosaveFrequency(float pFrequeny)
{
	return ImGui::GetIO().IniSavingRate;
}

void FR::FRImGuiHelper::EnableDocking(bool pValue)
{
	mDockingState = pValue;

	if (pValue)
	{
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}
	else
	{
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
	}
}

bool FR::FRImGuiHelper::IsDockingEnabled()
{
	return mDockingState;
}

void FR::FRImGuiHelper::ResetLayout(const std::string& pConfig)
{
	ImGui::LoadIniSettingsFromDisk(pConfig.c_str());
}

void FR::FRImGuiHelper::SetTheme(ETheme pTheme)
{
	switch (pTheme)
	{
	case FR::FRImGuiHelper::ETheme::Dark:
		DarkTheme();
		break;
	default:
		break;
	}
}

bool FR::FRImGuiHelper::ShouldClose()
{
	return mWindow->ShouldClose();
}

void FR::FRImGuiHelper::SetShouldClose(bool pValue)
{
	mWindow->SetShouldClose(pValue);
}

FR::Window* FR::FRImGuiHelper::GetWindow()
{
	return mWindow.get();
}

glm::vec2 FR::FRImGuiHelper::GetIconFontSize()
{
	return glm::vec2(22.f, 22.f);
}

glm::vec2 FR::FRImGuiHelper::GetWindowPosition()
{
	return mWindow->GetWindowPosition();
}

glm::vec2 FR::FRImGuiHelper::GetMousePositionRelativeToWindow()
{
	return mWindow->GetMousePositionRelativeToWindow();
}

void FR::FRImGuiHelper::SyncThreads()
{
#if UTILS_HAS_THREADING
	if (!mHasSynced) 
	{
		mHasSynced = true;
		FRFenceWarp::WaitAndDestroy(mEngine->CreateFence());
	}
#endif
}

void FR::FRImGuiHelper::CreateBuffers(int pNumRequiredBuffers)
{
	if (pNumRequiredBuffers > mVertexBuffers.size())
	{
		size_t previousSize = mVertexBuffers.size();
		mVertexBuffers.resize(pNumRequiredBuffers, nullptr);
		for (size_t i = previousSize; i < mVertexBuffers.size(); i++)
		{
			CreateVertexBuffer(i, 1000);
		}
	}
	if (pNumRequiredBuffers > mIndexBuffers.size())
	{
		size_t previousSize = mIndexBuffers.size();
		mIndexBuffers.resize(pNumRequiredBuffers, nullptr);
		for (size_t i = previousSize; i < mIndexBuffers.size(); i++)
		{
			CreateIndexBuffer(i, 5000);
		}
	}
}

void FR::FRImGuiHelper::CreateIndexBuffer(size_t pBufferIndex, size_t pCapacity)
{
	SyncThreads();
	mEngine->Destroy(mIndexBuffers[pBufferIndex]);
	mEngine->UnRegisterIndexBuffer(mIndexBuffers[pBufferIndex]);
	mIndexBuffers[pBufferIndex] = FRIndexBufferWarp::Builder()
		.IndexCount(pCapacity)
		.BufferType(FRIndexBufferWarp::EIndexType::USHORT)
		.Build(mEngine);
}

void FR::FRImGuiHelper::CreateVertexBuffer(size_t pBufferIndex, size_t pCapacity)
{
	SyncThreads();
	mEngine->Destroy(mVertexBuffers[pBufferIndex]);
	mEngine->UnRegisterVertexBuffer(mVertexBuffers[pBufferIndex]);
	mVertexBuffers[pBufferIndex] = FRVertexBufferWarp::Builder()
		.BufferCount(1)
		.VertexCount(pCapacity)
		.Attribute(FRVertexBufferWarp::EVertexAttribute::POSITION, 0, FRVertexBufferWarp::EAttributeType::FLOAT2, 0, sizeof(ImDrawVert))
		.Attribute(FRVertexBufferWarp::EVertexAttribute::UV0, 0, FRVertexBufferWarp::EAttributeType::FLOAT2, sizeof(glm::vec2), sizeof(ImDrawVert))
		.Attribute(FRVertexBufferWarp::EVertexAttribute::COLOR, 0, FRVertexBufferWarp::EAttributeType::UBYTE4, 2 * sizeof(glm::vec2), sizeof(ImDrawVert))
		.Normalized(FRVertexBufferWarp::EVertexAttribute::COLOR)
		.Build(mEngine);
}

void FR::FRImGuiHelper::ProcessImGuiCommands(ImDrawData* pCommands, const ImGuiIO& pIO)
{
	ImGui::SetCurrentContext(mImGuiContext);

	mHasSynced = false;
	auto rcm = mEngine->GetRenderableManager();

	int fbwidth = (int)(pIO.DisplaySize.x * pIO.DisplayFramebufferScale.x);
	int fbheight = (int)(pIO.DisplaySize.y * pIO.DisplayFramebufferScale.y);

	if (fbwidth == 0 || fbheight == 0)
	{
		return;
	}

	pCommands->ScaleClipRects(pIO.DisplayFramebufferScale);

	CreateBuffers(pCommands->CmdListsCount);

	size_t nPrims = 0;
	for (int cmdListIndex = 0; cmdListIndex < pCommands->CmdListsCount; cmdListIndex++)
	{
		const ImDrawList* cmds = pCommands->CmdLists[cmdListIndex];
		nPrims += cmds->CmdBuffer.size();
	}
	auto rbuilder = FRRenderableManagerWarp::Builder(nPrims);
	rbuilder.BoundingBox({ { 0, 0, 0 }, { 10000, 10000, 10000 } }).Culling(false);

	rcm->Destroy(mRenderable);

	int bufferIndex = 0;
	int primIndex = 0;
	int material2dIndex = 0;
	int materialExternalIndex = 0;
	for (int cmdListIndex = 0; cmdListIndex < pCommands->CmdListsCount; cmdListIndex++)
	{
		const ImDrawList* cmds = pCommands->CmdLists[cmdListIndex];
		PopulateVertexData(
			bufferIndex,
			cmds->VtxBuffer.Size * sizeof(ImDrawVert), cmds->VtxBuffer.Data,
			cmds->IdxBuffer.Size * sizeof(ImDrawIdx), cmds->IdxBuffer.Data);
		for (const auto& pcmd : cmds->CmdBuffer)
		{
			if (pcmd.UserCallback)
			{
				pcmd.UserCallback(cmds, &pcmd);
			}
			else
			{
				auto texture = (FRTextureWarp*)pcmd.TextureId;
				FRMaterialInstanceWarp* materialInstance;
				{
					if (material2dIndex == mMaterial2dInstances.size())
					{
						mMaterial2dInstances.push_back(mMaterial2d->CreateInstance());
					}
					materialInstance = mMaterial2dInstances[material2dIndex++];
				}
				materialInstance->SetScissor(
					std::max(pcmd.ClipRect.x, 0.f),
					std::max(fbheight - pcmd.ClipRect.w, 0.f),
					(uint16_t)(pcmd.ClipRect.z - pcmd.ClipRect.x),
					(uint16_t)(pcmd.ClipRect.w - pcmd.ClipRect.y));
				if (texture)
				{
					FRTextureSamplerWarp sampler(FRTextureSamplerWarp::EMinFilter::LINEAR, FRTextureSamplerWarp::EMagFilter::LINEAR);
					materialInstance->SetParameter("albedo", texture, sampler);
				}
				else
				{
					materialInstance->SetParameter("albedo", mTexture, mSampler);
				}
				rbuilder
					.Geometry(primIndex, FRRenderableManagerWarp::EPrimitiveType::TRIANGLES,
						mVertexBuffers[bufferIndex], mIndexBuffers[bufferIndex],
						pcmd.IdxOffset, pcmd.ElemCount)
					.BlendOrder(primIndex, primIndex)
					.Material(primIndex, materialInstance);
				primIndex++;
			}
		}
		bufferIndex++;
	}
	if (pCommands->CmdListsCount > 0)
	{
		rbuilder.Build(mEngine, mRenderable);
	}
}

void FR::FRImGuiHelper::PopulateVertexData(size_t pBufferIndex, size_t pVBSizeInBytes, void* pVBData, size_t pIBSizeInBytes, void* pIBData)
{
	size_t requiredVertCount = pVBSizeInBytes / sizeof(ImDrawVert);
	size_t capacityVertCount = mVertexBuffers[pBufferIndex]->GetVertexCount();
	if (requiredVertCount > capacityVertCount)
	{
		CreateVertexBuffer(pBufferIndex, requiredVertCount);
	}
	size_t nVbBytes = requiredVertCount * sizeof(ImDrawVert);
	void* vbFilamentData = malloc(nVbBytes);
	memcpy(vbFilamentData, pVBData, nVbBytes);
	mVertexBuffers[pBufferIndex]->SetBufferAt(mEngine, 0,
		FRBufferDescriptorWarp(vbFilamentData, nVbBytes,
			[](void* buffer, size_t size, void* user) {
				free(buffer);
			}, /* user = */ nullptr));

	size_t requiredIndexCount = pIBSizeInBytes / 2;
	size_t capacityIndexCount = mIndexBuffers[pBufferIndex]->GetIndexCount();
	if (requiredIndexCount > capacityIndexCount)
	{
		CreateIndexBuffer(pBufferIndex, requiredIndexCount);
	}
	size_t nIbBytes = requiredIndexCount * 2;
	void* ibFilamentData = malloc(nIbBytes);
	memcpy(ibFilamentData, pIBData, nIbBytes);
	mIndexBuffers[pBufferIndex]->SetBuffer(mEngine,
		FRBufferDescriptorWarp(ibFilamentData, nIbBytes,
			[](void* buffer, size_t size, void* user) {
				free(buffer);
			}, /* user = */ nullptr));
}

void FR::FRImGuiHelper::DarkTheme()
{
	ImGui::StyleColorsDark();

	auto& style = ImGui::GetStyle();
	
	style.FrameRounding = 3.0f;

	style.ScrollbarRounding = 12.0f;
	
	auto darkHeaderBG = ImVec4(62.0f / 255.0f, 62.0f / 255.0f, 62.0f / 255.0f, 255 / 255.0f);

	auto darkWindowBG = ImVec4(56.0f / 255.0f, 56.0f / 255.0f, 56.0f / 255.0f, 255 / 255.0f);

	auto darkMenuBarBG = ImVec4(25.0f / 255.0f, 25.0f / 255.0f, 25.0f / 255.0f, 255 / 255.0f);
	
	auto darkScrollbarBg = ImVec4(53.0f / 255.0f, 53.0f / 255.0f, 53.0f / 255.0f, 255 / 255.0f);

	auto darkTabActive = darkWindowBG;
	auto darkTabUnactive = ImVec4(40.0f / 255.0f, 40.0f / 255.0f, 40.0f / 255.0f, 255 / 255.0f);
	auto darkTabHovered = ImVec4(48.0f / 255.0f, 48.0f / 255.0f, 48.0f / 255.0f, 255 / 255.0f);

	auto darkButtonAtive = darkWindowBG;

	ImVec4* colors = style.Colors;

	//colors[ImGuiCol_Text] = ImVec4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);

	colors[ImGuiCol_WindowBg] = darkWindowBG;
	colors[ImGuiCol_ChildBg] = darkWindowBG;

	//colors[ImGuiCol_PopupBg] = ImVec4(42.0f / 255.0f, 38.0f / 255.0f, 47.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	//colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	//colors[ImGuiCol_FrameBg] = ImVec4(65.0f / 255.0f, 79.0f / 255.0f, 92.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
	//colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);

	colors[ImGuiCol_TitleBg] = darkTabUnactive;
	colors[ImGuiCol_TitleBgActive] = darkTabUnactive; 
	//colors[ImGuiCol_TitleBgCollapsed] = Titlebar;
	colors[ImGuiCol_MenuBarBg] = darkMenuBarBG;

	colors[ImGuiCol_ScrollbarBg] = darkScrollbarBg;
	//colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
	//colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.7f, 0.7f, 0.7f, 1.00f);
	//colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

	//colors[ImGuiCol_CheckMark] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_SliderGrab] = ImVec4(155.0f / 255.0f, 130.0f / 255.0f, 207.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_SliderGrabActive] = ImVec4(185.0f / 255.0f, 160.0f / 255.0f, 237.0f / 255.0f, 1.00f);
	//colors[ImGuiCol_Button] = darkButtonAtive;
	//colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	//colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);

	//colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	//colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	//colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);

	//colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	//colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	//colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);

	//colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	//colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	//colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	//colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	//colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	//colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	//colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	//colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	//colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	//colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	//colors[ImGuiCol_Header] = darkHeaderBG;
	//colors[ImGuiCol_HeaderHovered] = TabActive + ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
	//colors[ImGuiCol_HeaderActive] = TabActive + ImVec4(0.05f, 0.05f, 0.05f, 0.1f);

	colors[ImGuiCol_Tab] = darkTabUnactive;
	colors[ImGuiCol_TabActive] = darkTabActive;
	colors[ImGuiCol_TabHovered] = darkTabHovered;
	colors[ImGuiCol_TabUnfocused] = darkTabUnactive;
	colors[ImGuiCol_TabUnfocusedActive] = darkTabActive;
	colors[ImGuiCol_DockingEmptyBg] = darkTabActive;
	//colors[ImGuiCol_DockingPreview] = ImVec4(40.0f / 255.0f, 40.0f / 255.0f, 40.0f / 255.0f, 255.0f / 255.0f);
}
