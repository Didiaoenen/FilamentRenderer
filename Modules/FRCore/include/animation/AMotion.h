#pragma once

#include <string>
#include <Core.FRObject.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>

namespace FR
{
	class SkeletonRig;

	class AMotion
		: public FRObject
	{
	public:
		AMotion() = default;

		virtual bool InitData(SkeletonRig* pSkeletonRig) = 0;

		virtual bool Update(float pDeltaTime) = 0;

		virtual bool Sample(float pDeltaTime) = 0;

		ozz::vector<ozz::math::SoaTransform> GetLocalTrans() { return mLocalTrans; }

	public:
		virtual ~AMotion() {}

	public:
		std::string path;

	protected:
		SkeletonRig* mSkeletonRig{ nullptr };

		ozz::vector<ozz::math::SoaTransform> mLocalTrans;

	};
}

