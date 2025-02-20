#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class FRModel;

	class FRModelManager
		: public FRResourceManager<FRModel>
	{
	public:
		virtual FRModel* CreateResource(const std::string& pPath) override;

		virtual void ReloadResource(FRModel* pResource, const std::string& pPath) override;
		
		virtual void DestroyResource(FRModel* pResource) override;

	};
}

