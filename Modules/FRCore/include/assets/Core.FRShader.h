#pragma once

#include "Core.FRObject.h"
#include <FRMaterialWarp.h>

#include <any>
#include <string>
#include <vector>

namespace FR
{
	class FRMaterial;
	class FRMaterialInstanceWarp;

	struct FRPropInfo
	{
		bool sampler;
		std::string name;
		std::string size;
		FRMaterialWarp::ESamplerType samplerType;
		FRMaterialWarp::EUniformType uniformType;
		std::any data;
	};

	class FRShader
		: public FRObject
	{
		friend class FRShaderLoader;

	public:
		FRShader(std::vector<FRPropInfo> pPropInfo, std::vector<uint8_t> pData);

		std::vector<FRMaterial*>& GetRefMaterials();

		void SetRefMaterial(FRMaterial* pMaterial);

		FRMaterialWarp* NativePtr();

	public:
		virtual ~FRShader();

	public:
		std::string path;
		std::vector<uint8_t> data;
		std::vector<FRPropInfo> propInfos;

	private:
		FRMaterialWarp* mShader{ nullptr };
		
		std::vector<FRMaterial*> mRefMaterials{ nullptr };

	};
}