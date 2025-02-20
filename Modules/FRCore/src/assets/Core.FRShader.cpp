#include "Core.FRShader.h"
#include <FREngineWarp.h>
#include <FRMaterialWarp.h>
#include <FRFilamentHelper.h>

FR::FRShader::FRShader(std::vector<FR::FRPropInfo> pPropInfo, std::vector<uint8_t> pData)
	: propInfos(pPropInfo)
	, data(pData)
{
	auto engine = FRFilamentHelper::GetEngine();

	mShader = FRMaterialWarp::Builder()
		.Package(pData.data(), pData.size())
		.Build(engine);
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
	return mShader;
}

FR::FRShader::~FRShader()
{
	FRFilamentHelper::GetEngine()->Destroy(mShader);
	FRFilamentHelper::GetEngine()->UnRegisterShader(mShader);
	delete mShader; mShader = nullptr;
}