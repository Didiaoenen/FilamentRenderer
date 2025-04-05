#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	template <typename T, size_t _Size>
	class FRSliderMultipleScalars
		: public FRDataWidget<std::array<T, _Size>>
	{
		static_assert(_Size > 1, "Invalid SliderMultipleScalars _Size (2 or more requiered)");

	public:
		FRSliderMultipleScalars(ImGuiDataType_ pDataType, T pMin, T pMax, T pValue, const std::string& pLabel, const std::string& pFormat) 
			: FRDataWidget<std::array<T, _Size>>(values)
			, min(pMin)
			, max(pMax)
			, label(pLabel)
			, format(pFormat)
			, mDataType(pDataType)
		{
			values.fill(pValue);
		}

	protected:
		void _Draw_Impl() override
		{
			if (max < min)
			{
				max = min;
			}

			for (size_t i = 0; i < _Size; ++i)
			{
				if (values[i] < min)
				{
					values[i] = min;
				}
				else if (values[i] > max)
				{
					values[i] = max;
				}
			}

			bool valueChanged = ImGui::SliderScalarN((label + this->mWidgetID).c_str(), mDataType, values.data(), _Size, &min, &max, format.c_str());

			if (valueChanged)
			{
				ValueChangedEvent.Invoke(values);
				this->NotifyChange();
			}
		}

	public:
		T min;
		T max;

		std::string label;
		std::string format;

		std::array<T, _Size> values;

		FREvent<std::array<T, _Size>&> ValueChangedEvent;

	protected:
		ImGuiDataType_ mDataType;

	};

	template <size_t _Size>
	class SliderMultipleInts
		: public FRSliderMultipleScalars<int, _Size>
	{
	public:
		SliderMultipleInts(int pMin = 0, int pMax = 100, int pValue = 50, const std::string& pLabel = "", const std::string& pFormat = "%d")
			: FRSliderMultipleScalars<int, _Size>(ImGuiDataType_S32, pMin, pMax, pValue, pLabel, pFormat)
		{
		}

	};

	template <size_t _Size>
	class SliderMultipleFloats
		: public FRSliderMultipleScalars<float, _Size>
	{
	public:
		SliderMultipleFloats(float pMin = 0.0f, float pMax = 1.0f, float pValue = 0.5f, const std::string& pLabel = "", const std::string& pFormat = "%.3f")
			: FRSliderMultipleScalars<float, _Size>(ImGuiDataType_::ImGuiDataType_Float, pMin, pMax, pValue, pLabel, pFormat)
		{
		}

	};

	template <size_t _Size>
	class SliderMultipleDoubles
		: public FRSliderMultipleScalars<double, _Size>
	{
	public:
		SliderMultipleDoubles(double pMin = 0.0, double pMax = 1.0, double pValue = 0.5, const std::string& pLabel = "", const std::string& pFormat = "%.6f")
			: FRSliderMultipleScalars<double, _Size>(ImGuiDataType_::ImGuiDataType_Double, pMin, pMax, pValue, pLabel, pFormat)
		{
		}

	};
}

