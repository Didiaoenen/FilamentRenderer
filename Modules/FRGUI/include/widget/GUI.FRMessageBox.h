#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRMessageBox
		: public FRAWidget
	{
	public:
		FRMessageBox(const std::string& pName);

		void InitMessageBox(const std::string& pTitle, const std::string& pContext, std::vector<std::string> pCaptions);

		void OpenMessageBox();

		bool IsInited();

	protected:
		void _Draw_Impl() override;

	private:
		std::string mTitle;

		std::string mContext;

		std::vector<std::string> mCaptions;

		bool mInited{ false };

		FREvent<int> ClickedEvent;

	};
}

