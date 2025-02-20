#include "Core.FRShaderLoader.h"

#include "Core.FRShader.h"
#include "Core.FRTexture.h"

#include <EnumOpt.h>
#include <FileConfig.h>
#include <StringExtension.h>
#include <MaterialCompiler.h>
#include <Tools.FRFile.h>

#include <glm/glm.hpp>

#include <utils/Path.h>
#include <filamat/MaterialBuilder.h>

#include <sstream>
#include <fstream>

FR::FRShader* FR::FRShaderLoader::Create(const std::string& pFilePath)
{
	auto splits = StringExtension::Split(pFilePath, '.');
	auto propInfos = ParseProperty(splits[0] + ".shader");
	auto data = FRFile::ReadBinaryFile(splits[0] + ".filamat");
	return new FRShader(propInfos, data);
}

void FR::FRShaderLoader::Recompile(FRShader& pShader, const std::string& pFilePath)
{
}

void FR::FRShaderLoader::Destroy(FRShader*& pShader)
{
	delete pShader; pShader = nullptr;
}

std::vector<FR::FRPropInfo> FR::FRShaderLoader::ParseProperty(const std::string& pFilePath)
{
	std::vector<FRPropInfo> propInfos;

	filamat::MaterialBuilder::init();
	filamat::MaterialBuilder builder;

	matc::MaterialCompiler compiler;
	if (compiler.run(matc::FileConfig{ utils::Path(pFilePath).getAbsolutePath() }, builder))
	{
		for (int i = 0; i < builder.getParameterCount(); ++i)
		{
			FRPropInfo& info = propInfos.emplace_back();
			auto& parameter = builder.getParameters()[i];
			info.name = parameter.name.c_str();
			info.size = parameter.size;

			info.sampler = parameter.isSampler();
			if (!info.sampler)
			{
				info.uniformType = parameter.uniformType;
				switch (info.uniformType)
				{
				case FRMaterialWarp::EUniformType::BOOL:
					info.data = std::make_any<bool>(false);
					break;
				case FRMaterialWarp::EUniformType::INT:
					info.data = std::make_any<int>(0);
					break;
				case FRMaterialWarp::EUniformType::FLOAT:
					info.data = std::make_any<float>(0.f);
					break;
				case FRMaterialWarp::EUniformType::FLOAT2:
					info.data = std::make_any<glm::vec2>(0.f);
					break;
				case FRMaterialWarp::EUniformType::FLOAT3:
					info.data = std::make_any<glm::vec3>(0.f);
					break;
				case FRMaterialWarp::EUniformType::FLOAT4:
					info.data = std::make_any<glm::vec4>(0.f);
					break;
				case FRMaterialWarp::EUniformType::MAT3:
					info.data = std::make_any<glm::mat3>(1.f);
					break;
				case FRMaterialWarp::EUniformType::MAT4:
					info.data = std::make_any<glm::mat4>(1.f);
					break;
				default:
					break;
				}
			}
			else
			{
				info.samplerType = parameter.samplerType;
				switch (info.samplerType)
				{
				case FRMaterialWarp::ESamplerType::SAMPLER_2D:
					info.data = std::make_any<FRTexture*>(nullptr);
					break;
				default:
					break;
				}
			}
		}
	}

	return propInfos;
}
