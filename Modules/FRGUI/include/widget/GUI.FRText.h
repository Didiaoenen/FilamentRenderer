#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	class FRText
		: public FRDataWidget<std::string>
	{
	public:
		FRText(const std::string& pContent = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string content;

	};

	class FRTextClickable
		: public FRText
	{
	public:
		FRTextClickable(const std::string& pContent = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		FREvent<> ClickedEvent;
		FREvent<> DoubleClickedEvent;

	};

	class FRTextColored
		: public FRText
	{
	public:
		FRTextColored(const std::string& pContent = "", const Color& pColor = {});

	public:
		Color color{};

	protected:
		virtual void _Draw_Impl() override;

	};

	class TextDisabled
		: public FRText
	{
	public:
		TextDisabled(const std::string& pContent = "");

	protected:
		virtual void _Draw_Impl() override;

	};

	class FRTextLabelled
		: public FRText
	{
	public:
		FRTextLabelled(const std::string& pContent = "", const std::string& pLabel = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string label;

	};

	class FRTextSelectable
		: public FRText
	{
	public:
		FRTextSelectable(const std::string& pContent = "", bool pSelected = false, bool pDisabled = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		bool selected{ false };
		bool disabled{ false };

		FREvent<> SelectedEvent;
		FREvent<> UnselectedEvent;
		FREvent<bool> ClickedEvent;

	};

	class FRTextWrapped
		: public FRText
	{
	public:
		FRTextWrapped(const std::string& pContent = "");

	protected:
		virtual void _Draw_Impl() override;

	};

	class FRTextClipped
		: public FRText
	{
	public:
		FRTextClipped(const std::string& pContent, void* pEnd, const glm::vec2& pMin, const glm::vec2& pMax,
			const glm::vec2* pTextSize, const glm::vec2& pAlign, const glm::vec4* pRect, float pWrapWidth);
	
	protected:
		virtual void _Draw_Impl() override;

	public:
		glm::vec2 min{};
		glm::vec2 max{};
		glm::vec2 align{};
		void* end{ nullptr };
		const glm::vec4* rect{ nullptr };
		const glm::vec2* textSize{ nullptr };
		float wrapWidth{ 0.f };

	};
}

