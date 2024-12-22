#pragma once

#include <any>
#include <vector>
#include <string>

#include <EUniformType.h>
#include "EMaterialDefine.h"
#include "Core.FRObject.h"

namespace FR
{
	class FRMaterial;
	class FRMaterialWarp;
	class FRMaterialInstanceWarp;

	struct FRPropInfo
	{
		bool sampler;
		std::string name;
		std::string size;
		ESamplerType samplerType;
		EUniformType uniformType;
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