#pragma once

#include <array>
#include <glm/glm.hpp>
#include <SDL_events.h>
#include <Tools.FRMessage.h>

#include "EKeyCode.h"

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
		static bool mCursorVisible;
		static glm::vec2 mMouseDelta;
		static glm::vec2 mMousePosition;
		static glm::vec2 mMouseWheelDelta;

	};
}

