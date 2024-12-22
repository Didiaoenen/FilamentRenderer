#pragma once

#include <array>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <FRTransformManagerWarp.h>
#include <FRRenderableManagerWarp.h>
#include "Core.FREntity.h"

namespace FR
{
	class FRMesh;
	class FRMaterial;
	class SkeletonRig;

	class FRBoxWarp;

	struct FRModelData
	{
		std::vector<FRMesh*> meshs;
		std::vector<FRModelData> childs;
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 accTransform = glm::mat4(1.0f);
	};

	class FRModel
		: public FREntity
	{
		friend class FRModelLoader;
		friend class FROzzModelLoader;

		const static uint8_t kMaterialMaxCount = 0xFF;

	public:
		FRModel();

		void InitMeshInfo();

		void AddMesh(FRMesh* pMesh);

		const std::vector<FRMesh*>& GetMeshes() const;

		SkeletonRig* GetSkeletonRig() const;

		void FillMaterial(FRMaterial* pMaterial);

		void SetMaterialAtIndex(uint8_t pIndex, FRMaterial* pMaterial);

		void SetAxisAlignedBoundingBox(const FRBoxWarp& pBox);

		const std::array<FRMaterial*, kMaterialMaxCount>& GetMaterials() const;

		const std::vector<std::string>& GetMaterialNames() const;

		//const BoundingSphere& GetBoundingSphere() const;

		FRTransformManagerWarp::Instance GetTransInstance();
		
		FRRenderableManagerWarp::Instance GetRenderInstance();

	public:
		~FRModel();

		//void ComputeBoundingSphere();

	public:
		const std::string path;

	private:
		std::vector<FRMesh*> mMeshes;
		std::array<FRMaterial*, kMaterialMaxCount> mMaterials;

		SkeletonRig* mSkeletonRig{ nullptr };

		std::vector<std::string> mMaterialNames;
		glm::mat4 mTransformData = glm::mat4(1.0f);
		glm::mat4 mAccTransformData = glm::mat4(1.0f);

		//BoundingSphere m_boundingSphere;

	};
}

