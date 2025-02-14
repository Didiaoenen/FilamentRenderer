#pragma once

#include <string>
#include <glm/glm.hpp>

struct SDL_Window;

namespace FR
{
	class Window
	{
	public:

		struct Settings
		{
			std::string title;
			float width{ 0.f };
			float height{ 0.f };
		};

		Window(const Settings& pSetting);

		void SetTitle(const std::string& pTitle);

		void SetIcon(const std::string& pFilePath);

		void SetSize(const glm::vec2& pSize);

		void SetPosition(const glm::vec2& pPosition);

		void Update();

		void Show();
		void Hide();
		void Focus();
		void Minimize();
		void Maximize();
		void FullScreen();

		bool IsHidden();
		bool IsVisible();
		bool IsFocused();
		bool IsMinimized();
		bool IsMaximized();
		bool IsFullScreen();
		
		bool ShouldClose();
		void SetShouldClose(bool pValue);

		glm::vec2 GetWindowPosition();
		glm::vec2 GetMousePositionRelativeToWindow();

		void Restore();

		glm::vec2 GetSize();

		void* GetRawWindow();

		SDL_Window* GetSDLWindow();

	private:
		void* CreateRawWindow(SDL_Window* pWindow);

	public:
		~Window();

	private:
		inline static Window* sWindow{ nullptr };

		bool mShouldClose{ false };
		void* mRawWindow{ nullptr };
		SDL_Window* mWindow{ nullptr };

	};
}

