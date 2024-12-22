#include "Core.FROzzModelLoader.h"

#include "Core.FRMesh.h"
#include "Core.FRModel.h"

#include "SkeletonRig.h"
#include <StringExtension.h>
#include <Tools.FRPathUtils.h>

#include <ozz/animation/runtime/skeleton.h>

namespace FR
{
	FROzzModelParser FROzzModelLoader::__OZZ;
}

FR::FRModel* FR::FROzzModelLoader::Create(const std::string& pFilepath)
{
	FRModelData dataTree;
	std::vector<std::string> materialNames;

	if (__OZZ.LoadMesh(pFilepath, dataTree, materialNames))
	{
		FRModel* result = new FRModel();
		result->mMaterialNames = materialNames;

		std::string skelPath = pFilepath;
		StringExtension::Replace(skelPath, "ozz", "skel");
		auto skeleton = new ozz::animation::Skeleton();
		if (__OZZ.LoadSkeleton(skelPath, skeleton))
		{
			result->mSkeletonRig = new SkeletonRig(skeleton);
		}

		for (auto mesh : dataTree.meshs)
		{
			result->AddMesh(mesh);
		}

		result->InitMeshInfo();

		return result;
	}

	return nullptr;
}

void FR::FROzzModelLoader::Reload(FRModel& pModel, const std::string& pFilePath)
{
}

bool FR::FROzzModelLoader::Destroy(FRModel*& pModelInstance)
{
	return false;
}
