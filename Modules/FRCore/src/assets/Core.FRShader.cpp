#include "Core.FRShader.h"
#include <MathConvert.h>
#include <FRMaterialWarp.h>
#include <FRFilamentHelper.h>

FR::FRPropInfo* FR::FRShader::GetPropInfo(const std::string& pName)
{
	auto found = std::find_if(propInfos.begin(), propInfos.end(), [&pName](const FRPropInfo& pElement)
		{
			return pName == pElement.name;
		});
	
	if (found != propInfos.end())
	{
		return &(*found);
	}
	return nullptr;
}

FR::FRMaterialWarp* FR::FRShader::NativePtr()
{
	return mMaterial;
}

FR::FRMaterialInstanceWarp* FR::FRShader::CreateInstance(const std::string& pName)
{
	return mMaterial->CreateInstance(pName.c_str());
}

FR::FRShader::FRShader(std::vector<FR::FRPropInfo> pPropInfo, std::vector<uint8_t> pData)
	: propInfos(pPropInfo)
	, data(pData)
{
	auto engine = FRFilamentHelper::GetEngine();
	mMaterial = FRMaterialWarp::Builder()
		.Package(pData.data(), pData.size())
		.Build(engine);

	FRMaterialWarp::ParameterInfo parameterInfo[96];
	auto count = mMaterial->GetParameters(parameterInfo, 999);
	for (int i = 0; i < count; i++)
	{
	}
}
