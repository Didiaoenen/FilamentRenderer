#pragma once

#include <string>
#include <Core.FRObject.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>

namespace FR
{
	class SkeletonRig;
	class AnimationMask;

	class AMotion
		: public FRObject
	{
	public:
		AMotion() = default;

		virtual bool InitData(SkeletonRig* pSkeletonRig) = 0;

		virtual bool Update(float pDeltaTime) = 0;

		virtual bool Sample(float pDeltaTime) = 0;

		virtual void SetTimeRatio(float pTime) = 0;

		virtual float GetTimeRatio() = 0;

		virtual float GetDuration() = 0;

		ozz::vector<ozz::math::SoaTransform>& GetLocalTrans()
		{
			return mLocalTrans;
		}

	public:
		virtual ~AMotion() {}

	public:
		std::string path;

		float weight{ 1.f };

		bool additive{ false };

		float playbackSpeed{ 1.f };

		AnimationMask* mask{ nullptr };

	protected:
		SkeletonRig* mSkeletonRig{ nullptr };

		ozz::vector<ozz::math::SoaTransform> mLocalTrans;

		float mTimeRatio{ 0.f };

	};
}

