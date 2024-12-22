#pragma once

#include "Editor.FREditorActions.h"

namespace FR
{
	template<typename T>
	inline FRActor& FREditorActions::CreateMonoComponentActor(bool pFocusOnCreation, FRActor* pParent)
	{
		FRActor a;
		auto& instance = a;//CreateEmptyActor(false, pParent);

		T& component = instance.AddComponent<T>();

		instance.name = component.GetName();

		if (pFocusOnCreation)
		{
			SelectActor(instance);
		}

		return instance;
	}
}