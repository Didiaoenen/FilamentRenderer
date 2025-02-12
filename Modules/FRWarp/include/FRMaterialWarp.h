#pragma once

#include "FRPtrWarp.h"
#include <filament/Material.h>

namespace FR
{
	class FREngineWarp;
	class FRTextureWarp;
	class FRTextureSamplerWarp;
	class FRMaterialInstanceWarp;

	class FRMaterialWarp
		: public FRPtrWarp<filament::Material>
	{
	public:
		using EUniformType = filament::Material::ParameterType;

		using ESamplerType = filament::Material::SamplerType;

		using ESubpassType = filament::Material::SubpassType;

	public:

		class Builder
		{
			friend class FRMaterialWarp;

		public:
			Builder()
				: mBuilder()
			{
			}

			Builder& Package(const void* pPayload, size_t pSize)
			{
				mBuilder.package(pPayload, pSize);
				return *this;
			}

			FRMaterialWarp* Build(FREngineWarp* pEngine)
			{
				return new FRMaterialWarp(pEngine, this);
			}

		private:
			filament::Material::Builder mBuilder;
		};

		struct ParameterInfo
		{
			std::string name;
			bool isSampler;
			bool isSubpass;
			union {
				EUniformType uniformType;
				ESamplerType samplerType;
				ESubpassType subpassType;
			};
			uint32_t count;
		};

		FRMaterialWarp() = default;

		FRMaterialWarp(FREngineWarp* pEngine, Builder* pBuilder);

		FRMaterialInstanceWarp* CreateInstance(const char* pName = nullptr);

		void SetDefaultParameter(const char* pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler);

		size_t GetParameters(ParameterInfo* pParameters, size_t pCount);

		bool HasParameter(const std::string& pName);

		size_t GetParameterCount();

	};
}

