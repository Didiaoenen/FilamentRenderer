#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class FRTexture2D;

	class FRKtxManager
		: public FRResourceManager<FRTexture2D>
	{
	public:
		virtual FRTexture2D* CreateResource(const std::string& pPath) override;

		virtual void DestroyResource(FRTexture2D* pResource) override;

		virtual void ReloadResource(FRTexture2D* pResource, const std::string& pPath) override;

	};
}

