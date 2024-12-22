#pragma once

#include "Editor.FRImGuiHelper.h"
#include <GUI.FRPanelWindow.h>

namespace FR
{
	template<typename T, typename... Args>
	void FRImGuiHelper::AddPanel(const std::string& pTitle, Args&&... pArgs)
	{
		if constexpr (std::is_base_of<GUI::FRPanelWindow, T>::value)
		{
			mPanels.emplace(typeid(T).hash_code(), std::make_shared<T>(pTitle, std::forward<Args>(pArgs)...));
		}
		else
		{
			mPanels.emplace(typeid(T).hash_code(), std::make_shared<T>(std::forward<Args>(pArgs)...));
		}

		mCanvas.AddPanel(mPanels[typeid(T).hash_code()].get());
	}

	template<typename T>
	T* FRImGuiHelper::GetPanel()
	{
		return static_cast<T*>(mPanels[typeid(T).hash_code()].get());
	}
}