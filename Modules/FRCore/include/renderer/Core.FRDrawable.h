#pragma once

#include <Tools.FROptRef.h>
#include "Core.FRDescribable.h"

namespace FR
{
	class FRMesh;
	class FRMaterial;

	struct FRDrawable
		: public FRDescribable
	{
		FROptRef<FRMesh> mesh;
		FROptRef<FRMaterial> material;
		//EPrimitiveMode primitiveMode = EPrimitiveMode::TRIANGLES;
	};
}