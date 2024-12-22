#pragma once

#include "FRPtrValue.h"
#include <filament/IndirectLight.h>

namespace FR
{
	class FRIndirectLightWarp
	{
	public:
		FRIndirectLightWarp() = default;

		filament::IndirectLight* Value()
		{
			return mValue.value();
		}

	private:
		FRPtrValue<filament::IndirectLight> mValue;

	};
}

