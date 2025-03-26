#pragma once


#include "EKeyCode.h"
#include <SDL_events.h>
#include <Tools.FRMessage.h>

#include <array>
#include <glm/glm.hpp>

namespace FR
{
	class FRInput
	{
	public:
		FRInput();

		void Reset();

		void Update();

		static bool GetKeyDown(const EKeyCode pKey);
		static bool GetKeyUp(const EKeyCode pKey);
		static bool GetKey(const EKeyCode pKey);

		static void SetMouseCursorVisible(const bool pVisible);
		static void SetMousePosition(const glm::vec2& pPosition);

		static bool GetMouseCursorVisible();
		static const glm::vec2& GetMouseDelta();
		static const glm::vec2& GetMousePosition();
		static const glm::vec2& GetMouseWheelDelta();

	private:
		void PollMouse();
		void PollKeyboard();

		void OnEvent(SDL_Event pEvent);
		void OnEventMouse(SDL_Event pEvent);

	public:
		~FRInput();

	private:
		inline static bool mCursorVisible{ true };
		inline static glm::vec2 mMouseDelta{ 0.f };
		inline static glm::vec2 mMousePosition{ 0.f };
		inline static glm::vec2 mMouseWheelDelta{ 0.f };

	};
}

