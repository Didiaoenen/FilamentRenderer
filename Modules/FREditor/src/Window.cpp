#include "Window.h"

#include "Editor.FRInput.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <Tools.FRMessage.h>

namespace FR
{
	FR::Window* FR::Window::sWindow = nullptr;
}

FR::Window::Window(const Settings& pSetting)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		return;
	}

	const int x = SDL_WINDOWPOS_CENTERED;
	const int y = SDL_WINDOWPOS_CENTERED;

	//
	uint32_t flags = /*SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | */SDL_WINDOW_SHOWN;
	mWindow = SDL_CreateWindow(pSetting.title.c_str(), x, y, pSetting.width, pSetting.height, flags);
	mRawWindow = CreateRawWindow(mWindow);
}

void FR::Window::SetTitle(const std::string& pTitle)
{
	SDL_SetWindowTitle(mWindow, pTitle.c_str());
}

void FR::Window::SetIcon(const std::string& pFilePath)
{
	//SDL_SetWindowIcon(mWindow, );
}

void FR::Window::SetSize(const glm::vec2& pSize)
{
	SDL_SetWindowSize(mWindow, pSize.x, pSize.y);
}

void FR::Window::SetPosition(const glm::vec2& pPosition)
{
	SDL_SetWindowPosition(mWindow, pPosition.x, pPosition.y);
}

void FR::Window::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.windowID == SDL_GetWindowID(mWindow))
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					mShouldClose = true;
					break;
				default:
					break;
				}
			}
		}

		FRMessage::Invoke<SDL_Event>(EventType::SDL, event);
	}
}

void FR::Window::Show()
{
	SDL_ShowWindow(mWindow);
}

void FR::Window::Hide()
{
	SDL_HideWindow(mWindow);
}

void FR::Window::Focus()
{
	SDL_RaiseWindow(mWindow);
}

void FR::Window::Minimize()
{
	SDL_MinimizeWindow(mWindow);
}

void FR::Window::Maximize()
{
	SDL_MaximizeWindow(mWindow);
}

void FR::Window::FullScreen()
{
	SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
}

bool FR::Window::IsFullScreen()
{
	return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_FULLSCREEN;
}

bool FR::Window::IsHidden()
{
	return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_HIDDEN;
}

bool FR::Window::IsVisible()
{
	return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_SHOWN;
}

bool FR::Window::IsFocused()
{
	return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_INPUT_FOCUS || SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MOUSE_FOCUS;
}

bool FR::Window::IsMinimized()
{
	return SDL_GetWindowFlags(mWindow)& SDL_WINDOW_MINIMIZED;
}

bool FR::Window::IsMaximized()
{
	return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MAXIMIZED;
}

bool FR::Window::ShouldClose()
{
	return mShouldClose;
}

void FR::Window::SetShouldClose(bool pValue)
{
	mShouldClose = pValue;
}

glm::vec2 FR::Window::GetMousePositionRelativeToWindow()
{
	int x = 0, y = 0;
	SDL_GetWindowPosition(mWindow, &x, &y);
	return { FRInput::GetMousePosition().x - x, FRInput::GetMousePosition().y - y};
}

glm::vec2 FR::Window::GetWindowPosition()
{
	int x = 0, y = 0;
	SDL_GetWindowPosition(mWindow, &x, &y);
	return { x, y };
}

void FR::Window::Restore()
{
	SDL_RestoreWindow(mWindow);
}

glm::vec2 FR::Window::GetSize()
{
	int width = 0, height = 0;
	SDL_GetWindowSize(mWindow, &width, &height);
	return { width, height };
}

void* FR::Window::GetRawWindow()
{
	return mRawWindow;
}

SDL_Window* FR::Window::GetSDLWindow()
{
	return mWindow;
}

void* FR::Window::CreateRawWindow(SDL_Window* pWindow)
{
	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	SDL_GetWindowWMInfo(pWindow, &wmi);
	HWND win = (HWND)wmi.info.win.window;
	return static_cast<void*>(win);
}

FR::Window::~Window()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}