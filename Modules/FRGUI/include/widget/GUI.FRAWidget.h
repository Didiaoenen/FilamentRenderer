#pragma once

#include <string>

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

		FRWidgetContainer* GetParent();
		
		void LinkTo(const FRAWidget* pWidget);

		void SetParent(FRWidgetContainer* pParent);

		std::string GetWidgetID();

		glm::vec2 GetLabelSize();

	protected:
		virtual void SetItemSize();

		virtual void SetItemAlign();

		virtual void SetItemLayout();

		virtual void DrawItemActivityOutline(glm::vec2 pMin, glm::vec2 pMax, bool pInactive = false, Color pColorActive = { 80.0f, 80.0f, 80.0f });

		virtual void _Draw_Impl() = 0;

		glm::vec2 CaculateSize();

	public:
		~FRAWidget() = default;

	public:
		std::string name;
		bool enabled{ true };
		bool lineBreak{ true };
		FRWidgetContainer* parent{ nullptr };

		glm::vec2 size{ 0.f };
		glm::vec2 position{ 0.f };
		EWidgetSizeType sizeType{ EWidgetSizeType::ABSOLUTE };
		EWidgetAlignment alignment{ EWidgetAlignment::LEFT };

	protected:
		std::string mWidgetID;
		glm::vec2 mCaculeteSize{ 0.f };
		bool mAutoExecutePlugins{ true };

	private:
		bool mDestroyed{ false };
		static uint64_t __WIDGET_ID_INCREMENT;

	};
}

