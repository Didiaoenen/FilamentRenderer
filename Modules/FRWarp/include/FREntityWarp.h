#pragma once

#include "FRObjWarp.h"
#include <utils/Entity.h>

namespace FR
{
	class FREntityManagerWarp;

	class FREntityWarp
		: public FRObjWarp<utils::Entity>
	{
	public:
		FREntityWarp() = default;

		FREntityWarp(FREntityManagerWarp* pEntityManager);

	public:
		virtual ~FREntityWarp();

	};
}

