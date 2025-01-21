#pragma once

#include "GUI.FRAWidget.h"

namespace FR::GUI
{
	class FRAButton
		: public FRAWidget
	{
	public:
		FRAButton() = default;

	public:
		virtual ~FRAButton() = default;

	protected:
		void _Draw_Impl() override = 0;

	public:
		FREvent<> ClickedEvent;

	};

	class FRButton
		: public FRAButton
	{
	public:
		FRButton(const std::string& pLabel = "", const glm::vec2& pSize = {}, bool pDisabled = false, bool pAlignText = false);

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;

		bool disabled{ false };
		bool alignText{ false };
		
		Color textColor{};
		Color idleBackgroundColor{};
		Color hoveredBackgroundColor{};
		Color clickedBackgroundColor{};

	};

	class FRButtonArrow
		: public FRAButton
	{
	public:
		FRButtonArrow(ImGuiDir pDirection = ImGuiDir_None);

	protected:
		void _Draw_Impl() override;

	public:
		ImGuiDir direction;

	};

	class FRButtonColored
		: public FRAButton
	{
	public:
		FRButtonColored(const std::string& pLabel = "", const Color& pColor = {}, const glm::vec2& pSize = {}, bool pEnableAlpha = true);

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;
		bool enableAlpha{ false };

		Color color{};
	
	};

	class FRButtonImage
		: public FRAButton
	{
	public:
		FRButtonImage(void* pTextureID, const glm::vec2& pSize);

	protected:
		void _Draw_Impl() override;

	public:
		void* textureID{ nullptr };
		
		bool disabled{ false };

		Color tint = { 1, 1, 1, 1 };
		Color background = { 0, 0, 0, 0 };

	};

	class FRButtonSmall
		: public FRAButton
	{
	public:
		FRButtonSmall(const std::string& pLabel = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;

		Color textColor{};
		Color idleBackgroundColor{};
		Color hoveredBackgroundColor{};
		Color clickedBackgroundColor{};

	};

	class FRButtonInvisible
		: public FRAButton
	{
	public:
		FRButtonInvisible(const glm::vec2& pSize);

	protected:
		void _Draw_Impl() override;

	};
}

