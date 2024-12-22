#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class FRTexture;

	class FRTextureManager
		: public FRResourceManager<FRTexture>
	{
	public:
		virtual FRTexture* CreateResource(const std::string& pPath) override;

		virtual void DestroyResource(FRTexture* pResource) override;

		virtual void ReloadResource(FRTexture* pResource, const std::string& pPath) override;

	};
}

