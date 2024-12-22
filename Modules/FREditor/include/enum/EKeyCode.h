#pragma once

#include <cstdint>

namespace FR
{
	enum class EKeyCode : uint8_t
	{
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
		Alpha0, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
		Keypad0, Keypad1, Keypad2, Keypad3, Keypad4, Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Esc,
		Tab,
		Space,
		CapsLock,
		Backspace,
		Enter,
		Delete,
		Home,
		End,
		Insert,
		PageUp, PageDown,
		AltLeft, AltRight,
		CtrlLeft, CtrlRight,
		ShiftLeft, ShiftRight,
		ArrowLeft, ArrowRight, ArrowUp, ArrowDown,

		ClickLeft, ClickRight, ClickMiddle,

		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		Back,
		Guide,
		Start,
		StickLeft,
		StickRight,
		ShoulderLeft,
		ShoulderRight,
		Misc1,
		Paddle1,
		Paddle2,
		Paddle3,
		Paddle4,
		Touchpad,
		Max,
	};
}