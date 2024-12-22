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
		static double mTimeMs;
		static double mDeltaTimeMs;
		static double mDeltaTimeSmoothedMs;

		// fps
		static float mFpsMin;
		static float mFpsMax;
		static float mFpsLimit;
		static float mFpsLimitPrevious;

		// misc
		static std::chrono::steady_clock::time_point mLastTickTime;

	};
}

