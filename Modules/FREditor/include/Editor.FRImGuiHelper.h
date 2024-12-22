#pragma once

#include <vector>
#include <unordered_map>

#include "Window.h"
#include <GUI.FRCanvas.h>
#include <Tools.FRMessage.h>

#include <SDL.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <utils/Entity.h>

#include <FREntityWarp.h>
#include <FRTextureSamplerWarp.h>

namespace FR
{
	class Window;

	class FRViewWarp;
	class FRSceneWarp;
	class FRCameraWarp;
	class FREngineWarp;
	class FRTextureWarp;
	class FRRendererWarp;
	class FRIndexBufferWarp;
	class FRVertexBufferWarp;
	class FRMaterialWarp;
	class FRMaterialInstanceWarp;

	class FRImGuiHelper
	{
	public:

		enum class ETheme : uint8_t
		{
			Dark,
		};

		FRImGuiHelper(const Window::Settings& pSetting, ETheme pTheme = ETheme::Dark);

		void Update();

		void Render();

		void SetDisplaySize(int pWidth, int pHeight, float pScaleX = 1.f, float pScaleY = 1.f, bool pFlipVertical = false);

		void ProcessEvent(SDL_Event event);

		void CreateAtlasTexture(FREngineWarp* pEngine);

		bool LoadFont(const std::string& pID, const std::string& pPath, float pFontSize);

		bool UnLoadFont(const std::string& pID);

		bool UseFont(const std::string& pID);

		void UseDefaultFont();

		void EnableEditorLayoutSave(bool pValue);

		bool IsEditorLayoutSaveEnabled() const;

		void SetEditorLayoutSaveFilename(const std::string& pFilename);

		void SetEditorLayoutAutosaveFrequency(float pFrequency);

		float GetEditorLayoutAutosaveFrequency(float pFrequeny);

		void EnableDocking(bool pValue);

		bool IsDockingEnabled();

		void ResetLayout(const std::string& pConfig);

		void SetTheme(ETheme pTheme);

		bool ShouldClose();

		void SetShouldClose(bool pValue);

		Window* GetWindow();

		glm::vec2 GetWindowPosition();

		glm::vec2 GetMousePositionRelativeToWindow();

		template<typename T, typename... Args>
		inline void AddPanel(const std::string& pTitle, Args&&... pArgs);

		template<typename T>
		T* GetPanel();

		//
		static glm::vec2 GetIconFontSize();

	private:
		void SyncThreads();
		void CreateBuffers(int pNumRequiredBuffers);
		void CreateIndexBuffer(size_t pBufferIndex, size_t pCapacity);
		void CreateVertexBuffer(size_t pBufferIndex, size_t pCapacity);
		void ProcessImGuiCommands(ImDrawData* pCommands, const ImGuiIO& pIO);
		void PopulateVertexData(size_t pBufferIndex, size_t pVBSizeInBytes, void* pVBData, size_t pIBSizeInBytes, void* pIBData);

		void DarkTheme();

	public:
		~FRImGuiHelper();

	private:
		FRViewWarp* mUIView{ nullptr };
		FRSceneWarp* mUIScene{ nullptr };
		FRCameraWarp* mUICamera{ nullptr };
		FREngineWarp* mEngine{ nullptr };

		std::unique_ptr<Window> mWindow{ nullptr };

		bool mHasSynced{ false };
		ImGuiContext* mImGuiContext{ nullptr };

		std::vector<FRIndexBufferWarp*> mIndexBuffers;
		std::vector<FRVertexBufferWarp*> mVertexBuffers;

		FRMaterialWarp* mMaterial2d{ nullptr };
		FRMaterialWarp* mMaterialExternal{ nullptr };

		std::vector<FRMaterialInstanceWarp*> mMaterial2dInstances;
		std::vector<FRMaterialInstanceWarp*> mMaterialExternalInstances;

		FRTextureWarp* mTexture{ nullptr };
		
		FREntityWarp* mCameraEntity{ nullptr };
		FREntityWarp* mRenderable{ nullptr };
		FRTextureSamplerWarp mSampler{};

		bool mFlipVertical{ false };

		GUI::FRCanvas mCanvas;

		std::unordered_map<size_t, std::shared_ptr<GUI::FRAPanel>> mPanels;

		bool mDockingState{ false };
		std::string mLayoutSaveFilename{ "imgui.ini" };
		std::unordered_map<std::string, ImFont*> mFonts;

		FRMessage::ListenerID mListenerID;

	};
}

#include "Editor.FRImGuiHelper.inl"