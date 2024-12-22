#pragma once

#include "Core.FRGuiDrawer.h"
#include "Core.FRISerializable.h"

namespace FR
{
	class FRComponent;

	class FRIInspectorItem
		: public FRISerializable
	{
	public:
		virtual void OnInspector(GUI::FRWidgetContainer& pRoot) = 0;

		virtual void OnInspector(FRComponent* pOwner, GUI::FRWidgetContainer& pRoot) {};
	};
}