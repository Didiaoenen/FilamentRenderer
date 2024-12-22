#pragma once

#include "GUI.FRDragScalar.h"

namespace FR::GUI
{
	class FRDragInt
		: public FRDragSingleScalar<int>
	{
	public:
		FRDragInt(int pMin = 0, int pMax = 100, int pValue = 50,
			float pSpeed = 1.f, const std::string& pLabel = "", const std::string& pFormat = "%d")
			: FRDragSingleScalar<int>(ImGuiDataType_::ImGuiDataType_S32, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}
	
	};

	class FRDragFloat
		: public FRDragSingleScalar<float>
	{
	public:
		FRDragFloat(float pMin = 0.f, float pMax = 1.f, float pValue = 0.5f,
			float pSpeed = 0.1f, const std::string& pLabel = "", const std::string& pFormat = "%.3f")
			: FRDragSingleScalar<float>(ImGuiDataType_::ImGuiDataType_Float, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}
	
	};

	class FRDragDouble
		: public FRDragSingleScalar<double>
	{
	public:
		FRDragDouble(double pMin = 0.0, double pMax = 1.0, double pValue = 0.5,
			float pSpeed = 0.1f, const std::string& pLabel = "", const std::string& pFormat = "%.6f")
			: FRDragSingleScalar<double>(ImGuiDataType_::ImGuiDataType_Double, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}
	
	};

	template <size_t _Size>
	class FRDragMultipleInts
		: public FRDragMultipleScalars<int, _Size>
	{
	public:
		FRDragMultipleInts(int pMin = 0, int pMax = 100, int pValue = 50,
			float pSpeed = 1.0f, const std::string& pLabel = "", const std::string& pFormat = "%d") 
			: FRDragMultipleScalars<int, _Size>(ImGuiDataType_::ImGuiDataType_S32, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}

	};

	template <size_t _Size>
	class FRDragMultipleFloats
		: public FRDragMultipleScalars<float, _Size>
	{
	public:
		FRDragMultipleFloats(float pMin = 0.f, float pMax = 1.0f, float pValue = 0.5f,
			float pSpeed = 0.1f, const std::string& pLabel = "", const std::string& pFormat = "%.3f")
			: FRDragMultipleScalars<float, _Size>(ImGuiDataType_::ImGuiDataType_Float, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}

	};

	template <size_t _Size>
	class FRDragMultipleDoubles
		: public FRDragMultipleScalars<double, _Size>
	{
	public:
		FRDragMultipleDoubles(double pMin = 0.0, double pMax = 1.0, double pValue = 0.5,
			float pSpeed = 0.1f, const std::string& pLabel = "", const std::string& pFormat = "%.6f")
			: FRDragMultipleScalars<double, _Size>(ImGuiDataType_::ImGuiDataType_Double, pMin, pMax, pValue, pSpeed, pLabel, pFormat)
		{
		}

	};
}

