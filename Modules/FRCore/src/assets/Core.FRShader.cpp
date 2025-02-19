#include "Core.FRShader.h"
#include <FREngineWarp.h>
#include <FRMaterialWarp.h>
#include <FRFilamentHelper.h>

FR::FRShader::FRShader(std::vector<FR::FRPropInfo> pPropInfo, std::vector<uint8_t> pData)
	: propInfos(pPropInfo)
	, data(pData)
{
	auto engine = FRFilamentHelper::GetEngine();

	mMaterial = FRMaterialWarp::Builder()
		.Package(pData.data(), pData.size())
		.Build(engine);
}

FR::FRMaterialInstanceWarp* FR::FRShader::CreateInstance(const std::string& pName)
{
	return mMaterial->CreateInstance(pName.c_str());
}

std::vector<FR::FRMaterial*>& FR::FRShader::GetRefMaterials()
{
	return mRefMaterials;
}

void FR::FRShader::SetRefMaterial(FRMaterial* pMaterial)
{
	mRefMaterials.emplace_back(pMaterial);
}

FR::FRMaterialWarp* FR::FRShader::NativePtr()
{
	return mMaterial;
}

FR::FRShader::~FRShader()
{
	FRFilamentHelper::GetEngine()->Destroy(mMaterial);
	FRFilamentHelper::GetEngine()->UnRegisterMaterial(mMaterial);
	delete mMaterial; mMaterial = nullptr;
}