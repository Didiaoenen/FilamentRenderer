#pragma once

#include "FRPtrWarp.h"

#include <string>
#include <filament/Material.h>
#include <filament/MaterialInstance.h>

namespace FR
{
	class FRTextureWarp;
	class FRMaterialWarp;
	class FRTextureSamplerWarp;

	class FRMaterialInstanceWarp
		: public FRPtrWarp<filament::MaterialInstance>
	{
	public:
		FRMaterialInstanceWarp() = default;

		FRMaterialInstanceWarp(FRMaterialWarp* pMaterial, const char* pName);

		void SetScissor(uint32_t pLeft, uint32_t pBottom, uint32_t pWidth, uint32_t pHeight);

		void SetParameter(const char* pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler);
		
		void SetTransparencyMode(filament::TransparencyMode pMode);

		void SetCullingMode(filament::backend::CullingMode pCulling);

		void SetDepthCulling(bool pEnable);

		void SetColorWrite(bool pEnable);

		void SetDepthWrite(bool pEnable);

		template<typename T>
		inline void SetParameter(const std::string& pName, T const& value)
		{
			if (auto material = PtrValue(this)->getMaterial(); material->hasParameter(pName.c_str()))
			{
				PtrValue(this)->setParameter(pName.c_str(), value);
			}
		}

	};
}

