#pragma once

#include "FRRefWarp.h"
#include <utils/JobSystem.h>

namespace FR
{
	class FREngineWarp;

	class FRJobSystemWarp
		: public FRRefWarp<utils::JobSystem>
	{
	public:
		FRJobSystemWarp() = default;

		FRJobSystemWarp(FREngineWarp* pEngine);

	private:

	};
}

