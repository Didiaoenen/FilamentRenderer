#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	template <typename T, size_t _Size>
	class FRInputMultipleScalars
		: public FRDataWidget<std::array<T, _Size>>
	{
		static_assert(_Size > 1, "Invalid InputMultipleScalars _Size (2 or more requiered)");
		static_assert(std::is_scalar<T>::value, "Invalid InputMultipleScalars T (Scalar expected)");

	public:
		FRInputMultipleScalars(ImGuiDataType pDataType, T pDefaultValue, T pStep,
			T pFastStep, const std::string& pLabel, const std::string& pFormat, bool pSelectAllOnClick)
			: FRDataWidget<std::array<T, _Size>>(values)
			, mDataType(pDataType)
			, step(pStep)
			, fastStep(pFastStep)
			, label(pLabel)
			, format(pFormat)
			, selectAllOnClick(pSelectAllOnClick)
		{
			values.fill(pDefaultValue);
		}

	protected:
		void _Draw_Impl() override
		{
			std::array<T, _Size> previousValue = values;

			ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
			if (selectAllOnClick)
			{
				flags |= ImGuiInputTextFlags_AutoSelectAll;
			}

			bool enterPressed = ImGui::InputScalarN((label + this->mWidgetID).c_str(), mDataType, values.data(),
				_Size, step != 0.0f ? &step : nullptr, fastStep != 0.0f ? &fastStep : nullptr, format.c_str(), flags);

			bool hasChanged = false;

			for (size_t i = 0; i < _Size; ++i)
			{
				if (previousValue[i] != values[i])
				{
					hasChanged = true;
				}
			}

			if (hasChanged)
			{
				ContentChangedEvent.Invoke(values);
				this->NotifyChange();
			}

			if (enterPressed)
			{
				EnterPressedEvent.Invoke(values);
			}
		}

	public:
		T step;
		T fastStep;
		std::string label;
		std::string format;

		std::array<T, _Size> values;

		bool selectAllOnClick{ false };

		FREvent<std::array<T, _Size>&> EnterPressedEvent;
		FREvent<std::array<T, _Size>&> ContentChangedEvent;

	private:
		ImGuiDataType mDataType;

	};

	template <size_t _Size>
	class FRInputMultipleInts
		: public FRInputMultipleScalars<int, _Size>
	{
	public:
		FRInputMultipleInts(int pDefaultValue = 0, int pStep = 1, int pFastStep = 0,
			const std::string& pLabel = "", const std::string& pFormat = "%d", bool pSelectAllOnClick = true)
			: FRInputMultipleScalars<int, _Size>(ImGuiDataType_S32, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}

	};

	template <size_t _Size>
	class FRInputMultipleFloats
		: public FRInputMultipleScalars<float, _Size>
	{
	public:
		FRInputMultipleFloats(float pDefaultValue = 0.0f, float pStep = 0.1f, float pFastStep = 0.0f,
			const std::string& pLabel = "", const std::string& pFormat = "%.3f", bool pSelectAllOnClick = true)
			: FRInputMultipleScalars<float, _Size>(ImGuiDataType_Float, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}

	};

	template <size_t _Size>
	class FRInputMultipleDoubles
		: public FRInputMultipleScalars<double, _Size>
	{
	public:
		FRInputMultipleDoubles(double pDefaultValue = 0.0, double pStep = 0.1, double pFastStep = 0.0,
			const std::string& pLabel = "", const std::string& pFormat = "%.6f", bool pSelectAllOnClick = true)
			: FRInputMultipleScalars<double, _Size>(ImGuiDataType_Double, pDefaultValue, pStep, pFastStep, pLabel, pFormat, pSelectAllOnClick)
		{
		}

	};
}

