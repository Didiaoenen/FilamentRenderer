#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class FRMaterial;

	class FRMaterialManager
		: public FRResourceManager<FRMaterial>
	{
	public:
		virtual FRMaterial* CreateResource(const std::string& pPath) override;

		virtual void ReloadResource(FRMaterial* pResource, const std::string& pPath) override;

		virtual void DestroyResource(FRMaterial* pResource) override;

		virtual ~FRMaterialManager()
		{
			UnloadResources();
		}

	};
}

