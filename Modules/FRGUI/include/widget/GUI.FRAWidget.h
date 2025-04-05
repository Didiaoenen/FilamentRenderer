#pragma once

#include <Color.h>
#include <MathConvert.h>
#include <Tools.FREvent.h>
#include <IconsMaterialDesignIcons.h>

#include "EWidgetLayout.h"
#include "GUI.FRIDrawable.h"
#include "GUI.FRPluginable.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace FR::GUI
{
	class FRWidgetContainer;

	class FRAWidget
		: public FRPluginable, public FRIDrawable
	{
	public:
		FRAWidget(const std::string& pName = "");

		virtual void Draw() override;

		void Destroy();

		bool IsDestroyed();

		void LinkTo(const FRAWidget* pWidget);

		std::string GetWidgetID();

		glm::vec2 GetLabelSize();

	protected:
		virtual void _Draw_Impl() = 0;

		virtual void SetItemSize();

		virtual void SetItemAlign();

		virtual void SetItemLayout();

		virtual void DrawItemActivityOutline(
			const glm::vec2& pMin, const glm::vec2& pMax,
			bool pInActive = false, const Color& pActiveColor = { 80.0f, 80.0f, 80.0f });

		glm::vec2 CaculateSize();

	public:
		virtual ~FRAWidget() = default;

	public:
		std::string name;

		bool enabled{ true };
		
		bool lineBreak{ true };
		
		glm::vec2 size{ 0.f };
		
		glm::vec2 position{ 0.f };
		
		EWidgetSize sizeType{ EWidgetSize::ABSOLUTE };
		
		EWidgetAlignment alignment{ EWidgetAlignment::LEFT };

		FRWidgetContainer* parent{ nullptr };

	protected:
		std::string mWidgetID;
		
		glm::vec2 mCaculeteSize{ 0.f };
		
		bool mAutoExecutePlugins{ true };

	private:
		bool mDestroyed{ false };
		
		inline static size_t __WIDGET_ID_INCREMENT{ 0 };

	};
}

