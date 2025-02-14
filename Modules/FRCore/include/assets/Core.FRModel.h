#pragma once

#include "Core.FRObject.h"
#include <FRTransformManagerWarp.h>
#include <FRRenderableManagerWarp.h>

#include <array>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace FR
{
	class FRMesh;
	class FRMaterial;
	class SkeletonRig;

	class FRBoxWarp;
	class FREntityWarp;

	struct FRModelData
	{
		std::vector<FRMesh*> meshs;
		std::vector<FRModelData> childs;
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 accTransform = glm::mat4(1.0f);
	};

	class FRModel
		: public FRObject
	{
		friend class FRModelLoader;
		friend class FROzzModelLoader;

		static constexpr uint8_t kMaterialMaxCount = 0xFF;

	public:
		FRModel();

		void Build(FREntityWarp* pEntity);

		void AttachmentMesh(FRMesh* pMesh);

		SkeletonRig* GetSkeletonRig() const;

		const std::vector<FRMesh*>& GetMeshes() const;

		void FillMaterial(FRMaterial* pMaterial);

		void SetMaterialAtIndex(uint8_t pIndex, FRMaterial* pMaterial);

		void SetAxisAlignedBoundingBox(FRBoxWarp&& pBox);

		const std::array<FRMaterial*, kMaterialMaxCount>& GetMaterials() const;

		const std::vector<std::string>& GetMaterialNames() const;

		//const BoundingSphere& GetBoundingSphere() const;

		FRTransformManagerWarp::Instance GetTransInstance();
		
		FRRenderableManagerWarp::Instance GetRenderInstance();

		FREntityWarp* GetEntity();

		FRModel* Create();

	public:
		~FRModel();

		//void ComputeBoundingSphere();

	public:
		std::string path;

	private:
		std::vector<FRMesh*> mMeshes;
		std::array<FRMaterial*, kMaterialMaxCount> mMaterials;

		FREntityWarp* mEntity{ nullptr };
		SkeletonRig* mSkeletonRig{ nullptr };

		std::vector<std::string> mMaterialNames;
		glm::mat4 mTransformData = glm::mat4(1.0f);
		glm::mat4 mAccTransformData = glm::mat4(1.0f);

		//BoundingSphere m_boundingSphere;

	};
}

