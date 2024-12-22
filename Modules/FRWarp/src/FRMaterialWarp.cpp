#include "FRMaterialWarp.h"
#include "FREngineWarp.h"
#include "FRTextureWarp.h"
#include "FRTextureSamplerWarp.h"
#include "FRMaterialInstanceWarp.h"

FR::FRMaterialWarp::FRMaterialWarp(FREngineWarp* pEngine, Builder* pBuilder)
{
	mValue = FRPtrValue(pBuilder->mBuilder.build(*PtrValue(pEngine)));
}

FR::FRMaterialInstanceWarp* FR::FRMaterialWarp::CreateInstance(const char* pName)
{
	return new FR::FRMaterialInstanceWarp(this, pName);
}

void FR::FRMaterialWarp::SetDefaultParameter(const char* pName, FRTextureWarp* pTexture, FRTextureSamplerWarp& pSampler)
{
	PtrValue(this)->setDefaultParameter(pName, PtrValue(pTexture), RefValue(pSampler));
}

size_t FR::FRMaterialWarp::GetParameters(ParameterInfo* pParameters, size_t pCount)
{
	filament::Material::ParameterInfo parameters[96];
	pCount = PtrValue(this)->getParameters(parameters, pCount);

	for (int i = 0; i < pCount; i++)
	{
		auto& parameter = pParameters[i];
		parameter.name = parameters[i].name;
		parameter.isSampler = parameters[i].isSampler;
		parameter.isSubpass = parameters[i].isSubpass;
		parameter.uniformType = static_cast<FR::EUniformType>(parameters[i].type);
		parameter.samplerType = static_cast<FR::ESamplerType>(parameters[i].samplerType);
		parameter.subpassType = static_cast<FR::ESubpassType>(parameters[i].subpassType);
	}

	return pCount;
}

bool FR::FRMaterialWarp::HasParameter(const std::string& pName)
{
	return PtrValue(this)->hasParameter(pName.c_str());
}

size_t FR::FRMaterialWarp::GetParameterCount()
{
	return PtrValue(this)->getParameterCount();
}