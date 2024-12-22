#pragma once

#include "GUI.FRDataWidget.h"

namespace FR::GUI
{
	template <typename T>
	class FRDragSingleScalar
		: public FRDataWidget<T>
	{
		static_assert(std::is_scalar<T>::value, "Invalid DragSingleScalar T (Scalar expected)");

	public:
		FRDragSingleScalar(ImGuiDataType pDataType, T pMin, T pMax, T pValue,
			float pSpeed, const std::string& pLabel, const std::string& pFormat)
			: FRDataWidget<T>(value)
			, mDataType(pDataType)
			, min(pMin)
			, max(pMax)
			, value(pValue)
			, speed(pSpeed)
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

			this->SetItemLayout();

			if (ImGui::DragScalar((label + this->mWidgetID).c_str(), mDataType, &value, speed, &min, &max, format.c_str()))
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

		float speed{ 0.f };

		FREvent<T> ValueChangedEvent;

	private:
		ImGuiDataType mDataType;

	};

	template <typename T, size_t _Size>
	class FRDragMultipleScalars
		: public FRDataWidget<std::array<T, _Size>>
	{
		static_assert(_Size > 1, "Invalid DragMultipleScalars _Size (2 or more requiered)");

	public:
		FRDragMultipleScalars(ImGuiDataType_ pDataType, T pMin, T pMax, T pValue,
			float pSpeed, const std::string& pLabel, const std::string& pFormat) 
			: FRDataWidget<std::array<T, _Size>>(values)
			, mDataType(pDataType)
			, min(pMin)
			, max(pMax)
			, speed(pSpeed)
			, label(pLabel)
			, format(pFormat)
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

			this->SetItemLayout();

			if (ImGui::DragScalarN((label + this->mWidgetID).c_str(), mDataType, values.data(), _Size, speed, &min, &max, format.c_str()))
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

		float speed{ 0.f };
		
		std::array<T, _Size> values;

		FREvent<std::array<T, _Size>&> ValueChangedEvent;

	protected:
		ImGuiDataType_ mDataType;

	};
}

