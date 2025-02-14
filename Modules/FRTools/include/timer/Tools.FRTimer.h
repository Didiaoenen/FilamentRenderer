#pragma once

#include <chrono>
#include <cstdint>

namespace FR
{
	class FRTimer
	{
	public:
		FRTimer();

		void Update();

		static void SetFpsLimit(float pFps);

		static float GetFpsLimit();

		static double GetTimeMs();

		static double GetTimeSec();

		static double GetDeltaTimeMs();

		static double GetDeltaTimeSec();

		static double GetDeltaTimeSmoothedMs();

		static double GetDeltaTimeSmoothedSec();

		static std::string GetDateAsString();

	private:
		static double mWeightDelta;

		// frame time
		inline static double mTimeMs{ 0 };
		inline static double mDeltaTimeMs{ 0 };
		inline static double mDeltaTimeSmoothedMs{ 0 };

		// fps
		inline static float mFpsMin;
		inline static float mFpsMax;
		inline static float mFpsLimit = mFpsMin;
		inline static float mFpsLimitPrevious = mFpsLimit;

		// misc
		inline static std::chrono::steady_clock::time_point mLastTickTime;

	};
}

