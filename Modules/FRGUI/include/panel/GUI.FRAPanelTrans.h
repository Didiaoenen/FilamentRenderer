#pragma once

#include "GUI.FRAPanel.h"
#include "EPanelAlignment.h"

namespace FR::GUI
{
	class FRAPanelTrans
		: public FRAPanel
	{
	public:
		FRAPanelTrans(const glm::vec2& pDefaultPosition = { -1.f, -1.f }, const glm::vec2& pDefaultSize = { -1.f, -1.f },
			EPanelHorizontal pDefaultHAlignment = EPanelHorizontal::LEFT,
			EPanelVertical pDefaultVAlignment = EPanelVertical::TOP,
			bool pIgnoreConfigFile = false);

		void SetPosition(const glm::vec2& pPosition);

		void SetSize(const glm::vec2& pSize);

		void SetAlignment(EPanelHorizontal pHAlignment, EPanelVertical pVAlignment);

		const glm::vec2& GetPosition() const;

		const glm::vec2& GetSize() const;

		EPanelHorizontal GetHorizontalAlignment() const;

		EPanelVertical GetVerticalAlignment() const;

	protected:
		void Update();

		virtual void _Draw_Impl() = 0;

	private:
		glm::vec2 CalculatePositionAlignmentOffset(bool pDefault = false);

		void UpdatePosition();

		void UpdateSize();

		void CopyImGuiPosition();

		void CopyImGuiSize();

	public:
		bool autoSize{ true };

	protected:
		glm::vec2 mDefaultSize;

		glm::vec2 mDefaultPosition;
		
		EPanelHorizontal mDefaultHAlignment;
		
		EPanelVertical mDefaultVAlignment;
		
		bool mIgnoreConfigFile{ false };

		glm::vec2 mSize{ 0.f };

		glm::vec2 mPosition{ 0.f };

		bool mSizeChanged{ false };

		bool mPositionChanged{ false };

		EPanelHorizontal mHAlignment{ EPanelHorizontal::LEFT };

		EPanelVertical mVAlignment{ EPanelVertical::TOP };
		
		bool mAlignmentChanged{ false };

		bool mFirstFrame{ true };
	};
}

