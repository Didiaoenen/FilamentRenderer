#include "Core.FRModel.h"

#include "Core.FRMesh.h"

void FR::FRModel::SetMesh(FRMesh* pMesh)
{
	mMeshes.emplace_back(pMesh);
}

const std::vector<FR::FRMesh*>& FR::FRModel::GetMeshes() const
{
    return mMeshes;
}

const std::vector<std::string>& FR::FRModel::GetMaterialNames() const
{
    return mMaterialNames;
}

FR::FRModel::~FRModel()
{
	for (auto& mesh : mMeshes)
	{
		delete mesh; mesh = nullptr;
	}
	mMeshes.clear();
}
