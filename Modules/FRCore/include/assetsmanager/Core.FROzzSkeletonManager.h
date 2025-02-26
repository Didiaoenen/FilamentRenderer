#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class SkeletonRig;

	class FROzzSkeletonManager
		: public FRResourceManager<SkeletonRig>
	{
	public:
		virtual SkeletonRig* CreateResource(const std::string& pPath) override;

		virtual void ReloadResource(SkeletonRig* pResource, const std::string& pPath) override;

		virtual void DestroyResource(SkeletonRig* pResource) override;

	};
}