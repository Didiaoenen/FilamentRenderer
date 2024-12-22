#include "Editor.FRInput.h"
#include "Window.h"

namespace FR
{
	using KeyCoreStates = std::array<bool, static_cast<uint32_t>(EKeyCode::Max)>;

	KeyCoreStates keyCodeStates;
	KeyCoreStates keyCodeFrameStates;
	FRMessage::ListenerID tListenerID = 0;

	bool FRInput::mCursorVisible = true;
	glm::vec2 FRInput::mMouseDelta = glm::vec2{ 0.f };
	glm::vec2 FRInput::mMousePosition = glm::vec2{ 0.f };
	glm::vec2 FRInput::mMouseWheelDelta = glm::vec2{ 0.f };
}

FR::FRInput::FRInput()
{
	keyCodeStates.fill(false);
	keyCodeFrameStates.fill(false);

	tListenerID = FRMessage::AddListener<FRInput, SDL_Event>(EventType::SDL, this, &FR::FRInput::OnEvent);
}

void FR::FRInput::Reset()
{
	keyCodeFrameStates = keyCodeStates;
	mMouseWheelDelta = glm::vec2{ 0.f };
}

void FR::FRInput::Update()
{
	PollMouse();
	PollKeyboard();
}

bool FR::FRInput::GetKeyDown(const EKeyCode pKey)
{
	return GetKey(pKey) && !keyCodeFrameStates[static_cast<uint32_t>(pKey)];
}

bool FR::FRInput::GetKeyUp(const EKeyCode pKey)
{
	return !GetKey(pKey) && keyCodeFrameStates[static_cast<uint32_t>(pKey)];
}

bool FR::FRInput::GetKey(const EKeyCode pKey)
{
	return keyCodeStates[static_cast<uint32_t>(pKey)];
}

void FR::FRInput::SetMouseCursorVisible(const bool visible)
{
	SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

void FR::FRInput::SetMousePosition(const glm::vec2& position)
{
	mMousePosition = position;
	SDL_WarpMouseGlobal(static_cast<int>(position.x), static_cast<int>(position.y));
}

bool FR::FRInput::GetMouseCursorVisible()
{
	return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}

const glm::vec2& FR::FRInput::GetMouseDelta()
{
	return mMouseDelta;
}

const glm::vec2& FR::FRInput::GetMousePosition()
{
	return mMousePosition;
}

const glm::vec2& FR::FRInput::GetMouseWheelDelta()
{
	return mMouseWheelDelta;
}

void FR::FRInput::PollMouse()
{
	int x = 0, y = 0;
	Uint32 keysStates = SDL_GetGlobalMouseState(&x, &y);

	glm::vec2 position = { static_cast<float>(x), static_cast<float>(y) };

	mMouseDelta = position - mMousePosition;

	mMousePosition = position;

	keyCodeStates[static_cast<uint32_t>(EKeyCode::ClickLeft)] = (keysStates & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ClickRight)] = (keysStates & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ClickMiddle)] = (keysStates & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
}

void FR::FRInput::PollKeyboard()
{
	const Uint8* keysStates = SDL_GetKeyboardState(nullptr);

	// Function
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F1)] = keysStates[SDL_SCANCODE_F1];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F2)] = keysStates[SDL_SCANCODE_F2];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F3)] = keysStates[SDL_SCANCODE_F3];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F4)] = keysStates[SDL_SCANCODE_F4];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F5)] = keysStates[SDL_SCANCODE_F5];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F6)] = keysStates[SDL_SCANCODE_F6];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F7)] = keysStates[SDL_SCANCODE_F7];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F8)] = keysStates[SDL_SCANCODE_F8];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F9)] = keysStates[SDL_SCANCODE_F9];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F10)] = keysStates[SDL_SCANCODE_F10];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F11)] = keysStates[SDL_SCANCODE_F11];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F12)] = keysStates[SDL_SCANCODE_F12];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F13)] = keysStates[SDL_SCANCODE_F13];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F14)] = keysStates[SDL_SCANCODE_F14];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F15)] = keysStates[SDL_SCANCODE_F15];

	// Numbers
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha0)] = keysStates[SDL_SCANCODE_0];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha1)] = keysStates[SDL_SCANCODE_1];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha2)] = keysStates[SDL_SCANCODE_2];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha3)] = keysStates[SDL_SCANCODE_3];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha4)] = keysStates[SDL_SCANCODE_4];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha5)] = keysStates[SDL_SCANCODE_5];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha6)] = keysStates[SDL_SCANCODE_6];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha7)] = keysStates[SDL_SCANCODE_7];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha8)] = keysStates[SDL_SCANCODE_8];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Alpha9)] = keysStates[SDL_SCANCODE_9];
	
	// Keypad
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad0)] = keysStates[SDL_SCANCODE_KP_0];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad1)] = keysStates[SDL_SCANCODE_KP_1];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad2)] = keysStates[SDL_SCANCODE_KP_2];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad3)] = keysStates[SDL_SCANCODE_KP_3];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad4)] = keysStates[SDL_SCANCODE_KP_4];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad5)] = keysStates[SDL_SCANCODE_KP_5];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad6)] = keysStates[SDL_SCANCODE_KP_6];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad7)] = keysStates[SDL_SCANCODE_KP_7];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad8)] = keysStates[SDL_SCANCODE_KP_8];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Keypad9)] = keysStates[SDL_SCANCODE_KP_9];
	
	// Letters
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Q)] = keysStates[SDL_SCANCODE_Q];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::W)] = keysStates[SDL_SCANCODE_W];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::E)] = keysStates[SDL_SCANCODE_E];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::R)] = keysStates[SDL_SCANCODE_R];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::T)] = keysStates[SDL_SCANCODE_T];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Y)] = keysStates[SDL_SCANCODE_Y];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::U)] = keysStates[SDL_SCANCODE_U];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::I)] = keysStates[SDL_SCANCODE_I];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::O)] = keysStates[SDL_SCANCODE_O];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::P)] = keysStates[SDL_SCANCODE_P];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::A)] = keysStates[SDL_SCANCODE_A];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::S)] = keysStates[SDL_SCANCODE_S];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::D)] = keysStates[SDL_SCANCODE_D];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::F)] = keysStates[SDL_SCANCODE_F];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::G)] = keysStates[SDL_SCANCODE_G];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::H)] = keysStates[SDL_SCANCODE_H];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::J)] = keysStates[SDL_SCANCODE_J];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::K)] = keysStates[SDL_SCANCODE_K];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::L)] = keysStates[SDL_SCANCODE_L];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Z)] = keysStates[SDL_SCANCODE_Z];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::X)] = keysStates[SDL_SCANCODE_X];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::C)] = keysStates[SDL_SCANCODE_C];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::V)] = keysStates[SDL_SCANCODE_V];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::B)] = keysStates[SDL_SCANCODE_B];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::N)] = keysStates[SDL_SCANCODE_N];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::M)] = keysStates[SDL_SCANCODE_M];
	
	// Controls
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Esc)] = keysStates[SDL_SCANCODE_ESCAPE];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Tab)] = keysStates[SDL_SCANCODE_TAB];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Space)] = keysStates[SDL_SCANCODE_SPACE];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::CapsLock)] = keysStates[SDL_SCANCODE_CAPSLOCK];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Backspace)] = keysStates[SDL_SCANCODE_BACKSPACE];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Enter)] = keysStates[SDL_SCANCODE_RETURN];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Delete)] = keysStates[SDL_SCANCODE_DELETE];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Home)] = keysStates[SDL_SCANCODE_HOME];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::End)] = keysStates[SDL_SCANCODE_END];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::Insert)] = keysStates[SDL_SCANCODE_INSERT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ShiftLeft)] = keysStates[SDL_SCANCODE_LSHIFT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ShiftRight)] = keysStates[SDL_SCANCODE_RSHIFT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::CtrlLeft)] = keysStates[SDL_SCANCODE_LCTRL];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::CtrlRight)] = keysStates[SDL_SCANCODE_RCTRL];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::AltLeft)] = keysStates[SDL_SCANCODE_LALT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::AltRight)] = keysStates[SDL_SCANCODE_RALT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::PageUp)] = keysStates[SDL_SCANCODE_PAGEUP];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::PageDown)] = keysStates[SDL_SCANCODE_PAGEDOWN];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ArrowLeft)] = keysStates[SDL_SCANCODE_LEFT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ArrowRight)] = keysStates[SDL_SCANCODE_RIGHT];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ArrowUp)] = keysStates[SDL_SCANCODE_UP];
	keyCodeStates[static_cast<uint32_t>(EKeyCode::ArrowDown)]  = keysStates[SDL_SCANCODE_DOWN];
}

void FR::FRInput::OnEvent(SDL_Event pEvent)
{
	Uint32 eventType = pEvent.type;
	if (eventType == SDL_MOUSEWHEEL)
	{
		OnEventMouse(pEvent);
	}
}

void FR::FRInput::OnEventMouse(SDL_Event pEvent)
{
	if (pEvent.type == SDL_MOUSEWHEEL)
	{
		if (pEvent.wheel.x > 0) mMouseWheelDelta.x += 1;
		if (pEvent.wheel.x < 0) mMouseWheelDelta.x -= 1;
		if (pEvent.wheel.y > 0) mMouseWheelDelta.y += 1;
		if (pEvent.wheel.y < 0) mMouseWheelDelta.y -= 1;
	}
}

FR::FRInput::~FRInput()
{
	FRMessage::RemoveListener(EventType::SDL, tListenerID);
}