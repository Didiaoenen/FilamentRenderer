#pragma once

#include "GUI.FRAWidget.h"

namespace FR
{
	class FRTexture2D;
}

namespace FR::GUI
{
	class FRFileItem
		: public FRAWidget
	{
	public:
		FRFileItem(const std::string& pName, const glm::vec2& pSize, bool pDirectory,
			int pScalePercent, FRTexture2D* pBackgroud, FRTexture2D* pThumbnail, FRTexture2D* pColorFrame);

		void _Draw_Impl() override;

	public:
		std::string name;

		bool directory{ false };

		int scalePercent{ 50 };

		FRTexture2D* backgroud{ nullptr };
		FRTexture2D* thumbnail{ nullptr };
		FRTexture2D* colorFrame{ nullptr };

		FREvent<> OpenedEvent;
		FREvent<> ClosedEvent;

		FREvent<> ClickedEvent;
		FREvent<> DoubleClickedEvent;

	};
}

