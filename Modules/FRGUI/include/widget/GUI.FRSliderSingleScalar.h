#pragma once

#include "GUI.FRDataWidget.h"
#include "ESliderOrientation.h"

namespace FR::GUI
{
	template <typename T>
	class FRSliderSingleScalar
		: public FRDataWidget<T>
	{
		static_assert(std::is_scalar<T>::value, "Invalid SliderSingleScalar T (Scalar expected)");

	public:
		FRSliderSingleScalar(ImGuiDataType pDataType, T pMin, T pMax, T pValue,
			ESliderOrientation pOrientation, const std::string& pLabel, const std::string& pFormat)
			: FRDataWidget<T>(value)
			, mDataType(pDataType)
			, min(pMin)
			, max(pMax)
			, value(pValue)
			, orientation(pOrientation)
			, label(pLabel)
			, format(pFormat)
		{
		}

	protected:
		void _Draw_Impl() override
		{
			if (max < min)
			{
				max = min;
			}

			if (value < min)
			{
				value = min;
			}
			else if (value > max)
			{
				value = max;
			}

			bool valueChanged = false;

			switch (orientation)
			{
			case ESliderOrientation::HORIZONTAL:
				valueChanged = ImGui::SliderScalar((label + this->mWidgetID).c_str(), mDataType, &value, &min, &max, format.c_str());
				break;
			case ESliderOrientation::VERTICAL:
				valueChanged = ImGui::VSliderScalar((label + this->mWidgetID).c_str(),
					MathConvert::ToImVec2(verticalModeSize), mDataType, &value, &min, &max, format.c_str());
				break;
			}

			if (valueChanged)
			{
				ValueChangedEvent.Invoke(value);
				this->NotifyChange();
			}
		}

	public:
		T min;
		T max;
		T value;
		std::string label;
		std::string format;
		glm::vec2 verticalModeSize{};
		ESliderOrientation orientation{ ESliderOrientation::HORIZONTAL };

		FREvent<T> ValueChangedEvent;

	private:
		ImGuiDataType mDataType;
	};

	class SliderInt
		: public FRSliderSingleScalar<int>
	{
	public:
		SliderInt(int pMin = 0, int pMax = 100, int pValue = 50,
			ESliderOrientation pOrientation = ESliderOrientation::HORIZONTAL, const std::string& pLabel = "", const std::string& pFormat = "%d")
			: FRSliderSingleScalar<int>(ImGuiDataType_S32, pMin, pMax, pValue, pOrientation, pLabel, pFormat)
		{
		}

	};

	class SliderFloat
		: public FRSliderSingleScalar<float>
	{
	public:
		SliderFloat(float pMin = 0.0f, float pMax = 1.0f, float pValue = 0.5f,
			ESliderOrientation pOrientation = ESliderOrientation::HORIZONTAL, const std::string& pLabel = "", const std::string& pFormat = "%.3f")
			: FRSliderSingleScalar<float>(ImGuiDataType_Float, pMin, pMax, pValue, pOrientation, pLabel, pFormat)
		{
		}

	};

	class SliderDouble
		: public FRSliderSingleScalar<double>
	{
	public:
		SliderDouble(double pMin = 0.0, double pMax = 1.0, double pValue = 0.5,
			ESliderOrientation pOrientation = ESliderOrientation::HORIZONTAL, const std::string& pLabel = "", const std::string& pFormat = "%.6f")
			: FRSliderSingleScalar<double>(ImGuiDataType_Double, pMin, pMax, pValue, pOrientation, pLabel, pFormat)
		{
		}

	};
}

