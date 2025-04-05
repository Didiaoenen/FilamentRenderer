#pragma once

#include <cstdint>

namespace FR::GUI
{
	enum class EWidgetSize : uint8_t
	{
		ABSOLUTE,
		RELATIVE,
	};

	enum class EWidgetAlignment : uint8_t
	{
		LEFT,
		CENTER,
		RIGHT,
	};
}