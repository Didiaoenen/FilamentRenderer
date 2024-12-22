#include "Core.FRModel.h"

#include "Core.FRMesh.h"

#include <MathConvert.h>
#include <FRFilamentHelper.h>

FR::FRModel::FRModel()
	: FREntity()
{
	mMaterials.fill(nullptr);

	auto engine = FRFilamentHelper::GetEngine();
	auto tcm = engine->GetTransformManager();
	tcm->Create(mEntity, FRTransformManagerWarp::Instance{}, glm::mat4(1.0));

	FRRenderableManagerWarp::Builder builder(1);

	builder.BoundingBox({ { -0.5f, -0.5f , -0.5f }, { 0.5f ,0.5f ,0.5f } });
	builder.Build(engine, mEntity);
}

void FR::FRModel::AddMesh(FRMesh* pMesh)
{
	mMeshes.push_back(pMesh);
}

const std::vector<FR::FRMesh*>& FR::FRModel::GetMeshes() const
{
    return mMeshes;
}

void FR::FRModel::InitMeshInfo()
{
	for (const auto& mesh : mMeshes)
	{
		mesh->CreateRenderer(this);
		mesh->SetParentRender(this);
	}
}

FR::SkeletonRig* FR::FRModel::GetSkeletonRig() const
{
	return mSkeletonRig;
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

void FR::FRModel::SetAxisAlignedBoundingBox(const FRBoxWarp& pBox)
{
	auto engine = FRFilamentHelper::GetEngine();
	auto rcm = engine->GetRenderableManager();
	rcm->SetAxisAlignedBoundingBox(GetRenderInstance(), { { -500.0f, -500.0f, -500.0f }, { 500.0f, 500.0f, 500.0f } });
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

FR::FRModel::~FRModel()
{
}
