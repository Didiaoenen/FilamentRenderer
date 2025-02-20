#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class Animation;

	class AnimationManager
		: public FRResourceManager<Animation>
	{
	public:
		virtual Animation* CreateResource(const std::string& pPath) override;

		virtual void ReloadResource(Animation* pResource, const std::string& pPath) override;
		
		virtual void DestroyResource(Animation* pResource) override;

	};
}

