#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	template <typename T>
	class FRInputSingleScalar
		: public FRDataWidget<T>
	{
		static_assert(std::is_scalar<T>::value, "Invalid InputSingleScalar T (Scalar expected)");

	public:
		FRInputSingleScalar(ImGuiDataType pDataType, T pDefaultValue, T pStep,
			T pFastStep, const std::string& pLabel, const std::string& pFormat, bool pSelectAllOnClick)
			: FRDataWidget<T>(value)
			, mDataType(pDataType)
			, value(pDefaultValue)
			, step(pStep)
			, fastStep(pFastStep)
			, label(pLabel)
			, format(pFormat)
			, selectAllOnClick(pSelectAllOnClick)
		{
		}

	protected:
		void _Draw_Impl() override
		{
			T previousValue = value;

			ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
			if (selectAllOnClick)
			{
				flags |= ImGuiInputTextFlags_AutoSelectAll;
			}

			bool enterPressed = ImGui::InputScalar((label + this->mWidgetID).c_str(), mDataType,
				&value, step != 0.0f ? &step : nullptr, fastStep != 0.0f ? &fastStep : nullptr, format.c_str(), flags);

			if (previousValue != value)
			{
				ContentChangedEvent.Invoke(value);
				this->NotifyChange();
			}

			if (enterPressed)
			{
				EnterPressedEvent.Invoke(value);
			}
		}

	public:
		T step;
		T value;
		T fastStep;
		std::string label;
		std::string format;
		
		bool selectAllOnClick{ false };
		
		FREvent<T> ContentChangedEvent;
		FREvent<T> EnterPressedEvent;

	private:
		ImGuiDataType mDataType;
	};

	class InputInt
		: public FRInputSingleScalar<int>
	{
	public:
		InputInt(int pDefaultValue = 0, int pStep = 1, int pFastStep = 0,
			const std::string& pLabel = "", const std::string& pFormat = "%d", bool pSelectAllOnClick = true)
			: FRInputSingleScalar<int>(ImGuiDataType_S32, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}
	
	};

	class InputFloat
		: public FRInputSingleScalar<float>
	{
	public:
		InputFloat(float pDefaultValue = 0.0f, float pStep = 0.1f, float pFastStep = 0.0f,
			const std::string& pLabel = "", const std::string& pFormat = "%.3f", bool pSelectAllOnClick = true)
			: FRInputSingleScalar<float>(ImGuiDataType_Float, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}

	};

	class InputDouble
		: public FRInputSingleScalar<double>
	{
	public:
		InputDouble(double pDefaultValue = 0.0, double pStep = 0.1, double pFastStep = 0.0,
			const std::string& pLabel = "", const std::string& pFormat = "%.6f", bool pSelectAllOnClick = true)
			: FRInputSingleScalar<double>(ImGuiDataType_Double, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}

	};
}

