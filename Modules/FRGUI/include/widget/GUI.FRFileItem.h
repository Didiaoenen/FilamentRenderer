#pragma once

#include "GUI.FRAWidget.h"

namespace FR
{
	class FRTexture;
}

namespace FR::GUI
{
	class FRFileItem
		: public FRAWidget
	{
	public:
		FRFileItem(const std::string& pName, glm::vec2 pSize, bool pDirectory,
			int pScalePercent, FRTexture* pBackgroud, FRTexture* pThumbnail, FRTexture* pColorFrame);

		void _Draw_Impl() override;

	public:
		std::string name;
		int scalePercent{ 50 };
		bool directory{ false };
		FRTexture* backgroud{ nullptr };
		FRTexture* thumbnail{ nullptr };
		FRTexture* colorFrame{ nullptr };

		FREvent<> ClickedEvent;
		FREvent<> DoubleClickedEvent;

		FREvent<> OpenedEvent;
		FREvent<> ClosedEvent;

	};
}

