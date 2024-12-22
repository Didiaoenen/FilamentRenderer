#pragma once

#include <cstdint>

namespace FR::GUI
{
	enum class EWidgetSizeType : uint8_t
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