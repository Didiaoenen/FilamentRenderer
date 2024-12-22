#pragma once

#include "Core.FRResourceManager.h"

namespace FR
{
	class FRShader;

	class FRShaderManager
		: public FRResourceManager<FRShader>
	{
	public:
		virtual FRShader* CreateResource(const std::string& pPath) override;

		virtual void DestroyResource(FRShader* pResource) override;

		virtual void ReloadResource(FRShader* pResource, const std::string& pPath) override;

	};
}

