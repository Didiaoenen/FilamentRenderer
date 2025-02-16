#include "Core.FRModel.h"

#include "Core.FRMesh.h"

#include <MathConvert.h>
#include <FRFilamentHelper.h>

FR::FRModel::FRModel()
{
	mMaterials.fill(nullptr);
}

void FR::FRModel::Build(FREntityWarp* pEntity)
{
	mEntity = pEntity;
}

void FR::FRModel::AttachmentMesh(FRMesh* pMesh)
{
	pMesh->model = this;
	mMeshes.push_back(pMesh);
}

FR::SkeletonRig* FR::FRModel::GetSkeletonRig() const
{
	return mSkeletonRig;
}

const std::vector<FR::FRMesh*>& FR::FRModel::GetMeshes() const
{
    return mMeshes;
}

void FR::FRModel::FillMaterial(FRMaterial* pMaterial)
{
	for (size_t i = 0; i < mMeshes.size(); ++i)
	{
		mMaterials[i] = pMaterial;
		mMeshes[i]->SetMaterial(pMaterial);
	}
}

void FR::FRModel::SetMaterialAtIndex(uint8_t pIndex, FRMaterial* pMaterial)
{
	mMaterials[pIndex] = pMaterial;
	mMeshes[pIndex]->SetMaterial(pMaterial);
}

void FR::FRModel::SetAxisAlignedBoundingBox(FRBoxWarp&& pBox)
{
	auto engine = FRFilamentHelper::GetEngine();
	auto rcm = engine->GetRenderableManager();
	rcm->SetAxisAlignedBoundingBox(GetRenderInstance(), std::forward<FRBoxWarp>(pBox));
}

const std::array<FR::FRMaterial*, FR::FRModel::kMaterialMaxCount>& FR::FRModel::GetMaterials() const
{
	return mMaterials;
}

const std::vector<std::string>& FR::FRModel::GetMaterialNames() const
{
    return mMaterialNames;
}

FR::FRTransformManagerWarp::Instance FR::FRModel::GetTransInstance()
{
	return FRFilamentHelper::GetTransformManager()->GetInstance(mEntity);
}

FR::FRRenderableManagerWarp::Instance FR::FRModel::GetRenderInstance()
{
	return FRFilamentHelper::GetRenderableManager()->GetInstance(mEntity);
}

FR::FREntityWarp* FR::FRModel::GetEntity()
{
	return mEntity;
}

FR::FRModel* FR::FRModel::Create()
{
	auto model = new FRModel();
	model->path = path;
	model->mSkeletonRig = mSkeletonRig;

	for (const auto& mesh : mMeshes)
	{
		model->AttachmentMesh(mesh->Create());
	}

	return model;
}

FR::FRModel::~FRModel()
{
	for (const auto mesh : mMeshes)
	{
		delete mesh;
	}
	mMeshes.clear();
}
