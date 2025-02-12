#pragma once

#include <any>
#include <vector>
#include <string>

#include "Core.FRObject.h"
#include <FRMaterialWarp.h>

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

		FRMaterialInstanceWarp* CreateInstance(const std::string& pName = "");
		
		FRPropInfo* GetPropInfo(const std::string& pName);

		FRMaterialWarp* NativePtr();

	public:
		~FRShader() = default;

	public:
		const std::string path;
		std::vector<uint8_t> data;
		std::vector<FRPropInfo> propInfos;

		FRMaterial* material{ nullptr };

	private:
		FRMaterialWarp* mMaterial{ nullptr };

	};
}