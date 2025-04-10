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
		using ECullingMode = filament::MaterialInstance::CullingMode;

		using ETransparencyMode = filament::MaterialInstance::TransparencyMode;

	public:
		FRMaterialInstanceWarp() = default;

		FRMaterialInstanceWarp(FRMaterialWarp* pMaterial, const std::string& pName);

		void SetScissor(uint32_t pLeft, uint32_t pBottom, uint32_t pWidth, uint32_t pHeight);

		void SetParameter(const std::string& pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler);
		
		void SetTransparencyMode(ETransparencyMode pMode);

		void SetCullingMode(ECullingMode pCulling);

		void SetDepthCulling(bool pEnable);

		void SetColorWrite(bool pEnable);

		void SetDepthWrite(bool pEnable);

		template<typename T>
		void SetParameter(const std::string& pName, T const& value);

	};

	#include "FRMaterialInstanceWarp.inl"
}

