#include "Tools.FRTimer.h"

#include <glm/glm.hpp>

namespace FR
{
	double FRTimer::mWeightDelta = 1.0 / 15;
}

FR::FRTimer::FRTimer()
{
	mFpsLimit = 60.f;
	mLastTickTime = std::chrono::steady_clock::now();
}

void FR::FRTimer::Update()
{
	if (mLastTickTime.time_since_epoch() != std::chrono::steady_clock::duration::zero())
	{
		mDeltaTimeMs = static_cast<double>(std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - mLastTickTime).count());
	}

	double targetMs = 1000.0 / mFpsLimit;
	while (mDeltaTimeMs < targetMs)
	{
		mDeltaTimeMs = static_cast<double>(std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - mLastTickTime).count());
	}

	mDeltaTimeSmoothedMs = mDeltaTimeSmoothedMs * (1.0 - mWeightDelta) + mDeltaTimeMs * mWeightDelta;
	mTimeMs += mDeltaTimeMs;

	mLastTickTime = std::chrono::steady_clock::now();
}

void FR::FRTimer::SetFpsLimit(float pFps)
{
	mFpsLimit = glm::clamp(pFps, mFpsMin, mFpsMax);
}

float FR::FRTimer::GetFpsLimit()
{
	return mFpsLimit;
}

double FR::FRTimer::GetTimeMs()
{
	return mTimeMs;
}

double FR::FRTimer::GetTimeSec()
{
	return mTimeMs / 1000.0;
}

double FR::FRTimer::GetDeltaTimeMs()
{
	return mDeltaTimeMs;
}

double FR::FRTimer::GetDeltaTimeSec()
{
	return mDeltaTimeMs / 1000.0f;
}

double FR::FRTimer::GetDeltaTimeSmoothedMs()
{
	return mDeltaTimeSmoothedMs;
}

double FR::FRTimer::GetDeltaTimeSmoothedSec()
{
	return mDeltaTimeSmoothedMs / 1000.0;
}

std::string FR::FRTimer::GetDateAsString()
{
	tm ltm;
	auto now = time(nullptr);

	localtime_s(&ltm, &now);

	std::string dateData[6] =
	{
		std::to_string(1900 + ltm.tm_year),
		std::to_string(1 + ltm.tm_mon),
		std::to_string(ltm.tm_mday),
		std::to_string(ltm.tm_hour),
		std::to_string(ltm.tm_min),
		std::to_string(ltm.tm_sec)
	};

	for (uint8_t i = 1; i < 6; ++i)
	{
		if (dateData[i].size() < 2)
			dateData[i].insert(dateData[i].begin(), '0');
	}

	std::string date;
	for (uint8_t i = 0; i < 6; ++i)
	{
		date += dateData[i];
		if (i == 2)
			date += '_';
		else if (i != 5)
			date += '-';
	}

	return date;
}