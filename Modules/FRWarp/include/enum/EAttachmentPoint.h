#pragma once

#include <cstdint>

namespace FR
{
	enum class EAttachmentPoint : uint8_t
	{
		COLOR0 = 0,          //!< identifies the 1st color attachment
		COLOR1 = 1,          //!< identifies the 2nd color attachment
		COLOR2 = 2,          //!< identifies the 3rd color attachment
		COLOR3 = 3,          //!< identifies the 4th color attachment
		COLOR4 = 4,          //!< identifies the 5th color attachment
		COLOR5 = 5,          //!< identifies the 6th color attachment
		COLOR6 = 6,          //!< identifies the 7th color attachment
		COLOR7 = 7,          //!< identifies the 8th color attachment
		DEPTH = 8,			//!< identifies the depth attachment
		COLOR = COLOR0,     //!< identifies the 1st color attachment
	};
}