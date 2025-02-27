#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class AnimationClip;

	class FROzzAnimationManager
		: public FRResourceManager<AnimationClip>
	{
	public:
		virtual AnimationClip* CreateResource(const std::string& pPath) override;

		virtual void ReloadResource(AnimationClip* pResource, const std::string& pPath) override;
		
		virtual void DestroyResource(AnimationClip* pResource) override;

	};
}

